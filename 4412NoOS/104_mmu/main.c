/*
 * 李柏章　Li Baizhang,  makelinux@gmail.com, 2013-08, 
 */


#include "regs.h"

void (*printf)(char *, ...) = 0x43e11a2c;

void main(void)
{	
	unsigned int main_id, cpu_feature, c1_flags ;
	__asm__ __volatile__ (
		"mrc p15, 0, %0, c0, c0, 0\n"
		"mrc p15, 0, %1, c0, c1, 0\n"
		"mrc p15, 0, %2, c1, c0, 0\n"
		: "=r" (main_id), "=r" (cpu_feature), "=r" (c1_flags)
	);

	printf("MAIN ID:      0x%08x\n", main_id);
	printf("CPU FEATURE:  0x%08x\n", cpu_feature);
	printf("C1:	      0x%08x\n", c1_flags);

	c1_flags = (1 << 3) | ( 1 << 11) | (1 << 28);

	__asm__ __volatile__ (
		"mcr p15, 0, %0, c1, c0, 0\n"
		"mrc p15, 0, %0, c1, c0, 0\n"
		: "+r" (c1_flags)
	);
	printf("----------------------------------\n");	
	printf("C1:	      0x%08x\n", c1_flags);
}
