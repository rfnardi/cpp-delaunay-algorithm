#! /bin/bash
if [ $# -lt 1 ]
then
    echo "quantas linhas? (multiplo de 200)"
    exit
fi
SUM=0
COUNT=0
for TIME in $(cat "timer.log" | grep "$1 " | awk '{print $2 " "}')
do
    let COUNT=COUNT+1
    let SUM=SUM+TIME
done
echo "Contagem de $COUNT parcelas."
echo "Média de $((SUM / COUNT)) ms."
