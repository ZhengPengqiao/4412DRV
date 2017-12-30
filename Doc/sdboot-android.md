# 使用SD卡启动Android（**还未实现**)

## 制作文件镜像，或者挂在文件镜像

* 得到system.img
* $simg2img  system.img  system_raw.img
* $mkdir  system
* mount -t ext4 -o loop system_raw.img system
* .... "随意"修改system目录下的文件
* $./make_ext4fs -s -l 512M -a system system_new.img system    #512M表分区大小 第一个system表示挂载点为/system, 第二个system表示system目录。
* 新生成的system_new.img就可以用来烧写了。

## android分区及uboot引导 (**还没有搞好**)

```text
/dev/block/mmcblk0p2 /system ext4
/dev/block/mmcblk0p3 /data   ext4
/dev/block/mmcblk0p4 /cache  ext4

'console=ttySAC0,115200n8 androidboot.console=ttySAC0 ctp=2 skipcali=y vmalloc=384m ethmac=1C:6F:65:34:51:7E androidboot.selinux=permissive lcd=S702'
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
    setenv bootargs console=ttySAC0,115200n8 androidboot.console=ttySAC0 lcd=S700
    saveenv
    ```
* 然后重启Tiny4412即可。

**************************************************************************************
**************************************************************************************
