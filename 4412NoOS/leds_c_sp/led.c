#define 	GPM4CON 	(*(volatile unsigned long *) 0x110002E0)
#define 	GPM4DAT		(*(volatile unsigned long *) 0x110002E4)

void delay(int r0)					// 延时
{
    volatile int count = r0;
    while (count--)
        ;
}

void led_blink()					// LED闪烁
{
	GPM4CON = 0x00001111;			// 配置引脚
	while(1)							
	{
		GPM4DAT = 0;				// LED on
		delay(0x200000);
		GPM4DAT = 0xf;				// LED off
		delay(0x200000);
	}
}
