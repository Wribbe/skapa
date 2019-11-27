#!/bin/make

DIR_SRC=src
DIR_BIN=bin

SRC=$(wildcard ${DIR_SRC}/*.c)
BIN=$(foreach f,${SRC},$(subst $(DIR_SRC)/,,${DIR_BIN}/${f:%.c=%}))

all: ${BIN}

${DIR_BIN}/% : ${DIR_SRC}/%.c | ${DIR_BIN}
	gcc -g $(filter %.c %.o,$^) -o $@

${DIR_BIN}:
	mkdir $@
