#!/bin/bash

if [ $# -ne 1 ]; then
	echo "usage: create_all_clones.sh <clone_dir>"
	exit -1
fi

CLONE_DIR=$1
mkdir -p ${CLONE_DIR}

# cloneBench <bench> <top>
function cloneBench {
	BENCH=$1
	TOP=$2
	
	#check for source dir
	SRC_DIR=examples/${BENCH}
	if [ ! -d "${SRC_DIR}" ]; then
		echo "Directory ${SRC_DIR} does not exists"
		exit -1
	fi
	
	OUT_DIR=${CLONE_DIR}/${BENCH}
	mkdir -p ${OUT_DIR}
	
	TARGET_DIR=${OUT_DIR}/orig
	rm -rf ${TARGET_DIR}
	mkdir -p ${TARGET_DIR}
	
	cp -r ${SRC_DIR}/* ${TARGET_DIR}
	OLD_DIR=$PWD
	cd ${TARGET_DIR}
	make
	cd ${OLD_DIR}
	
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 10000
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 5 &
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 10 &
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 20 &
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 50 &
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 100 &
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 200 &
	./create_clone.sh ${TARGET_DIR} ${OUT_DIR} ${TOP} 500 &
	wait
}

#cloneBench scatter_gather 95
#cloneBench nw 92
#cloneBench particlefilter 92
#cloneBench pathfinder 92
#cloneBench srad 92
cloneBench bfs 90
#cloneBench gobmk 90
#cloneBench hmmer 90
#cloneBench h264ref 90
#cloneBench libquantum 90
#cloneBench mcf 90


