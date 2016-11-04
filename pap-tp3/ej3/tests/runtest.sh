# sh runtest.sh testunos.py 1000 1000 1000

T1=$(mktemp)
T2=$(mktemp)

eval "$@" 2> $T2 | python ../ej3.py > $T1

diff $T1 $T2

rm $T1 $T2
