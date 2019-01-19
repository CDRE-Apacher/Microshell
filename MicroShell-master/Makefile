CC=gcc
CFLAGS=-Wall -ansi

BUILD_DIR=build/
BINARY=microshell
SOURCEFILES=main.c tokenizer.c util.c cmds.c

$(BINARY): $(SOURCEFILES) Makefile
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$(BINARY) $(SOURCEFILES) 
