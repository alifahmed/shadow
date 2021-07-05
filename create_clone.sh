#!/bin/bash

if [ $# -ne 4 ]; then
	echo "usage: create_clone.sh <orig_dir> <clone_dir> <top> <step_in_million>"
	exit -1
fi

ROOT_DIR=$PWD
PIN_BIN=${ROOT_DIR}/pin/pin
TARGET=${ROOT_DIR}/obj-intel64/MAPProfiler.so

ORIG_DIR=${ROOT_DIR}/$1
CLONE_DIR=${ROOT_DIR}/$2
TOP_PERC=$3
INTERVAL=$4

#check if original directory exists
if [ ! -d "${ORIG_DIR}" ]; then
	echo "Directory ${ORIG_DIR} does not exists"
	exit -1
fi 

#check for bin file
if [ ! -f "${ORIG_DIR}/cmd.bin" ]; then
	echo "Original binary file name ${ORIG_DIR}/cmd.bin does not exists"
	exit -1
fi

cd ${ORIG_DIR}
make

#check for bin file
ORIG_BIN=${ORIG_DIR}/$(cat ${ORIG_DIR}/cmd.bin)
if [ ! -f "${ORIG_BIN}" ]; then
	echo "Original binary file ${ORIG_BIN} does not exists"
	exit -1
fi

#check for argument file
ARG_FILE=${ORIG_DIR}/cmd.param
if [ ! -f "${ARG_FILE}" ]; then
	echo "Argument file ${ARG_FILE} does not exists"
	exit -1
fi



mkdir -p ${CLONE_DIR}

CLONE_OUT_DIR=${CLONE_DIR}/${INTERVAL}M
rm -rf ${CLONE_OUT_DIR}
mkdir ${CLONE_OUT_DIR}
echo "" > ${CLONE_OUT_DIR}/cmd.param
echo "genCode.out" > ${CLONE_OUT_DIR}/cmd.bin

PIN_CMD="${PIN_BIN} -t ${TARGET} -out ${CLONE_OUT_DIR}/genCode.cpp -top ${TOP_PERC} -step ${INTERVAL}000000 -- ${ORIG_BIN} $(cat ${ARG_FILE})"

INPUT_FILE=${ORIG_DIR}/cmd.input
if [ ! -f "${INPUT_FILE}" ]; then
	${PIN_CMD}
else
	cat $(cat ${INPUT_FILE}) | ${PIN_CMD}
fi

