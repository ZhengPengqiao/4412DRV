# uboot fastboot命令驱动修改（uboot-imx/drivers/fastboot/fastboot.c）

展开
1、添加块类型的分区
	确定分区名字
	设置分区起始地址
	设置分区块的大小
2、添加分区表类型的分区
	确定分区名字
	获取分区的分区表信息
	设置分区起始地址