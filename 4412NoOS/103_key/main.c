/*
 * 李柏章　Li Baizhang,  makelinux@gmail.com, 2013-08, 
 */


#include "regs.h"


//GPX3_2  --->  k1
//GPX3_3  --->  k2
//GPX3_4  --->  k3
//GPX3_5  --->  k4
//K1/K2/K3/K4 : 0 == Keydown, 1 == Keyup

#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3

#define KEY1MASK (1<<2)
#define KEY2MASK (1<<3)
#define KEY3MASK (1<<4)
#define KEY4MASK (1<<5)

void keys_init();
int  keys_val();
void leds_init();
void leds_Off(int ledNum);
void leds_On(int ledNum);
void delay(unsigned long count);
void (*printf)(char *, ...) = 0x43e11a2c;


int main(void)
{
	int keyVal;
	
	leds_init();
	keys_init();
	while(1) 
	{
		keyVal = keys_val();

		if (keyVal & KEY1MASK) 
		{
			leds_Off(LED1);
		}
		else
		{
			leds_On(LED1);
			printf("Key1 Down\r\n");
		}

		if (keyVal & KEY2MASK) 
		{
			leds_Off(LED2);
		}
		else
		{
			leds_On(LED2);
			printf("Key2 Down\r\n");			
		}

		if (keyVal & KEY3MASK) 
		{
			leds_Off(LED3);
		}
		else
		{
			leds_On(LED3);
			printf("Key3 Down\r\n");			
		}

		if (keyVal & KEY4MASK) 
		{
			leds_Off(LED4);
		}
		else
		{
			leds_On(LED4);
			printf("Key4 Down\r\n");
		}
		delay(0x1000);
	}	

	return 0;
}

void keys_init()
{
	GPX3CON &= ~(0xFFFF << 8); //Configure GPX3_2/GPX3_3/GPX3_4/GPX3_5 as input
}

int keys_val()
{
	return GPX3DAT;
}

void leds_init()
{
	GPM4CON  &= ~0xffff;
	GPM4CON  |=  0x1111;
}

void leds_On(int ledNum)
{
	GPM4DAT  &=  ~(1<<ledNum);
}


void leds_Off(int ledNum)
{
	GPM4DAT  |=  (1<<ledNum);
}

// 延时函数
void delay(unsigned long count)
{
	volatile unsigned long i = count;
	while (i--)
		;
}