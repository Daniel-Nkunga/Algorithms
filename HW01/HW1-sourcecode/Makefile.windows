PROJECT_DIR=.

CFLAGS=-I${PROJECT_DIR}/include/
CC=gcc
CXX=g++
# Using OpenCV for Visualization
OPENCV=0
ifeq ($(OPENCV), 1)
	LDFLAGS+=  -IC:/opencv-3.4.13/build/install/include
	CFLAGS+= -DOPENCV=1 -LC:/opencv-3.4.13/build/bin -lopencv_imgcodecs3413 -lopencv_core3413 \
				-lopencv_highgui3413 -lopencv_imgproc3413
endif

SRC_DIR=${PROJECT_DIR}/src

all: run

run: compile

compile: main

main: ${SRC_DIR}/linked_list.cpp ${SRC_DIR}/graph.cpp ${SRC_DIR}/queue.cpp ${SRC_DIR}/main.cpp
		${CXX} ${CFLAGS} $^ ${LDFLAGS} -o bin/$@.exe 





