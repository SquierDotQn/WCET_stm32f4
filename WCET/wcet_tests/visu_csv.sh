#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Error : usage cmd path_to_csv"
else
	python visu_csv.py $1
fi