.globl _start

_start:
	// 关闭看门狗
	ldr	r0, =0x10060000  //WTCON
	mov	r1, #0
	str	r1, [r0]

	// 设置GPM4CON的bit[0:4]，配置GPM4_0/1/2/3引脚为输出功能
	ldr r1, =0x110002E0 					
	ldr r0, =0x00001111
	str r0, [r1]

	// 设置闪烁的次数,使用r2有问题，可能和调用c语言有关
	mov r5, #20

led_blink:
	// 设置GPM4DAT的bit[0:3]，使GPM4_0/1/2/3引脚输出低电平，LED亮
	ldr r1, =0x110002E4 				
	mov r0, #0
	str r0, [r1]


    // 延时,r0是传递的第一个参数
	mov r0, #0x200000
	bl delay

	// 设置GPM4DAT的bit[0:3]，使GPM4_0/1/2/3引脚输出高电平，LED灭
	ldr r1, =0x110002E4 					
	mov r0, #0xf
	str r0, [r1]

    
    // 延时,r0是传递的第一个参数
	mov r0, #0x200000
	bl delay
	
    sub r5, r5, #1
	cmp r5, #0
	bne led_blink


halt:
	b halt



