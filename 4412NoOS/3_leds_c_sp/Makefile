DEVNAME=sdc

led_sp.bin: start.o led.o
	arm-linux-ld -Ttext 0x0 -o led_sp.elf $^
	arm-linux-objcopy -O binary led_sp.elf u-boot.bin
	arm-linux-objdump -D led_sp.elf > led_sp_elf.dis
	
%.o : %.S
	arm-linux-gcc -o $@ $< -c

%.o : %.c
	arm-linux-gcc -o $@ $< -c 

.PHONY:clean
clean:
	rm *.o *.elf *.bin *.dis  -f

.PHONY:fuseToSD
fuseToSD:
	sudo ../sd_fuse/tiny4412/sd_fusing.sh /dev/${DEVNAME}
	sync