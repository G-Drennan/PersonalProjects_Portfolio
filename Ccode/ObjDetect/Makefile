C = gcc
CFLAGS=-g -Wall -std=c99 -Iinclude
LIBS=-lm
TARGET = cam_detect 

SRC_DIR = src
OBJ_DIR = build
INC_DIR = include
_DEPS = bitmap.h CamDetectFuncs.h
_OBJS = cam_detect.o bitmap.o CamDetectFuncs.o
_OBJSMain = cam_detect.o

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OBJSMain) $(TARGET)



