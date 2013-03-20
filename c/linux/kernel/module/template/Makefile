#
# 通用内核模块编译 Makefile
# epheien@163.com - 2013-01-12
#

# 内核的 Makefile 读取的分支，防止重复读入此分支
ifneq ($(KERNELRELEASE),)
DEBUG := y

# 模块名字，不包括后缀名
module := hello

# 如果模块由多个对象文件组成，添加到这个变量
# NOTE: 模块名不能和这个变量中的任何对象名字（不包括后缀名）相同
#       例如 obj-m := mod.o，那么 $(mod-objs) 就不能有 mod.o
$(module)-objs := 
$(module)-objs += 

ifeq ($(DEBUG),y)
  DEBUG_CFLAGS := -O0 -g
else
  DEBUG_CFLAGS := -O2
endif

# 额外的编译选项添加到这个变量，不允许修改 CFLAGS 变量
EXTRA_CFLAGS := $(DEBUG_CFLAGS)

# obj-m 不需要修改
obj-m := $(module).o

# ============================================================================
# 这里之后的代码无须修改
else

# 默认的内核头文件目录，可被环境变量覆盖
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
# 此文件所在目录
PWD := $(shell pwd)

RECIPE = $(MAKE) -C $(KERNELDIR) M=$(PWD) $@

modules:
	$(RECIPE)

modules_install:
	$(RECIPE)

clean:
	$(RECIPE)

.PHONY: modules modules_install clean
endif
