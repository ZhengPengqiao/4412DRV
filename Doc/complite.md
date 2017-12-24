# <center>编译tiny4412系统</center>

## 编译uboot

>本u-boot源代码由三星原厂提供，并由友善之臂修改移植，以适用于Tiny4412开发板平台。

### Build uboot

* 配置编译环境
  * arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz，并设置好环境变量PATH，保证可以正常使用。
* 解压并编译uboot
  ```C
  tar xzf uboot_tiny4412_0929.tar.gz
  cd uboot_tiny4412
  make tiny4412_config
  make
  ```
* 编译 用于生成bl2 的工具
  ```C
  方法1：make -C sd_fuse
  方法2：cd sd_fuse; make
  ```

### 制作启动 Tiny4412 的SD卡

* 先准备一张4G或以上的SDHC卡
  * 注意：该卡的已有数据将会被破坏，因此请先对SD卡上的数据进行备份。
  * 将uboot和三星特殊引导代码烧录进SD卡中
  * 假设SD卡识别的设备名是:/dev/sdb
    ```C
    cd sd_fuse/tiny4412
    sudo ./sd_fusing.sh /dev/sdb
    ```

### 使用SD卡启动 Tiny4412 并烧写Android

* 将已经制作好的SD卡插到 Tiny4412 板上，拨动S2切换到SDBOOT，同时连接串口线到PC且假设已经准备好。
* 开发板加电，然后在串口控制台(如minicom)，按任意键进入uboot 命令行模式
* 对SD卡进行分区
  * 输入以下uboot命令即可对SD卡进行分区：
  * fdisk -c 0 320 806 518
  * 重新分区后，可重新格式化FAT分区
  * fatformat mmc 0:1

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
### 使用SD卡启动 Android

* 如果是使用HD700，则烧写完成后直接重启Tiny4412 即可自动启动 Android
* 如果是使用S700，则需要在uboot上设置kernel命令行参数:
    ```C
    setenv bootargs console=ttySAC0,115200n8 androidboot.console=ttySAC0 lcd=S700
    saveenv
    ```
* 然后重启Tiny4412即可。

**************************************************************************************
**************************************************************************************

## 将对应代码保存在linux-3.5同级目录，增加权限，运行后将在同级目录中的image中存在编译好的内核

### 编译linux-qt内核

```bash
#!/bin/bash
mkdir -p ./image
cd ./linux-3.5
cp ./tiny4412_linux_defconfig .config
make -j4
cp ./arch/arm/boot/zImage ../image
```

### 编译linux-ubuntu内核

```bash
#!/bin/bash
mkdir -p ./image
cd ./linux-3.5
cp ./tiny4412_ubuntu_defconfig .config
make -j4
cp ./arch/arm/boot/zImage ../image
```

### 编译linux-android内核

```bash
#!/bin/bash
mkdir -p ./image
cd ./linux-3.5
cp ./tiny4412_android_defconfig .config
make -j4
cp ./arch/arm/boot/zImage ../image
```

**************************************************************************************
**************************************************************************************

## 制作文件镜像，或者挂在文件镜像

* 得到system.img
* $simg2img  system.img  system_raw.img
* $mkdir  system
* mount -t ext4 -o loop system_raw.img system
* .... "随意"修改system目录下的文件
* $./make_ext4fs -s -l 512M -a system system_new.img system    #512M表分区大小 第一个system表示挂载点为/system, 第二个system表示system目录。
* 新生成的system_new.img就可以用来烧写了。

## 如果uboot中没有支持TRUSTZONE，则内核中就不能选择此选项： CONFIG_ARM_TRUSTZONE

```text
    CONFIG_ARM_TRUSTZONE
    -->System type
        -->Support TrustZone-enabled Trusted Execution Evvironment 
```

## 开启内核调试功能：

```text
    CONFIG_DEBUG_LL
    -->Kernel hacking 
        -->Kernel low-level debuging functions
```

## 从SD卡中启动的Uboot启动参数

```text
bootargs=root=/dev/mmcblk0p2 console=ttySAC0,115200 lcd=S70 ctp=2
bootcmd=fatload mmc 0:1 0x40008000 zImage;bootm 0x40008000
```

## 错误：Kernel panic - not syncing: Attempted to kill init! exitcode=0x00000100

* 文件系统有问题，使用了iMX6_ubuntu_12.04.tgz文件系统可以正常显示

## 编译内核

```text
make -j4
make -j4 modules
make modules_install INSTALL_MOD_PATH=../modules
```

## android分区及uboot引导

```text
/dev/block/mmcblk0p2 /system ext4
/dev/block/mmcblk0p3 /data   ext4
/dev/block/mmcblk0p4 /cache  ext4
root=/dev/mmcblk0p2 rootfstype=ext4 console=ttySAC0,115200 init=/linuxrc ctp=2 skipcali=y ethmac=1C:6F:65:34:51:7E lcd=S702
```
