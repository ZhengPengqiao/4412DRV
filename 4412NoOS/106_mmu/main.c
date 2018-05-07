/*
 * 李柏章　Li Baizhang,  makelinux@gmail.com, 2013-08, 
 */


#include "regs.h"

void (*printf)(char *, ...) = 0x43e11a2c;

void init_ttb(unsigned long *ttb_base, unsigned long *ttb_l2);
void mmap(unsigned long *ttb_base, unsigned long va, unsigned long pa);
void memset(char *buf, char ch, int size);

void main(void)
{	
	unsigned long c1_flags, ttb = 0x53000000;
	unsigned long ttb_l2 = 0x54000000;
	volatile int *p = 0x52345678;
	*p = 0x52300000;	
	printf("init_ttb \n");
	init_ttb(ttb, ttb_l2);
	printf("mmap \n");
	mmap(ttb, 0x12345678, 0x52345678);
	printf("mmap end\n");
	c1_flags = 1  | (1 << 3) | ( 1 << 11) | (1 << 28);

	__asm__ __volatile__ (
		"mvn r0, #0 \n"			
		"mcr p15, 0, r0, c3, c0, 0\n"

		"mov r0, #0\n"
		"mcr p15, 0, r0, c7, c7, 0\n" //invalidate I & D cache 
		"mcr p15, 0, r0, c8, c7, 0\n" //invalidate I & D TLB

		"mcr p15, 0, %1, c2, c0, 0\n" //configure ttb
		"mcr p15, 0, %0, c1, c0, 0\n" //enable mmu
		:
		: "r" (c1_flags), "r" (ttb)
		: "r0"
	);

	printf("mmu init end\n");
	printf("mmu init end\n");
	printf("mmu init end\n");
	printf("mmu init end\n");
	
	//p = 0x12345678;
	//printf("*p = 0x%08x\n",  *p);
}

void init_ttb(unsigned long *ttb_base, unsigned long *ttb_l2)
{
	unsigned long va, pa;

	memset(ttb_base, 0x00, 16 * 1024 );		

	for (va = 0x00000000; va < 0x14000000; ttb_l2+= 0x400) {
		unsigned long to;
		ttb_base[ va >> 20] = ((unsigned long)ttb_l2 & 0xfffffc00) | 1;	
		to = va + 0x100000;
		for (  ; va < to; va += 0x1000) {
			pa = va;
			ttb_l2[(va >> 12) & 0xff] = (pa & 0xfffff000) | 2; 
		}
	}


	for (va = 0x40000000; va < 0x80000000; ttb_l2+= 0x400) {
		unsigned long to;
		ttb_base[ va >> 20] = ((unsigned long)ttb_l2 & 0xfffffc00) | 1;	
		to = va + 0x100000;
		for (  ; va < to; va += 0x1000) {
			pa = va;
			ttb_l2[(va >> 12) & 0xff] = (pa & 0xfffff000) | 2; 
		}
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











