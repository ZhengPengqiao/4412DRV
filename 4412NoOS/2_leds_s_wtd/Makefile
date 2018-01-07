DEVNAME=sdc

led_wtd.bin: start.o delay.o
	arm-linux-ld -Ttext 0x0 -o led_wtd.elf $^
	arm-linux-objcopy -O binary led_wtd.elf u-boot.bin
	arm-linux-objdump -D led_wtd.elf > led_wtd_elf.dis

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