# Uncompressing Linux..... done, booting the kernel.

## 造成Uncompressing Linux..... done, booting the kernel.的常见的几种可能罗列一下

* 机器码不匹配

  * 解决方法：在配置内核时开启debug 
    ```C
    Kernel hacking 
        -> <*> Kernel low-level debugging functions
    Kernel hacking 
        -> <*> Kernel low-level debugging messages via S3C UART
    Device Drivers
        ->Character devices
            ->Serial drivers 
                -><*> Samsung SoC serial support
                -><*> Support for console on Samsung SoC serial port
    ```

  * 如果是机器码不匹配的问题，就会出现相关打印信息例如
    ```C
    Machine configuration botched (nr 182), unable to continue.
    ```

  * 核对一下你的uboot机器码是否匹配。
  * 如果不匹配，你可以修改uboot include/asm-arm/mach-types.h 文件中有关机器码的定义。或者修改内核 arch/arm/tools/mach-types 文件。
  * 在新内核移植时有关机器码的修改步骤及分析如下：
    * 修改机器码,机器码在/arch/arm/mach-s3c2440/mach-test2440.c文件中MACHINE_START(TEST2440, "TEST2440")这一行定义的,第二个参数无所谓,重要的是第一个参数,在gcc编译这个mach-test2440.c的时候,会把TEST2440匹配到/include/asm-arm/mach-types.h中的"#define MACH_TYPE_TEST2440 N"这里, 如果在mach-types.h中找不到MACH_TYPE_TEST2440的定义, gcc编译mach-test2440.c则报错;
    * 还有,/include/asm-arm/mach-types.h是每次make zImage过程中, 由arch/arm/tools/mach-types文件生成的,

  * 总结,修改机器码,涉及内核代码的三个地方,MACHINE_START宏,mach-types.h,mach-types,初启动时,bootloader向内核传递一个机器码。

* 串口配置不正确

  * 确保在配置内核时选上了在
    ```C
    Device Drivers
        ->Character devices
            ->Serial drivers
                -><*> Samsung SoC serial support
                -><*> Support for console on Samsung SoC serial port
    ```

* arch/arm/mach-s3c2440/Kconfig配置文件设置出错，某项关键选项没选上。

  * 这个情况在网上不多见，但是一出错就会让人很纠结。如果芯片级或板级关键配置没选上或导致内核启动进入start_kernel函数之前就进入死循环。如果芯片级的配置没选上，会在内核执行完cpu id号匹配函数__lookup_processor_type()后进入死循环，这种情况你无论怎么配置内核的debug，串口都不会再有打印信息输出了。只有点个灯之类的才能跟踪代码的执行。
  * 这种情况往往在打印Uncompressing Linux..... done, booting the kernel后就无任何输出了，即便你配置了debug。
* 我碰到这种情况是因为我在arch/arm/mach-s3c2440/Kconfig 上没有select ARCH_S3C2440。
* 导致Uncompressing Linux..... done, booting the kernel 卡住的大致就这几种情况。
