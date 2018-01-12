sdram.bin: start.o clock_init_tiny4412.o mem_init_tiny4412.o mmc_relocate.o
	arm-linux-ld -Tsdram.lds -o sdram.elf $^
	arm-linux-objcopy -O binary sdram.elf boot.bin
	arm-linux-objdump -D sdram.elf > sdram_elf.dis
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c 

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis  -f
