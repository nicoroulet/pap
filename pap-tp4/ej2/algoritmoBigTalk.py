from random import shuffle

def correr(lista):
  shuffle(lista)
  cantidadpasos = 0
  while(0 < len(lista)):
    shuffle(lista)
    while(0 < len(lista) and lista[0] == min(lista)):
      del lista[0]
    cantidadpasos= cantidadpasos+1
  
  return cantidadpasos

print("Ingrese la lista")
s = input()
lista = list(map(int, s.split()))
print("Ingrese cantidad de repeticiones")
m = input()
j = 0
res = []
while(j < int(m)):
  j+=1
  listaCopia = lista[:]
  res.append(correr(listaCopia))
print("Se corrió ", m, " veces. En promedio dio:", (sum(res)/float(len(res))))