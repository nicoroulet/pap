D=$((10**9))

rand() {
    shuf -n$1 -ri1-$D | paste -d' '
}

n=40
p=$(rand 1)
ds="$(rand $n)"

echo -e $p $n $ds | tee /dev/stderr | ../ej1
