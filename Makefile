APP_EXE  = classifier
APP_SRC  = main.c $(STARTUP)
LDSCRIPT = ../common/soc.ld
RISCV_GCC_OPTS = -nostartfiles -T $(LDSCRIPT) -march=$(MARCH) -mabi=$(MABI) -O2

include ../common/common.mk

