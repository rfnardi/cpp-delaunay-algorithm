#! /bin/bash

DELTA_Z=0.001

NUM_LINHAS=200
MAX_NUM_LIN=10000

NUM_EXP=500

while [ $NUM_LINHAS -lt $MAX_NUM_LIN ]
do
    cat parafuso_teste | head -$NUM_LINHAS > conjunto-teste
    echo "Arquivo contendo $NUM_LINHAS linhas."
    EXP=0
    while [ $EXP -lt $NUM_EXP ]
    do
        echo "Experimento $EXP"
        ./conversor-stl conjunto-teste $DELTA_Z
        let EXP=EXP+1
    done
    let NUM_LINHAS=NUM_LINHAS+200
done