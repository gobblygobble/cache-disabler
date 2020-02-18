#EXTRA_CFLAGS = -m32
obj-m += disableCache.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test: all
	sudo insmod ./disableCache.ko
	dmesg | tail -2
	sudo rmmod disableCache
	dmesg | tail -2
