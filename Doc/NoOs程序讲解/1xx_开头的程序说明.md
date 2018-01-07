# 1xx_开头的程序说明

## 这类程序是在uboot启动后,通过dnw,或者sd卡的方式,将需要执行的程序load到ram,然后在跳转到指定位置运行程序

* 因为是在uboot中加载和执行的,所以可以使用uboot的函数,但是需要指定相应函数的地址
  * 例如printf函数(具体地址需要通过编译uboot时产生的System.map文件中查找):
  * void (*printf)(char *, ...) = 0x43e11a2c;
* 可以使用dnw将程序加载进RAM并运行
  * dnw 0x50000000
  * go 0x50000000
* 也可以将文件放入sd卡的fat分区中,加载进RAM并运行
  * fatload mmc 0:1 0x50000000 main.bin
  * go 0x50000000