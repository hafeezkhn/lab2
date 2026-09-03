obj-m += char_driver.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc -Wall test_app.c -o test_app

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f test_app