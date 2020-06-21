INC_DIR=/usr/local/boost1.70.0/include
BIN_DIR=./bin
SRC_DIR=./src
OBJ_DIR=./obj

SRC_FILES=${wildcard ${SRC_DIR}/*.cpp}
INC_FILES=${wildcard ${INC_DIR}/*.cpp}

OBJ=${patsubst %.cpp,${OBJ_DIR}/%.o, ${notdir ${SRC_FILES}}} \
	${patsubst %.cpp,${OBJ_DIR}/%.o, ${notdir ${INC_FILES}}}

TARGET=test
BIN_TARGET=${BIN_DIR}/${TARGET}

CC=g++
CFLAGS=-g -Wall -I${INC_DIR}

${BIN_TARGET}: ${OBJ}
	${CC} ${OBJ} -o $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	${CC} ${CFLAGS} -c $< -o $@
${OBJ_DIR}/%.o: ${INC_DIR}/%.cpp
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${BIN_TARGET} ${OBJ_DIR}/*.o
