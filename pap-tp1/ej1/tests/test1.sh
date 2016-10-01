N=50

pn="$(head -1 test1.in)"
ds="$(tail -1 test1.in)"


for i in $(seq 1 $N)
do
    dsp="$(shuf -e $ds)"
    k="$(echo $pn $dsp | ../ej1)"
    if [ "$k" -ne 40 ]
    then
        echo $pn
        echo $dsp
        echo "=> $k"
        exit 1
    fi
done
