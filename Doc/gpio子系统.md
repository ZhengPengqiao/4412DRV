# gpio子系统

* 在用户空间可以通过/sys/class/gpio来控制gpio引脚
  * 可以使用/sys/class/gpio/来控制gpio的前提是：要使用的gpio没有被系统使用。
  * 操作目录：/sys/class/gpio/
  * 注册一个引脚: echo gpio引脚号 > export
  * 注册成功后，就会出现一个gpio{引脚号}的文件夹
  * 进入引脚的文件夹： cd gpio{引脚号}
  * 设置引脚的方向： echo out/in > direction
  * 设置引脚或读取引脚的值： 读取：cat ./value   设置：echo 1/0 > ./value
  * 注销一个引脚: echo gpio引脚号 > unexport
* 例如：
    ```C
    root@iMX6-ubuntu-desktop:/sys/class/gpio#
    root@iMX6-ubuntu-desktop:/sys/class/gpio# echo  79 > export
    root@iMX6-ubuntu-desktop:/sys/class/gpio#
    root@iMX6-ubuntu-desktop:/sys/class/gpio# ls
    export       gpiochip137  gpiochip182  gpiochip239  gpiochip31  gpiochip79
    gpio79       gpiochip145  gpiochip191  gpiochip246  gpiochip37  gpiochip88
    gpiochip0    gpiochip153  gpiochip200  gpiochip25   gpiochip42  gpiochip9
    gpiochip106  gpiochip16   gpiochip209  gpiochip255  gpiochip47  gpiochip97
    gpiochip115  gpiochip161  gpiochip218  gpiochip264  gpiochip56  unexport
    gpiochip122  gpiochip169  gpiochip227  gpiochip273  gpiochip64
    gpiochip131  gpiochip178  gpiochip234  gpiochip282  gpiochip70
    root@iMX6-ubuntu-desktop:/sys/class/gpio#
    root@iMX6-ubuntu-desktop:/sys/class/gpio# cd gpio79
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79#
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79# ls
    active_low  direction  power  subsystem  uevent  value
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79#
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79# echo out > direction
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79#
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79# echo 1 > value
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79#
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79# echo 0 > value
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79#
    root@iMX6-ubuntu-desktop:/sys/class/gpio/gpio79# cd ..
    root@iMX6-ubuntu-desktop:/sys/class/gpio#
    root@iMX6-ubuntu-desktop:/sys/class/gpio# echo 79 > unexport
    root@iMX6-ubuntu-desktop:/sys/class/gpio#
    root@iMX6-ubuntu-desktop:/sys/class/gpio#
    ```