DEVNAME=sdc

led_icache.bin: start.o led.o
	arm-linux-ld -Ttext 0x0 -o led_icache.elf $^
	arm-linux-objcopy -O binary led_icache.elf boot.bin
	arm-linux-objdump -D led_icache.elf > led_icache_elf.dis


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