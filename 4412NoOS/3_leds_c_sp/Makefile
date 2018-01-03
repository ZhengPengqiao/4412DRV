led_sp.bin: start.o led.o
	arm-linux-ld -Ttext 0x0 -o led_sp.elf $^
	arm-linux-objcopy -O binary led_sp.elf u-boot.bin
	arm-linux-objdump -D led_sp.elf > led_sp_elf.dis
	cp u-boot.bin ../../Doc/
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis  -f
