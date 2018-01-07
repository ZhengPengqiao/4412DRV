//#define CONFIG_SYS_ICACHE_OFF  

.global _start

_start:
	// 关闭看门狗
	ldr	r0, =0x10060000
	mov	r1, #0
	str	r1, [r0]

    // 打开icache可提高运行速度
	// 将cp15的寄存器c1值读到r0中
   	mrc	p15, 0, r0, c1, c0, 0
	
#ifdef CONFIG_SYS_ICACHE_OFF
    // clear bit 12 (I) I-cache
    bic	r0, r0, #0x00001000//??
#else
    // set bit 12 (I) I-cache
    orr	r0, r0, #0x00001000
#endif
    mcr	p15, 0, r0, c1, c0, 0
	//mcr p15, 0, r0, c7, c5, 0	@ invalidate icache

	// 设置栈，以便调用c函数,
	// exynox4412内部的256K的位置0x0202_0000~0x0206_0000
	ldr	sp, =0x02060000

	// 调用c函数,LED闪烁
	bl	main

halt:
	b halt

