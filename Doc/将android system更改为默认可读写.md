# 将android system更改为默认可读写

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
