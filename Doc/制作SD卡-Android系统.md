# 制作SD卡-Android系统

## 启动后,设备的名称

* 从EMMC中启动的时候
  * EMMC === mmcblk0
  * SD   === mmcblk1
* 从SD卡启动的时候:
  * SD   === mmcblk0
  * EMMC === mmcblk1

## 编译uboot

> 本u-boot源代码由三星原厂提供，并由友善之臂修改移植，以适用于Tiny4412开发板平台。

### Build uboot

* 解压并编译uboot

  ```C
  tar xzf uboot_tiny4412_0929.tar.gz
  cd uboot_tiny4412
  make tiny4412_config
  make
  ```

## 编译linux-android内核

```bash
#!/bin/bash
mkdir -p ./image
mkdir -p ./image/modules
cd ./linux-3.5
cp ./tiny4412_android_defconfig .config
make -j4
make modules -j4
make modules_install INSTALL_MOD_PATH=../image/modules

cp ./arch/arm/boot/zImage ../image
cd ../image/modules
tar jcvf ../modules.tar.bz2 ./*
```

## 相关文件放置，及对应的配置

* uboot
  * 将编译出来的u-boot.bin烧录到SD卡中
    * 编译 用于生成bl2 的工具

      ```C
      方法1：make -C sd_fuse
      方法2：cd sd_fuse; make
      ```

    * sd_fusing.sh会将三星提供的tiny4412开始的引导代码，和uboot一起烧录到SD卡上
    * 先准备一张4G或以上的SDHC卡
      * 注意：该卡的已有数据将会被破坏，因此请先对SD卡上的数据进行备份。
      * 将uboot和三星特殊引导代码烧录进SD卡中
      * 假设SD卡识别的设备名是:/dev/sdc

      ```C
      cd sd_fuse/tiny4412
      sudo ./sd_fusing.sh /dev/sdc
      ```

  * 使用fastboot烧录uboot
    * 在PC端通过fastboot烧写uboot到SD卡先手动生成bl2.bin
      * cd sd_fuse/tiny4412
      * ../mkbl2 ../../u-boot.bin bl2.bin 14336
      * 然后输入以下命令:

        ```C
          fastboot flash fwbl1 E4412_N.bl1.bin
          fastboot flash bl2 bl2.bin
          fastboot flash bootloader ../../u-boot.bin
          fastboot flash tzsw E4412_tzsw.bin
        ```

* kernel
  * 如果内核是使用fastboot烧录(fastboot flash kernel zImage)
    * movi read kernel 0 40008000;bootm 40008000"
  * 如果内核是直接放到第一个分区的FAT格式
    * fatload mmc 0:1 0x40008000 zImage;bootm 0x40008000

* 使用fastboot烧录的分区，使用ramdisk分区的文件系统
  * setenv bootargs "console=ttySAC0,115200n8 androidboot.console=ttySAC0 ctp=2 skipcali=y vmalloc=384m ethmac=1C:6F:65:34:51:7E androidboot.selinux=permissive lcd=S702"
  * setenv bootcmd "movi read kernel 0 40008000;movi read ramdisk 0 41000000 400000;bootm 40008000 41000000"
* 使用fat文件中内核，使用ramdisk分区的文件系统
  * setenv bootargs "console=ttySAC0,115200n8 androidboot.console=ttySAC0 ctp=2 skipcali=y vmalloc=384m ethmac=1C:6F:65:34:51:7E androidboot.selinux=permissive lcd=S702"
  * setenv bootcmd "fatload mmc 0:1 0x40008000 zImage;movi read ramdisk 0 41000000 400000;bootm 40008000 41000000"

## 启动android时，都是需要内核(zImage)和linux的最小文件系统(Ramdisk.img)

* 引导方式不同，但需要的东西是一样的。
  * 从EMMC启动时:
    * 从EMMC启动的时候，ramdisk是烧录到ramdisk分区的。启动的时候，加载ramdisk分区到内存，然后启动
    * bootcmd=movi read kernel 0 40008000;movi read ramdisk 0 41000000 400000;bootm 40008000 41000000
* 从SD卡启动时：
  * 我们也可以继续使用ramdisk分区.
    * bootcmd=movi read kernel 0 40008000;movi read ramdisk 0 41000000 400000;bootm 40008000 41000000
  * 或者将最小文件系统拷贝到指定分区,然后启动的时候在bootatgs中指定
    * root={ramdisk分区} init={init名字}

## 分区情况

```shell
# SD卡
TINY4412 # fdisk -p 0
partion #    size(MB)     block start #    block count    partition_Id 
   1          3925          7547652         8039556          0x0C 
   2          1028           138348         2105964          0x83 
   3          2064          2244312         4227300          0x83 
   4           525          6471612         1076040          0x83 

# EMMC
TINY4412 # fdisk -p 1

partion #    size(MB)     block start #    block count    partition_Id 
   1           407          6659994          835296          0x0C 
   2           608           134244         1245486          0x83 
   3          2057          1379730         4213770          0x83 
   4           520          5593500         1066494          0x83 
```

## android分区及uboot引导

  ```text
  文件：device/friendly-arm/tiny4412/conf/fstab.tiny4412
  /dev/block/mmcblk0p2 /system ext4 ro     wait
  /dev/block/mmcblk0p4 /cache  ext4 noatime,nosuid,nodev,nomblk_io_submit,errors=panic wait
  /dev/block/mmcblk0p3 /data   ext4 noatime,nosuid,nodev,nomblk_io_submit,noauto_da_alloc,errors=panic wait

  setenv bootargs 'root={ramdisk分区} init={init名字} console=ttySAC0,115200n8 androidboot.console=ttySAC0 ctp=2 skipcali=y vmalloc=384m ethmac=1C:6F:65:34:51:7E androidboot.selinux=permissive lcd=S702'
  ```

## 继续使用EMMC启动时使用的内核，和uboot,只更换android系统

  ```C
      /dev/block/mmcblk0p2 /system ext4 ro     wait
      /dev/block/mmcblk0p4 /cache  ext4 noatime,nosuid,nodev,nomblk_io_submit,errors=panic wait
      /dev/block/mmcblk0p3 /data   ext4 noatime,nosuid,nodev,nomblk_io_submit,noauto_da_alloc,errors=panic wait
    更换为
      /dev/block/mmcblk1p2 /system ext4 ro     wait
      /dev/block/mmcblk1p4 /cache  ext4 noatime,nosuid,nodev,nomblk_io_submit,errors=panic wait
      /dev/block/mmcblk1p3 /data   ext4 noatime,nosuid,nodev,nomblk_io_submit,noauto_da_alloc,errors=panic wait
      将android相应的东西拷贝到SD卡分区中，这里更换linux系统启动时，挂在的分区，之前是挂在EMMC的分区。可以更改为挂在SD卡中的分区，这样来启动SD卡中的android的系统。但是内核和最小文件系统使用的和EMMC启动的时候是一样的
  ```

## 使用SD卡启动 Tiny4412 并烧写Android

* 将已经制作好的SD卡插到 Tiny4412 板上，拨动S2切换到SDBOOT，同时连接串口线到PC且假设已经准备好。
* 开发板加电，然后在串口控制台(如minicom)，按任意键进入uboot 命令行模式
* 对SD卡进行分区
  * 输入以下uboot命令即可对SD卡进行分区：

      ```C
        fdisk -c 0 1024 2057 520
        执行后会返回分区信息，继续格式话分区1，2，3，4
        >fatformat mmc 0:1
        这句话意思是对mmc 0(SD)设备的第一分区格式作fat格式化。
        >ext3format mmc 0:2
        >ext3format mmc 0:3
        >ext3format mmc 0:4
        上面三个指令是分别对mmc 0(SD)的分区2,3,4作ext3格式化。
      ```

* 进入fastboot模式以烧写Android
  * 使用USB线连接Tiny4412的MICRO_USB口到PC，然后输入以下uboot命令:
  * fastboot

* 烧写 Android 到SD卡
  * 首先请准备好Android image，包括: zImage,ramdisk-u.img, system.img
  * 在PC端输入以下命令进行烧写:

    ```bash
      fastboot flash kernel zImage (烧写kernel)
      fastboot -w  (格式化userdata和cache)
      fastboot flash ramdisk ramdisk-u.img (烧写ramdisk)
      fastboot flash system system.img  (烧写system)
    ```

  * 也可以在PC端通过fastboot烧写uboot到SD卡先手动生成bl2.bin
    * cd sd_fuse/tiny4412
    * ../mkbl2 ../../u-boot.bin bl2.bin 14336

    * 然后输入以下命令:

      ```C
        fastboot flash fwbl1 E4412_N.bl1.bin
        fastboot flash bl2 bl2.bin
        fastboot flash bootloader ../../u-boot.bin
        fastboot flash tzsw E4412_tzsw.bin
      ```

## 相关问题

* 不同显示相关
  * 如果是使用HD700，则烧写完成后直接重启Tiny4412 即可自动启动 Android
  * 如果是使用S700，则需要在uboot上设置kernel命令行参数添加配置lcd=S700
* Q:prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.11-4.6//x86_64-linux/include/c++/4.6/bits/basic_string.h:235: error: unsupported reloc 43
  * A:cp /usr/bin/ld.gold prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.11-4.6/x86_64-linux/bin/ld 
* fastboot焼写system.img时出现FAILED (remote: data too large)，
  * 原因是fastboot版本太旧。换成sdk中的就行。
  * 指定每次传输的大小
    * fastboot -S xxxM flash system system.img

