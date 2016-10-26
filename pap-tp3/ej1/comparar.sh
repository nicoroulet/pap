for file in tests/*.test; do
	echo "Probando $file"
	python3 ej1.py < "$file" > "$file.out"

	echo "Diff entre $file.out y $file.res"
    diff "$file.out" "$file.res"

    echo " "
done