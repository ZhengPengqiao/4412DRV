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
	unsigned long c1_flags, ttb = 0x53000000;
	volatile int *p1 = 0x52300000,
		     *p2 = 0x52400000;
	*p1 = 0x52300000;
	*p2 = 0x52400000;

	init_ttb(ttb);

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

	p1 = 0x12300000;

	mmap(ttb, 0x12300000, 0x52300000);
	printf("1st: *p = 0x%08x\n",  *p1);

	__asm__ __volatile__ (
		"mov r0, #0\n"
		/* invalidate I & D TLB */
//		"mcr p15, 0, r0, c8, c7, 0\n"
		/* invalidate D TLB */
//		"mcr p15, 0, r0, c8, c6, 0\n"
		/* invalidate D TLB signel entry */
		"mcr p15, 0, %0, c8, c6, 1\n"
		:
		: "r" (0x12300000)
		: "r0"
	);
	mmap(ttb, 0x12300000, 0x52400000);
	printf("2nd: *p = 0x%08x\n",  *p1);
}

void init_ttb(unsigned long *ttb_base)
{
	unsigned long va, pa;

	memset(ttb_base, 0x00, 16 * 1024 );		

	for (va = 0x50000000; va < 0x58000000; va += 0x100000) {
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) | 2;	
	}
	for (va = 0x70000000; va < 0x80000000; va += 0x100000) {
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) |  2;	
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











