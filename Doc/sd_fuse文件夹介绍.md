# sd_fuse文件夹介绍

## mkbl2文件修改,一定要注意

* 文件:V310-EVT1-mkbl2.c
    ```C
    #if 0   //代码大于14K
        //如果裸机程序大于14K,则需要将程序重定向到别的位置，将程序前14K修改为具有校验码的程序，
        //在14K代码内，需要实现代码重定位。
        if ( BufLen > fileLen )
        {
            printf("Usage: unsupported size\n");
            free(Buf);
            fclose(fp);
            return -1;
        }

        nbytes = fread(Buf, 1, BufLen, fp);

        if ( nbytes != BufLen )
        {
            printf("source file read error\n");
            free(Buf);
            fclose(fp);
            return -1;
        }

    #else       //代码小于14K

        //焼写裸机程序时，裸机程序一般14K,所以这里按照规定，在14K位置添加校验码，将裸机程序转为转换为合格的bin文件
        if ( fileLen >  (BufLen-16))
        {
            printf("Usage: unsupported size,size more than 14K \n");
            free(Buf);
            fclose(fp);
            return -1;
        }

        nbytes = fread(Buf, 1, BufLen, fp);

    #endif
    ```
* 此程序是生成bl2.bin程序用的,这里为了下载裸机程序,修改了一点代码,当裸机程序小于14K时,可以直接使用生成的bl2.bin就行,bl2.bin就是程序的前14K-4Bytes数据, 如果程序大于14K,需要在前14K数据中进行程序重定向.

## 裸机程序下载

* 裸机焼写时，将需要焼写的代码，放在Doc中。
* 进入./sd_fuse/tiny4412
* 运行： sudo ./sd_fusing.sh /dev/{设备名}

* 烧录裸机到SD卡的工具 sd_fuse
    ```C
        .
        ├── Makefile
        ├── mkbl2                   ...............V310-EVT1-mkbl2.c编译所得
        ├── sd_fdisk                ...............由sd_fdisk.c编译所得，格式化指定的SD卡
        ├── sd_fdisk.c
        ├── sd_mbr.dat
        ├── tiny4412
        │   ├── bl2.bin             ...............mkbl2运行所得，将裸机程序加上校验值后改为bl2.bin
        │   ├── E4412_N.bl1.bin     ...............exynos4412最开始运行的代码
        │   ├── E4412_tzsw.bin      ...............TrustZone
        │   ├── fast_fuse.sh
        │   └── sd_fusing.sh
        └── V310-EVT1-mkbl2.c
    ```
* Makefile
    ```C
        CFLAGS  = -o
        $(CC) $(CFLAGS)	mkbl2 V310-EVT1-mkbl2.c     ......将V310-EVT1-mkbl2.c编译为mkbl2
        $(CC) $(CFLAGS)	sd_fdisk sd_fdisk.c         ......将sd_fdisk.c编译为sd_fdisk
    ```
* sd_fusing.sh程序
    ```C
        #
        # Copyright (C) 2011 Samsung Electronics Co., Ltd.
        #              http://www.samsung.com/
        #
        # This program is free software; you can redistribute it and/or modify
        # it under the terms of the GNU General Public License version 2 as
        # published by the Free Software Foundation.
        #
        ####################################

        if [ -z $1 ]
        then
            echo "usage: ./sd_fusing.sh <SD Reader's device file>"
            exit 0
        fi

        if [ -b $1 ]
        then
            echo "$1 reader is identified."
        else
            echo "$1 is NOT identified."
            exit 0
        fi

        ####################################
        #<verify device>

        #找出设备名  如:sda/sdb/sdc
        BDEV_NAME=`basename $1`
        #得到对应设备的大小
        BDEV_SIZE=`cat /sys/block/${BDEV_NAME}/size`

        #设备大小 小于等于0，或者大于32G, 都会退出
        if [ ${BDEV_SIZE} -le 0 ]; then
            echo "Error: NO media found in card reader."
            exit 1
        fi

        if [ ${BDEV_SIZE} -gt 32000000 ]; then
            echo "Error: Block device size (${BDEV_SIZE}) is too large"
            exit 1
        fi

        ####################################
        # check files

        E4412_UBOOT=../../u-boot.bin
        MKBL2=../mkbl2

        #查看需要的文件是否存在
        if [ ! -f ${E4412_UBOOT} ]; then
            echo "Error: u-boot.bin NOT found, please build it & try again."
            exit -1
        fi

        if [ ! -f ${MKBL2} ]; then
            echo "Error: can not find host tool - mkbl2, stop."
            exit -1
        fi

        #<make bl2> <将裸机程序经过处理为bl2.bin>
        ${MKBL2} ${E4412_UBOOT} bl2.bin 14336

        ####################################
        # fusing images <每个镜像焼写的位置>
        signed_bl1_position=1
        bl2_position=17
        uboot_position=49
        tzsw_position=705

        #<BL1 fusing> <焼写E4412_N.bl1.bin到指定位置>
        echo "---------------------------------------"
        echo "BL1 fusing"
        dd iflag=dsync oflag=dsync if=./E4412_N.bl1.bin of=$1 seek=$signed_bl1_position

        #<BL2 fusing> <焼写裸机加校验后的bl2.bin到指定位置>
        echo "---------------------------------------"
        echo "BL2 fusing"
        dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position

        #<u-boot fusing>  
        #<如果裸机小于14K,可以都放在BL2中，不用重定向，这一步焼写就没意义了>
        #<如果代码大于14K,BL2存不下，所以需要将代码加载到这一部分，然后跳转到这里>
        echo "---------------------------------------"
        echo "u-boot fusing"
        dd iflag=dsync oflag=dsync if=${E4412_UBOOT} of=$1 seek=$uboot_position

        #<TrustZone S/W fusing> <焼写TrustZone代码>
        echo "---------------------------------------"
        echo "TrustZone S/W fusing"
        dd iflag=dsync oflag=dsync if=./E4412_tzsw.bin of=$1 seek=$tzsw_position

        #<flush to disk> <将处于内存的数据刷新到设备中>
        sync

        ####################################
        #<Message Display>
        echo "---------------------------------------"
        echo "U-boot image is fused successfully."
        echo "Eject SD card and insert it again."
    ```
