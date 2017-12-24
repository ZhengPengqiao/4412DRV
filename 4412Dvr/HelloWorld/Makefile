KERN_DIR = /home/zpq/WorkPlatfrom/tiny4412/linux-3.5
TARGET := tiny4412_helloworld
obj-m	+= tiny4412_helloworld.o

all:
	make -C $(KERN_DIR) M=`pwd` modules

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
