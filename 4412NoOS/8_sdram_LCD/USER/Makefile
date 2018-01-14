user_bin: start.o main.o lcd.o
	arm-linux-ld -Tsdram.lds -o user_bin.elf $^
	arm-linux-objcopy -O binary user_bin.elf user.bin
	arm-linux-objdump -D user_bin.elf > user_bin_elf.dis
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c  

%.o : %.c
	arm-linux-gcc -o $@ $< -c   

clean:
	rm *.o *.elf *.bin *.dis -f
