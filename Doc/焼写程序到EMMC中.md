
# 焼写程序到EMMC中

<尊重劳动成果_摘抄自：[<http://www.arm9home.net/read.php?tid-83474.html]>>

* EMMC存储和SD卡基本相同，只是一个是贴在板子上，一个是通过插座连接
    1. 下载附件dnw编译
    1. 按照友善文档，制作SD启动卡，开发板SW2开关选择SD启动.
    1. 把串口先连接PC与开发板。
    1. 插制作好的SD卡到开发板，并给开发板上电SW1.
    1. 键盘按任意键盘进入uboot终端，此时输入help可以看到很多指令。
    1. 现在我们进入了SD卡模式启动的u-boot. 现在我们看下mmc设备信息:
        ```C
            u-boot模式:  <可以看到一张mmc 0: 8G 4bit SD卡， 一个mmc 1: 4G 8bit EMMC>
            TINY4412 # mmcinfo 0
            Device: S3C_HSMMC2
            Manufacturer ID: 12
            OEM: 3456
            Name: SD
            Tran Speed: 0
            Rd Block Len: 512
            SD version 2.0
            High Capacity: Yes
            Size: 7540MB (block: 15441920)
            Bus Width: 4-bit
            Boot Partition Size: 0 KB
            TINY4412 #
            TINY4412 # mmcinfo 1
            Device: S5P_MSHC4
            Manufacturer ID: 15
            OEM: 100
            Name: 4YMD3
            Tran Speed: 0
            Rd Block Len: 512
            MMC version 4.0
            High Capacity: Yes
            Size: 3728MB (block: 7634944)
            Bus Width: 8-bit
            Boot Partition Size: 4096 KB
        ```
    1. 查看各设备分区信息
        ```C
            u-boot模式:  <mmc 0/1设备的分区表信息>
            TINY4412 # fdisk -p 0

            partion #    size(MB)     block start #    block count    partition_Id
            1          7539               32        15441888          0x0B
            TINY4412 #
            TINY4412 # fdisk -p 1

            partion #    size(MB)     block start #    block count    partition_Id
            1           407          6659994          835296          0x0C
            2           608           134244         1245486          0x83
            3          2057          1379730         4213770          0x83
            4           520          5593500         1066494          0x83
        ```
        * 这两条指令是分别查看mmc 0/1设备的分区表信息。
        * 设备mmc1的分区信息，即eMMC分析，注意这个是superboot分区信息，我们就用这个分区。
        * 分区1 是FAE分区， 分区2 是给system的，分区3是user-data, 分区4 是 cache.
    1. 格式化eMMC, u-boot模式下输入如下指令来格式化eMMC设备。
        ```C
            >fdisk -c 1 608 2057 520
            执行后会返回分区信息，继续格式话分区1，2，3，4
            >fatformat mmc 1:1
            这句话意思是对mmc 1设备的第一分区格式作fat格式化。
            >ext3format mmc 1:2
            >ext3format mmc 1:3
            >ext3format mmc 1:4
            上面三个指令是分别对eMMC的分区2,3,4作ext3格式化。

            到此我们完成了对eMMC的设备的格式化。

            接下来我们要想办法烧录bl1.bin, bl2.bin, u-boot.bin, tzsw.bin烧录到eMMC中。
        ```

    1. 从PC端下载固件到开发板Memory中。
        1. 使用DNW将程序下载到内存，然后将程序从缓存烧录到eMMC中。
        1. 首先我们要打开emmc设备

            ```C
            u-boot下输入：
            >emmc open 1
            eMMC OPEN Success.!!
                                    !!!Notice!!!
            !You must close eMMC boot Partition after all image writing!
            !eMMC boot partition has continuity at image writing time.!
            !So, Do not close boot partition, Before, all images is written.!
            上面提示emmc开启成功，注意说明，emmc一旦打开，需要连续烧录，烧录完成后可以关闭emmc.
            ```

        1. 接下来我们要运行dnw

            ```C
                u-boot下面输入：
                >dnw 0xc0000000
                OTG cable Connected!
                Now, Waiting for DNW to transmit data
                提示等待数据输入，这里就是等待我们从PC端通过DNW传送数据过来。

                此时在PC端终端串口，cd到u-boot目录所在路径
                user@~/u-boot/:
                输入： dwn sd_fuse/tiny4412/E4412_N.bl1.bin

                此时u-boot中断会提示传送校验完成，此时已经把bl1.bin通过USB传送到了memeory的0xc0000000起始地址，大小8KB.
                接下来我们烧录bl1.bin到eMMC中，u-boot下继续输入：
                >mmc write 1 0xc0000000 0 0x10
                会提示写入信息，说明已经写入成功。这个是把刚才从PC端通过dnw下载下来的bl1.bin固件下载到emmc中，起始0， 16个block, 一个block是512B, 16*512=8*1024=8KB. 这个是bl1.bin的存放位置。
            ```

            * 以此类推，烧录bl2.bin. u-boot.bin, tzsw.bin
            * u-boot终端继续输入：

            ```C
                >dnw 0xc0000000
                PC端输入: (注意输入内容是以 dnw 开始的，前面是当前路径，便于理解)
                user@~/u-boot/:  dwn sd_fuse/tiny4412/bl2.bin
                u-boot下继续输入：
                >mmc write 1 0xc0000000 0x10 0x1C
                bl2.bin实际大小约14K，分配的空间是16K. 其实是第16个block开始，写入28个block, 28*512B=14*1024=14K
                注意这个区域预分配是32个Block,所以下一个开始是32+16=48
            ```

            * u-boot终端继续输入：

            ```C
                >dnw 0xc0000000
                PC端输入: (注意输入内容是以 dnw 开始的，前面是当前路径，便于理解)
                user@~/u-boot/:  dwn u-boot.bin
                u-boot下继续输入：
                >mmc write 1 0xc0000000 0x30 0x21D
                u-boot.bin实际大小约270K，分配的空间是328K. 其实是第48个block开始，写入541个block, 541*512B=270.5*1024 约270K
            ```

            * u-boot终端继续输入：

            ```C
                >dnw 0xc0000000
                PC端输入: (注意输入内容是以 dnw 开始的，前面是当前路径，便于理解)
                user@~/u-boot/:  dwn sd_fuse/tiny4412/E4412_tzsw.bin
                u-boot下继续输入：
                >mmc write 1 0xc0000000 0x2c0 0xB8
                tzsw.bin实际大小约92K，分配的空间是160K. 其实是第704个block开始，写入184个block, 184*512=92*1024=92K
            ```

            ```C
                启动分区到此全部写入完成，注意一定要关闭emmc,
                u-boot下继续输入：
                >emmc close 1
                eMMC CLOSE Success.!!
                关闭emmc设备，提示关闭成功。此时我们已经把启动文件全部烧录到了eMMC中。
            ```

    1. 接下来我们可以把开发板的SW2拨动到NAND启动，同时u-boot中断输入reset, 并在电脑键盘按下任意键，此时我们可以看到：

        ```C
            U-Boot 2010.12-00000-g3e284d5-dirty (Jul 04 2014 - 17:40:58) for TINY4412

            CPU:    S5PC220 [Samsung SOC on SMP Platform Base on ARM CortexA9]
                    APLL = 1400MHz, MPLL = 800MHz

            Board:  TINY4412
            DRAM:   1023 MiB

            vdd_arm: 1.2
            vdd_int: 1.0
            vdd_mif: 1.1

            BL1 version:  N/A (TrustZone Enabled BSP)

            Checking Boot Mode ... EMMC4.41
            REVISION: 1.1
            MMC Device 0: 3728 MB
            MMC Device 1: 1876 MB
            MMC Device 2: N/A
            Read... Bootmode reg 0x00000000 
            Get Bootmode reg 0xf3ca4c36 
            ModeKey Check... run normal_boot 
            Net:    No ethernet found.
            Hit any key to stop autoboot:  0
            TINY4412 #
        ```

        * 大功告成啊，我们的u-boot已经成功写入到了eMMC中，并可以成功启动。

    1. 设置Uboot启动参数

        * 还有一件非常重要的事情我们还有做，就是启动参数写入，我们bootargs写入到env分区，注意ENV分区在TZSW分区后面，内核分区之前。即 TZSW | ENV | KERNEL
        * 从eMMC启动u-boot后，在u-boot终端输入：

            ```C
            >setenv bootargs console=ttySAC0,115200n8 androidboot.console=ttySAC0 uhost0=n ctp=2 skipcali=y vmalloc=512m lcd=S70
            >saveenv
            设置并保存启动参数，此时再重启板子，进入U-boot。
            u-boot下输入：
            >printenv
            查看刚才烧录的启动参数是否成功。
            ```

    1. 烧写kernel, system, ramdisk (这里是将kernal,system,ramdisk焼写到相应分区 （分区位置在uboot中定义）)

    ```C
        下面烧kernel, system,ramdisk和SD卡烧录一样。
        u-boot继续输入
        >fastboot
        进入fastboot模式

        PC端使用fastboot flash kernel zImag, fastboot flash system system.img, fastboot flash ramdisk ramdisk-u.img即可把剩下全部的img烧录到eMMC中。重启开发板，就可以启动开发板。
    ```

## 烧录到EMMC的指令

>emmc open 1
>dnw 0x40000000
输入： tiny4412_dnw2 ../../uboot_tiny4412_0929/sd_fuse/tiny4412/E4412_N.bl1.bin
>mmc write 1 0x40000000 0 0x10
>dnw 0x40000000
输入： tiny4412_dnw2 ../../uboot_tiny4412_0929/sd_fuse/tiny4412/bl2.bin
>mmc write 1 0x40000000 0x10 0x1C
>dnw 0x40000000
输入： tiny4412_dnw2 ../../uboot_tiny4412_0929/u-boot.bin
>mmc write 1 0x40000000 0x30 0x21D
>dnw 0x40000000
输入： tiny4412_dnw2 ../../uboot_tiny4412_0929/sd_fuse/tiny4412/E4412_tzsw.bin
>mmc write 1 0x40000000 0x2c0 0xB8
>emmc close 1
