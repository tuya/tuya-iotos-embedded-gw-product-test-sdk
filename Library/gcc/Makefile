CURRENT_DIR = $(abspath ./)

.PHONY:clean all

DEST = demo

COMPILE_PREX ?=
CC = $(COMPILE_PREX)gcc

OUTPUT_DIR = $(CURRENT_DIR)/output
INC_DIR = $(CURRENT_DIR)/sdk/include
LIB_DIR = $(CURRENT_DIR)/sdk/lib/static
DEMO_NAME = $(CURRENT_DIR)/demo/demo.c

LINKFLAGS = -lm -pthread
CCFLAGS = \
	-g -fPIC -Wall -Wno-missing-braces -Wno-unused-function -Wno-unused-variable -Wno-pointer-sign -Wno-unused-but-set-variable

all: demo
	@mkdir -p $(OUTPUT_DIR)/bin
	@cd $(OUTPUT_DIR)/bin/;pwd;$(CC) -o  $(DEST) $(DEMO_NAME) -I$(INC_DIR) -L$(LIB_DIR) -ltuya_prodtest $(LINKFLAGS) $(CCFLAGS)
	@echo "Build DEMO Finish"

clean:
	@rm -rf *~
	@rm -rf $(OUTPUT_DIR)
	@echo "clean finish"
