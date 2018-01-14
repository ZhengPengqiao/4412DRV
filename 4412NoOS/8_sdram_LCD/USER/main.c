#include "lcd.h"

#define 	GPM4CON 	(*(volatile unsigned long *) 0x110002E0)
#define 	GPM4DAT		(*(volatile unsigned long *) 0x110002E4)




void main()				//LED 闪烁
{
	unsigned char val = 0;

	delay(0x200000);
	led_allOn();
	delay(0x200000);
	led_allOff();

	delay(0x200000);
	led_allOn();
	delay(0x200000);
	led_allOff();

	delay(0x200000);
	led_allOn();
	delay(0x200000);
	led_allOff();


	while(1)							
	{
		delay(0x200000);
		led_show_val(val);
		val++;
		val = (val&0x0F);
	}

}


