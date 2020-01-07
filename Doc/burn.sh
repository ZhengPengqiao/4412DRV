#!/bin/bash

fastboot flash fwbl1 ../../uboot_tiny4412_0929/sd_fuse/tiny4412/E4412_N.bl1.bin
fastboot flash bl2 ../../uboot_tiny4412_0929/sd_fuse/tiny4412/bl2.bin
fastboot flash bootloader ../../uboot_tiny4412_0929/u-boot.bin
fastboot flash tzsw ../../uboot_tiny4412_0929/sd_fuse/tiny4412/E4412_tzsw.bin
fastboot flash kernel ../../image/androidkernal/zImage
fastboot -w
fastboot flash ramdisk ../../image/androidkernal/Android/ramdisk-u.img
fastboot  -S 100M flash system ../../image/androidkernal/Android/system.img