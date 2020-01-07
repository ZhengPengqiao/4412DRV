# 制作SD卡-Linux系统

## 将当前终端配置为tiny4412的环境

* tiny4412配置编译环境
  * source /opt/tiny4412/4.5.1/environment.sh

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

* uboot引导参数介绍

    ```C
    TINY4412 # printenv
    baudrate=115200
    bootargs=root=/dev/mmcblk0p2 console=ttySAC0,115200 lcd=S70 ctp=2
    bootcmd=fatload mmc 0:1 0x40008000 zImage;bootm 0x40008000
    bootdelay=3
    ethaddr=00:40:5c:26:0a:5b
    gatewayip=192.168.0.1
    ipaddr=192.168.0.20
    netmask=255.255.255.0
    serverip=192.168.0.10

    Environment size: 284/16380 bytes
    ```

  * 从mmc的fat文件分区中读取zImage到0x40008000地址，然后跳转到这里运行
    * fatload mmc 0:1 0x40008000 zImage
    * bootm 0x40008000

* 编译 用于生成bl2 的工具

  ```C
  方法1：make -C sd_fuse
  方法2：cd sd_fuse; make
  ```

### 将编译出来的u-boot.bin烧录到SD卡中

* sd_fusing.sh会将三星提供的tiny4412开始的引导代码，和uboot一起烧录到SD卡上
* 先准备一张4G或以上的SDHC卡
  * 注意：该卡的已有数据将会被破坏，因此请先对SD卡上的数据进行备份。
  * 将uboot和三星特殊引导代码烧录进SD卡中
  * 假设SD卡识别的设备名是:/dev/sdb

    ```C
    cd sd_fuse/tiny4412
    sudo ./sd_fusing.sh /dev/sdb
    ```

## 编译linux-qt内核

```bash
#!/bin/bash
mkdir -p ./image
mkdir -p ./image/modules
cd ./linux-3.5
cp ./tiny4412_linux_defconfig .config
make -j4
make modules -j4
make modules_install INSTALL_MOD_PATH=../image/modules

cp ./arch/arm/boot/zImage ../image
cd ../image/modules
tar jcvf ../modules.tar.bz2 ./*
```

## 将内核和文件系统放到SD卡上

* 将SD卡分区

```shell
    #:~/WorkSpace/Tiny4412$ sudo fdisk /dev/sdc

    Welcome to fdisk (util-linux 2.31.1).
    Changes will remain in memory only, until you decide to write them.
    Be careful before using the write command.


    Command (m for help): n
    Partition type
    p   primary (0 primary, 0 extended, 4 free)
    e   extended (container for logical partitions)
    Select (default p): p
    Partition number (1-4, default 1): 
    First sector (2048-15728639, default 2048): 19531
    Last sector, +sectors or +size{K,M,G,T,P} (19531-15728639, default 15728639): 117188

    Created a new partition 1 of type 'Linux' and of size 47.7 MiB.

    Command (m for help): n
    Partition type
    p   primary (1 primary, 0 extended, 3 free)
    e   extended (container for logical partitions)
    Select (default p): p
    Partition number (2-4, default 2): 2
    First sector (2048-15728639, default 2048): 117189
    Last sector, +sectors or +size{K,M,G,T,P} (117189-15728639, default 15728639): 

    Created a new partition 2 of type 'Linux' and of size 7.5 GiB.

    Command (m for help): w
    The partition table has been altered.
    Calling ioctl() to re-read partition table.
    Syncing disks.
```

* 将分区格式化
  * sudo mkfs.fat /dev/sdc1
  * sudo mkfs.ext3 /dev/sdc2

* SD卡分两个分区
* 第一个分区（FAT32）
  * 将zImage,modules.tar.bz2放到Fat32分区中
* 第二个分区（EXT3）
  * sudo tar xvf rootfs_V0.3.tar.bz2 -C /media/zpq/573bdee7-b484-4b51-aa18-1876b65f53a6/

## 将SD卡插到Tiny4412开发板上，将启动模式拨到SDBoot位置，上电就可以启动

## 问题

* 如果uboot中没有支持TRUSTZONE，则内核中就不能选择此选项： CONFIG_ARM_TRUSTZONE

```text
    CONFIG_ARM_TRUSTZONE
    -->System type
        -->Support TrustZone-enabled Trusted Execution Evvironment
```

* 开启内核调试功能

```text
    CONFIG_DEBUG_LL
    -->Kernel hacking 
        -->Kernel low-level debuging functions
```
