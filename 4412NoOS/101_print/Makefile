default:
	arm-linux-gcc -c main.c  -o main.o
	arm-linux-ld  -Ttext=0x50000000  main.o  -o main
	arm-linux-objcopy  -O binary   main  main.bin
clean:
	rm -f main.o  main  main.bin   *~ 
