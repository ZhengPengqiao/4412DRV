.global _start

_start:
	// 关闭看门狗
	ldr	r0, =0x10060000			
	mov	r1, #0
	str	r1, [r0]

	// 设置栈，以便调用c函数,
	// exynox4412内部的256K的位置0x0202_0000~0x0206_0000
	ldr	sp, =0x02060000

	// 调用c函数,LED闪烁
	bl	main							

halt:
	b halt
