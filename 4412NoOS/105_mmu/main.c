/*
 * 李柏章　Li Baizhang,  makelinux@gmail.com, 2013-08, 
 */


#include "regs.h"

void (*printf)(char *, ...) = 0x43e11a2c;

void init_ttb(unsigned long *ttb_base);
void mmap(unsigned long *ttb_base, unsigned long va, unsigned long pa);
void memset(char *buf, char ch, int size);

void main(void)
{	
	unsigned long c1_flags, ttb = 0x73000000;
	volatile int *p = 0x52345678;

	*p = 0x52300000;	//将地址赋予一个值0x52300000

	init_ttb(ttb);		//初始化段表
	mmap(ttb, 0x15345678, 0x52345678);  //映射 : 0x153  < --- > 0x523

	c1_flags = 1 | (1 << 3) | ( 1 << 11) | (1 << 28);

	__asm__ __volatile__ (
		"mvn r0, #0 \n"			
		"mcr p15, 0, r0, c3, c0, 0\n"

		"mcr p15, 0, %1, c2, c0, 0\n" //configure ttb

		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr %0, r0, %0\n"
		"mcr p15, 0, %0, c1, c0, 0\n" //enable mmu
		:
		: "r" (c1_flags), "r" (ttb)
		: "r0"
	);

	p = 0x15345678;  //映射之后,就可以操作0x15345678这个地址了,相当于操作0x52345678地址
	printf("*p = 0x%08x\n",  *p);
}

void init_ttb(unsigned long *ttb_base)
{
	unsigned long va, pa;

	memset(ttb_base, 0x00, 16 * 1024 );		

	for (va = 0x00000000; va < 0x10000000; va += 0x100000) { //Others
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) | 2;	
	}

	for (va = 0x10000000; va < 0x14000000; va += 0x100000) { //SFR
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) |  2;	
	}

	for (va = 0x40000000; va < 0x80000000; va += 0x100000) { //DRAM
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) | 2;	
	}
	
}

void mmap(unsigned long *ttb_base, unsigned long va, unsigned long pa)
{
	ttb_base[ va >> 20] = (pa & 0xfff00000) |  2;	
}

void memset(char *buf, char ch, int size)
{
	int i;
	for (i = 0; i < size; i ++)
		buf[i] = ch;
}











