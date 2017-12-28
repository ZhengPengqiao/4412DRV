# sd_fuse文件夹介绍

## 裸机程序下载

* 裸机焼写时，将需要焼写的代码，放在Doc中。
* 进入./sd_fuse/tiny4412
* 运行： sudo ./sd_fusing.sh /dev/{设备名}

* 烧录裸机到SD卡的工具 **sd_fuse**
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

        #<make bl2>
        #将裸机程序经过处理为bl2.bin
        ${MKBL2} ${E4412_UBOOT} bl2.bin 14336

        ####################################
        # fusing images

        signed_bl1_position=1
        bl2_position=17
        uboot_position=49
        tzsw_position=705

        #<BL1 fusing>
        echo "---------------------------------------"
        echo "BL1 fusing"
        dd iflag=dsync oflag=dsync if=./E4412_N.bl1.bin of=$1 seek=$signed_bl1_position

        #<BL2 fusing>
        echo "---------------------------------------"
        echo "BL2 fusing"
        dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position

        #<u-boot fusing>
        echo "---------------------------------------"
        echo "u-boot fusing"
        dd iflag=dsync oflag=dsync if=${E4412_UBOOT} of=$1 seek=$uboot_position

        #<TrustZone S/W fusing>
        echo "---------------------------------------"
        echo "TrustZone S/W fusing"
        dd iflag=dsync oflag=dsync if=./E4412_tzsw.bin of=$1 seek=$tzsw_position

        #<flush to disk>
        sync

        ####################################
        #<Message Display>
        echo "---------------------------------------"
        echo "U-boot image is fused successfully."
        echo "Eject SD card and insert it again."
    ```
