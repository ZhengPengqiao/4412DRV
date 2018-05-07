DEVPARTNAME=/media/zpq/0CB9-C64F/
ADDRESS=0x70003000

.PHONY:main_bin
main_bin:
	arm-linux-gcc -c main.c  -o main.o
	arm-linux-ld  -Ttext=$(ADDRESS)  main.o  -o main
	arm-linux-objcopy -I elf32-littlearm  -O binary   main  main.bin

.PHONY:clean
clean:
	rm -f main.o  main  main.bin   *~ 

.PHONY:cp
cp:
	cp ./main.bin $(DEVPARTNAME)
	sync
	umount $(DEVPARTNAME)


