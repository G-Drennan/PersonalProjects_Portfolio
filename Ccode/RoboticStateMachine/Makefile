
CC = gcc
CFLAGS=-g -Wall -std=c99 -Iinclude
LIBS=-lm
TARGET = state_machine 

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
_DEPS = state_machine.h operation_functions.h SM_Main_funct.h
_OBJS = main.o operation_functions.o state_machine.o SM_Main_funct.o
_OBJSMain = main.o

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OBJSMain) $(TARGET)



