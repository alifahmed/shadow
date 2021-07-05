#!/bin/bash

if [ $# -ne 1 ]; then
	echo "usage: create_all_clones.sh <clone_dir>"
	exit -1
fi

CLONE_DIR=$1

BENCH=scatter_gather
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 95 1 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 95 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 95 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 95 1000 &
wait


BENCH=nw
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1000 &
wait


BENCH=particlefilter
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1000 &
wait


BENCH=pathfinder
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1000 &
wait


BENCH=srad
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 92 1000 &
wait


BENCH=bfs
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 90 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 90 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 90 1000 &
wait


BENCH=gobmk
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 1 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 1000 &
wait


BENCH=hmmer
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 1000 &
wait


BENCH=h264ref
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 1000 &
wait


BENCH=libquantum
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 1 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 100 &
wait


BENCH=mcf
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 10 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 100 &
./create_clone.sh examples/${BENCH} ${CLONE_DIR}/${BENCH} 85 1000 &
wait



