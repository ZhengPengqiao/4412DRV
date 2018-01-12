DEVNAME=sdc

link.bin: start.o main.o 
	arm-linux-ld -Tlink.lds -o link.elf $^
	arm-linux-objcopy -O binary link.elf boot.bin
	arm-linux-objdump -D link.elf > link_elf.dis
	
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