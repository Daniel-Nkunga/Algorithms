PROJECT_DIR=.
BIN_DIR=${PROJECT_DIR}/bin
SRC_DIR=${PROJECT_DIR}/src
INC_DIR=${PROJECT_DIR}/include

# Compiler and standard flags
CC=gcc
CXX=g++ -std=c++11
CFLAGS=-I${INC_DIR}

# Optional OpenCV Configuration
OPENCV=0
ifeq ($(OPENCV), 1)
    LDFLAGS+= `pkg-config --libs opencv4`
    CFLAGS+= -DOPENCV=1 `pkg-config --cflags opencv4`
endif

# Default target: Compile and run the mission planner
all: run

# Target to compile and run immediately
run: main
	./${BIN_DIR}/main

# Target for a fresh build and run
rerun: clean run

# Compilation of the main binary
# Includes the core data structures and the new HW5 algorithms
main: ${SRC_DIR}/linked_list.cpp \
      ${SRC_DIR}/queue.cpp \
      ${SRC_DIR}/graph.cpp \
      ${SRC_DIR}/algorithms.cpp \
      ${SRC_DIR}/visualization.cpp \
      ${SRC_DIR}/main.cpp
	@mkdir -p ${BIN_DIR}
	${CXX} ${CFLAGS} $^ ${LDFLAGS} -o ${BIN_DIR}/$@

# Cleanup
clean:
	rm -rf ${BIN_DIR}

.PHONY: all run rerun clean