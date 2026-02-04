PROJECT_DIR=.

CFLAGS=-I${PROJECT_DIR}/include/
CC=gcc
CXX=g++ -std=c++11

# Using OpenCV for Visualization
OPENCV=1
ifeq ($(OPENCV), 1)
	LDFLAGS+=  `pkg-config --libs opencv4`
	CFLAGS+= -DOPENCV=1 `pkg-config --cflags opencv4`
endif

SRC_DIR=${PROJECT_DIR}/src

all: bfs

bfs: main
	./bin/main bfs

dfs: main
	./bin/main dfs

rdfs: main
	./bin/main rdfs 

main: ${SRC_DIR}/linked_list.cpp ${SRC_DIR}/graph.cpp ${SRC_DIR}/queue.cpp ${SRC_DIR}/stack.cpp ${SRC_DIR}/bfs.cpp ${SRC_DIR}/dfs.cpp ${SRC_DIR}/rdfs.cpp ${SRC_DIR}/main.cpp
	${CXX} ${CFLAGS} $^ ${LDFLAGS} -o bin/$@ 
