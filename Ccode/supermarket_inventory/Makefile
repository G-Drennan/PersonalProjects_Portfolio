
######################
##### Variables ######
######################

# Where the .c files are
SDIR=src

# Where the header files are
HDIR=include

# The compile you're using
CC=gcc

# Preprocessor flags (lets the preprocessor know where the header files are)
CPPFLAGS=-I$(HDIR)

# Handy compiler flags
CFLAGS=-Wall -pedantic

# What you want the output to be named
TARGET=inventory

# Chuck it all together
$(TARGET): $(wildcard $(SDIR)/*.c)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(TARGET) $(wildcard $(SDIR)/*.c)

# If you run 'make clean' this will remove the executable
.PHONY: clean
clean:
	$(RM) $(TARGET)
