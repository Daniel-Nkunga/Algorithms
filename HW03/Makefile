PROJECT_DIR=.

CFLAGS=-I${PROJECT_DIR}/include/ -std=c++14
CC=gcc
CXX=g++

FILES=linked_list.cpp graph.cpp queue.cpp stack.cpp bfs.cpp bst.cpp avl.cpp

# Using OpenCV for Visualization
OPENCV=1
ifeq ($(OPENCV), 1)
	LDFLAGS+=  `pkg-config --libs opencv4`
	CFLAGS+= -DOPENCV=1 `pkg-config --cflags opencv4`
endif

SRC_DIR=${PROJECT_DIR}/src/

SRC_FILES=$(addprefix ${SRC_DIR}, ${FILES})

all: bfs

bfs: main
	./bin/main

main: ${SRC_FILES} ${SRC_DIR}main.cpp
	${CXX} ${CFLAGS} $^ ${LDFLAGS} -o bin/$@ 


