#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Error : usage cmd path_to_csv"
else
	value=`grep -o ',' $1 | wc -l`
	python visu_csv.py $value $1
fi