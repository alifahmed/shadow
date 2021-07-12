#!/bin/bash

make -j

OBJ_FILES=$(find . -type f -name '*.out')

for bin in ${OBJ_FILES}; do
	echo ${bin}
	${bin}
done


#make clean
