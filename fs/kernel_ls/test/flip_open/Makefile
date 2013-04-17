#Makefile test_filp_open.c
obj-m := test_flip_open.o

CURRENT_PATH := $(shell pwd)
KERNEL_VERSION := $(shell uname -r)
LINUX_KERNEL_PATH := /usr/src/linux-headers-$(KERNEL_VERSION)

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
