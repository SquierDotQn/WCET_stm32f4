#/bin/bash

DIRS=`ls -l | grep drwxr | tr -s \ | cut -d\  -f 9`

for var in $DIRS; do
    python ../dlog_parser/dlog_to_csv.py $var/test
done