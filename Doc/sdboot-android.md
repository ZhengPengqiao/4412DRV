# 使用SD卡启动Android（**还未实现**)

## 编译android 源代码

* Q:prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.11-4.6//x86_64-linux/include/c++/4.6/bits/basic_string.h:235: error: unsupported reloc 43
* A:cp /usr/bin/ld.gold prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.11-4.6/x86_64-linux/bin/ld 

## 将android system更改为默认可读写

* Android 系统默认情况下,system 分区是只读 mount 的,因此无法进行往里写数据的。
* 可以用 adb 命令 adb remount 重新 mount 一下.
* 也可通过在板子上,输入以下命令重新 mount 一下 system 分区令其可读可写:
  * mount -o remount /dev/block/mmcblk0p2 /system
* 该命令只对当前启动有效,重启后会恢复为只读。
* 如想 system 分区一直处于可读写,可能过修改 Android 源代码中的以下文件:
  ```C
    device/friendly-arm/tiny4412/conf/fstab.tiny4412
    将文件以下内容:
    /dev/block/mmcblk0p2 /system ext4 ro wait
    /dev/block/mmcblk0p2 /system ext4 rw wait
  ```

## 制作文件镜像，或者挂在文件镜像

* 得到system.img
* $simg2img  system.img  system_raw.img
* $mkdir  system
* mount -t ext4 -o loop system_raw.img system
* .... "随意"修改system目录下的文件
* $./make_ext4fs -s -l 512M -a system system_new.img system    #512M表分区大小 第一个system表示挂载点为/system, 第二个system表示system目录。
* 新生成的system_new.img就可以用来烧写了。

## 启动android时，也需要linux的最小文件系统，（Ramdisk.img）

1. 引导方式不同，但需要的东西是一样的。
1. 从EMMC启动时:
    1. 从EMMC启动的时候，ramdisk是烧录到ramdisk分区的。启动的时候，加载ramdisk分区到内存，然后启动
    1. bootcmd=movi read kernel 0 40008000;movi read ramdisk 0 41000000 400000;bootm 40008000 41000000
1. 从SD卡启动时：
    1. 我们也可以继续使用ramdisk分区，或者将最小文件系统拷贝到指定分区
    1. 然后启动的时候在bootatgs中指定：root={ramdisk分区} init={init名字}

## android分区及uboot引导

  ```text
  文件：device/friendly-arm/tiny4412/conf/fstab.tiny4412
  /dev/block/mmcblk0p2 /system ext4 ro     wait
  /dev/block/mmcblk0p4 /cache  ext4 noatime,nosuid,nodev,nomblk_io_submit,errors=panic wait
  /dev/block/mmcblk0p3 /data   ext4 noatime,nosuid,nodev,nomblk_io_submit,noauto_da_alloc,errors=panic wait

  setenv bootargs 'root={ramdisk分区} init={init名字} console=ttySAC0,115200n8 androidboot.console=ttySAC0 ctp=2 skipcali=y vmalloc=384m ethmac=1C:6F:65:34:51:7E androidboot.selinux=permissive lcd=S702'
  ```

### 使用SD卡启动 Tiny4412 并烧写Android

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
    * fastboot焼写system.img时出现FAILED (remote: data too large)，原因是fastboot版本太旧。换成sdk中的就行。
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
        bootargs lcd=S700
    ```
* 然后重启Tiny4412即可。

**************************************************************************************
**************************************************************************************
