#!/bin/bash

rm -rf ps/*
cd gv
for f in *; do
	dot -Tps $f -o ../ps/$f.ps
done
