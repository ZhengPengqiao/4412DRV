#define 	GPM4CON 	(*(volatile unsigned long *) 0x110002E0)
#define 	GPM4DAT		(*(volatile unsigned long *) 0x110002E4)

// 延时函数
void delay(unsigned long count)
{
	volatile unsigned long i = count;
	while (i--)
		;
}

void main()				//LED 闪烁
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


