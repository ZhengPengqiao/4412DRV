# LED

* 这是一个引脚控制LED等的简单驱动和测试程序，程序运行效果是计数性叠加

* EXYNOS4X12_GPM4宏定义的位置
  * arch/arm/mach-exynos/include/mach/gpio.h
    * #define EXYNOS4X12_GPM4(_nr)	(EXYNOS4X12_GPIO_M4_START + (_nr))
