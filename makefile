# Last updated 2022-02-15 by Shane McDonough
CC=clang# c compiler
EXTENSION=.c# c extension
TARGET=bin/test# the output file
DBG_TARGET=$(TARGET).debug
CFLAGS=-Wextra -Iinclude -fsanitize=address# flags to be passed to compiler
LIBS=# librarys to link
DBG_FLAGS=-g# flags for debugging
DEBUGGER=lldb# debugger to use
ifeq ("$(wildcard src/*$(EXTENSION))", "")# if there are no c files
	CC=clang++# c++ compiler
	EXTENSION=.cpp# c++ extension
	CFLAGS+=-std=c++20# c++ flags
endif
INCLUDES=$(wildcard include/*)# get all include files
OBJECTS=$(patsubst src/%$(EXTENSION),bin/%.o,$(wildcard src/*$(EXTENSION)))# in bin/%.o format, all of the objects to be compiled
DBG_OBJECTS=$(patsubst %,%.debug,$(OBJECTS))

all: $(TARGET)

$(TARGET): $(OBJECTS)# compile the target
	$(CC) $^ $(LIBS) $(CFLAGS) -o $@
	
bin/%.o: src/%$(EXTENSION) $(INCLUDES) bin# create object file for %
	$(CC) $< $(CFLAGS) -c -o $@

clean:# remove contents of bin
	rm -rf bin

bin:# create folder bin
	mkdir bin

test: all# compile everything then run executible
	$(TARGET)

# DEBUGGING RULES
debug: $(DBG_TARGET)# run make with debug flags and call lldb
	$(DEBUGGER) $(DBG_TARGET)

$(DBG_TARGET): $(DBG_OBJECTS)# create debug executable
	$(CC) $^ $(LIBS) $(CFLAGS) $(DBG_FLAGS) -o $@

bin/%.o.debug: src/%$(EXTENSION) $(INCLUDES) bin# create debug object file for %
	$(CC) $< $(CFLAGS) $(DBG_FLAGS) -c -o $@

.PHONY: all clean test debug
