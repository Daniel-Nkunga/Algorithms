PROJECT_DIR=.
CFLAGS=-I${PROJECT_DIR}/include/ -std=c++14 
CXX=g++

# Core logic files required for the integrated build
FILES=data_structures/disjoint_set.cpp \
      graph.cpp \
      main.cpp \
      sort/msort.cpp \
      sort/hsort.cpp \
      algorithms/topologicalsort.cpp \
      algorithms/rbtree.cpp

# OpenCV Configuration
OPENCV=0
ifeq ($(OPENCV), 1)
    LDFLAGS+= `pkg-config --libs opencv4`
    CFLAGS+= -DOPENCV=1 `pkg-config --cflags opencv4`
endif

SRC_DIR=${PROJECT_DIR}/src/
SRC_FILES=$(addprefix ${SRC_DIR}, ${FILES})
ALG_DIR=${SRC_DIR}algorithms/

# The first target is the default. Typing 'make' now runs the full system.
all: bin/integrated
	./bin/integrated

# Compiles everything into a single integrated binary
bin/integrated: ${SRC_FILES} ${ALG_DIR}kruskal.cpp ${ALG_DIR}dijkstra.cpp ${ALG_DIR}prim.cpp
	@mkdir -p bin
	${CXX} ${CFLAGS} -DKRUSKAL -DDIJKSTRA -DPRIM -DINTEGRATED $^ ${LDFLAGS} -o $@ 

clean:
	rm -rf bin/*