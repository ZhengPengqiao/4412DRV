DEVNAME=sdc

.PHONY:all
all:
	make -C ./BOOT
	make -C ./USER
	cp ./BOOT/boot.bin ./
	cp ./USER/user.bin ./

.PHONY:clean
clean:
	make clean -C ./BOOT
	make clean -C ./USER
	rm *.bin -rf

.PHONY:fuseToSD
fuseToSD:
	@echo "fuse bl2.bin and user.bin to SDCard"
	@sudo ../sd_fuse/tiny4412/sd_fusing.sh /dev/${DEVNAME}
	sync