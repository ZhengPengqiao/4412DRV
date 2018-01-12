DEVNAME=sdc

uart.bin: start.o mem_init_tiny4412.o main.o clock_init_tiny4412.o
	arm-linux-ld -Tuart.lds -o uart.elf $^
	arm-linux-objcopy -O binary uart.elf boot.bin
	arm-linux-objdump -D uart.elf > uart_elf.dis
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c 

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

.PHONY:clean
clean:
	rm *.o *.elf *.bin *.dis  -f

.PHONY:fuseToSD
fuseToSD:
	@echo "fuse bl2.bin and user.bin to SDCard"
	@sudo ../sd_fuse/tiny4412/sd_fusing.sh /dev/${DEVNAME}
	sync