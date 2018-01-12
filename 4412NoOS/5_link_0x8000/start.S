.global _start

_start:
	// 关闭看门狗
	ldr	r0, =0x10060000			
	mov	r1, #0
	str	r1, [r0]

	// 设置栈，以便调用c函数,
	// exynox4412内部的256K的位置0x0202_0000~0x0206_0000
	ldr	sp, =0x02060000			
			
	// 重定位
	// _start当前所位于的地址：0x02020000,  adr 指令获取的值是代码当前位于的地址
	adr r0, _start
	// _start的链接地址:0x02028000,  ldr 指令获取的值是代码的链接地址。
	ldr r1, =_start
	// bss段的起始地址
	ldr r2, =bss_start
	// 如果r0 == r1, 也就是当前代码地址就是链接地址,就不用重定向代码,直接跳转到clean_bss
	cmp r0, r1
	beq clean_bss
	
copy_loop:
	ldr r3, [r0], #4    // 源
	str r3, [r1], #4	// 目的
	cmp r1, r2
	bne copy_loop


// 清bss段
clean_bss:
	// bss的起始地址赋值给r0
	ldr r0, =bss_start
	// bss的结束地址赋值给r1
	ldr r1, =bss_end
	// 如果r0 == r1, 也就是没有bss空间,就不用清空数据,直接跳转到run_on_dram
	cmp r0, r1
	beq run_on_dram
	mov r2, #0

// 如果r0 != r1, 也就是有bss空间,就清空数据
clear_loop:
	str r2, [r0], #4
	cmp r0, r1
	bne clear_loop

// 跳转
run_on_dram:			 
	ldr pc, =main

halt:
	b halt

