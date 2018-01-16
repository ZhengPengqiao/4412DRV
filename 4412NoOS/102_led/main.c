
/*
 * 李柏章　Li Baizhang,  makelinux@gmail.com, 2013-08, 
 */


#include "regs.h"



void led_on(void);
void led_off(void);
void delay(unsigned long count);

int main(void)
{
	while(1)
	{
		led_on();
		delay(0x100000);
		led_off();
		delay(0x100000);
	}
	return 0;
}


void led_on(void)
{
	GPM4CON  &= ~0xffff;
	GPM4CON  |=  0x1111;
	GPM4DAT  |=  0xf;
}

void led_off(void)
{
	GPM4CON  &= ~0xffff;
	GPM4CON  |=  0x1111;
	GPM4DAT  &= ~0xf;
}

// 延时函数
void delay(unsigned long count)
{
	volatile unsigned long i = count;
	while (i--)
		;
}