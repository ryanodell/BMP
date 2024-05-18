CC = gcc
CFLAGS = #-Wall
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2

SRC_FILES = src/main.c 

DEPS = 

LINKER_FLAGS = 

all: debug release

debug: CFLAGS += $(DEBUG_FLAGS)
debug: build

release: CFLAGS += $(RELEASE_FLAGS)
release: build

OBJ_NAME = bin\main

build: $(SRC_FILES)
	$(CC) $(CFLAGS) $^ -o $(OBJ_NAME) $(LINKER_FLAGS)

clean:
	rm -f bin\main.exe

# Dependencies
$(SRC_FILES): $(DEPS)
