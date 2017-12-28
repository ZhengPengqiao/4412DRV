led.bin: start.o 
	arm-linux-ld -Ttext 0x0 -o led.elf $^
	arm-linux-objcopy -O binary led.elf u-boot.bin
	arm-linux-objdump -D led.elf > led_elf.dis	
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis  -f
