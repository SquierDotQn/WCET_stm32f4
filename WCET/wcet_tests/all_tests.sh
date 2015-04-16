#!/bin/bash
# Ce script permet de lancer tous les tests présents dans le repertoire wcet_tests

# Precision, dlog_to_csv.py demande BeautifulSoup4 d'installé

# Fait par Théo Plockyn

DIRS=`ls -l | grep drwxr | tr -s \ | cut -d\  -f 9`

for var in $DIRS; do
    ./launch_test.sh $var 10
    sleep 12
done

sleep 5

for var in $DIRS; do
    python ../dlog_parser/dlog_to_csv.py $var/
done

