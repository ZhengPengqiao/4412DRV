# <center>开发板作为USB设备模拟网卡(linux usb 网卡)</center>

## 对内核做如下配置

* make menuconfig
    ```c
    Device Drivers -->
        [*]USB support -->
            <*>USB Gadget Support -->
                <M>USB Gadget Drivers
                <M>Ethernet Gadget (with CDC Ethernet support)
                [*] RNDIS support
                <M>CDC Composite Device (Ethernet and ACM)
    ```
* 编译内核
  * make zImage
  * 此时带有gadget 以及RNDIS | CDC 的内核就生成了

## =====

* 虽然内核是生成了,但是居然WINDOWS检测不到设备,查阅开发板的手册之后才知道,USB 从设备还有一个USB_EN信号,高电平的时候USB SLAVE才会使用,所以下一步就得修改BOOTLOADER了
  * 根据我的情况,控制USB_EN的IO口是GPC5
  * 找到初始化IO口的函数.根据S3C2440芯片手册做如下修改(兰色为修改或添加的代码)
    ```C
    void Port_Init(void)
    {
    GPACON = 0x7fffff;
    GPBCON = 0x044555;
    GPBUP = 0x7ff;  // The pull up function is disabled GPB[10:0]
    GPCCON = 0xaaaaa6aa;
    GPCDAT = 0x0020;
    GPCUP = 0xff7f; // The pull up function is disabled GPC[15:0] ,enable gpc5 for usb_device
    GPDCON = 0x00151544;
    GPDDAT = 0x0430;
    GPDUP = 0x877A;
    GPECON = 0xaa2aaaaa;
    GPEUP = 0xf7ff; // GPE11 is NC
    GPFCON = 0x55aa;
    GPFUP = 0xff;  // The pull up function is disabled GPF[7:0]
    GPGCON = 1<<8;
    GPGDAT = 0;
    GPHCON = 0x16faaa;
    GPHUP = 0x7ff;  // The pull up function is disabled GPH[10:0]
    EXTINT0 = 0x22222222; // EINT[7:0]
    EXTINT1 = 0x22222222; // EINT[15:8]
    EXTINT2 = 0x22222222; // EINT[23:16]
    }
    ```
  * 说明:
    ```C
    GPCCON = 0xaaaaa6aa; //根据S3C2440的芯片手册gpc5[11:10]为控制该IO口的寄存器,所以第11,10位为分别为1,0
    GPCDAT = 0x0020; // 数据寄存器,1为高电平,所以第5位为1
    GPCUP = 0xff7f; //上拉电阻寄存器 第5位设为0
    ```

  * 再次编译bootloader,这次WINDOWS终于识别出设备了,至于驱动自己去网上找吧~我用的是CSDN上的驱动.最后还有一个问题,就是开发板有网卡,还模拟USB为网卡的情况,一定要保证usb虚拟的网卡和WINDOWS上USB网卡在同一个IP段,并且不能和开发板原先的网卡的IP段一样,要不累死你都PING不到~
  * 这样之后应该就能和WINDOWS PING通了~
