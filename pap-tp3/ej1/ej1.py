def calcularBordes(s):
	n = len(s)
	bordes = [-1 for _ in range(n+1)]
	bordes[1] = 0
	for i in range(2,n+1):
		j = bordes[i-1]
		while (j >= 0 and s[i-1] != s[j]):
			j = bordes[j]
		bordes[i] = j + 1
	return bordes

nombre = input()
apodo = input()
esSubstring = len(apodo) in calcularBordes(apodo + '#' + nombre)
print('S' if esSubstring else 'N')
