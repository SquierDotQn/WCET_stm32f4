#!/bin/bash
# Ce script permet de flasher un algo sur la carte stm32f407 en donnant
# le chemin relatif vers le dossier contenant l'algo et le makefile

# Fait par Théo Plockyn

if [ $# -lt 2 ]; then
    echo "Mauvais usage : ./cmd path_to_wcet time"
    exit 1
fi

if [ ! -d $1 ]; then
    echo "Le path donné n'est pas correct"
    exit 1
fi
cd $1
./reload.sh > \dev\null 2>&1
echo "-------------------------"
echo ""
echo "<Appuyez sur Reset>"
echo ""
echo "-------------------------"
sleep 3
# TODO : trouver comment faire un reset automatiquement !
nb=`ls -l test | grep test_ | wc -l`
nb=`expr $nb + 1`
python ../auto.py $1_$nb $2

hasdir=`ls -l | grep drwxr | tr -s \ | cut -d\  -f 9 | grep test | wc -l`
if [ $hasdir -lt 1 ]; then
	mkdir test
fi
mv test_theo_$1_$nb.dlog test/

#TODO : conversion dlog -> csv
	
cd ..
