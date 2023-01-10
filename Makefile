C = gcc  # set the C compiler used
OFLAG = -o  # set the output flag
CFLAGS = -std=c17 -Wall -O2  # set the compiler flags

OS = $(shell uname)
ARCH = $(shell uname -p)
TARGET = voxel_engine
SRC = ./src
OBJ = ./objects
LIB = ./libs

MODE ?= RELEASE

SRC_FILES =\
	../$(SRC)/main.c

OBJ_FILES =\
	$(OBJ)/main.o

build: clean main

clean:
	@echo cleaning...
	rm -rf $(TARGET)/
	rm -rf $(OBJ)/
	rm -rf $(LIB)/
	rm -rf 3rd_party/glfw/build/

glew:
	@echo building glew
	cd 3rd_party/glew/auto && $(MAKE) PYTHON=python3.11
	cd 3rd_party/glew && $(MAKE) all
	mkdir -p $(LIB)/
	cp 3rd_party/glew/lib/libGLEW.a $(LIB)/libGLEW.a

glfw:
	@echo building glfw
	cd 3rd_party/glfw && cmake -DCMAKE_OSX_ARCHITECTURES=arm64 -S . -B build
	cd 3rd_party/glfw/build && $(MAKE)
	cp 3rd_party/glfw/build/src/libglfw3.a $(LIB)/libglfw3.a

main: glew glfw main.o
	mkdir -p $(TARGET)/
	$(C) -framework IOKit -framework Cocoa -framework OpenGL $(LIB)/libGLEW.a $(LIB)/libglfw3.a $(OFLAG) $(TARGET)/$(TARGET) $(OBJ_FILES)

main.o:
	@echo building $(TARGET) for $(ARCH) [$(OS)]
	mkdir -p $(OBJ)/
	cd $(OBJ) && $(C) $(CFLAGS) -I../3rd_party/glew/include -I../3rd_party/glfw/include -I../src/include -c $(SRC_FILES)
