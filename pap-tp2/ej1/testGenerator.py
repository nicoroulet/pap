from sys import argv, exit
from random import shuffle, choice

"imprime el grafo por salida estandar para poder pipearlo directamente al ejecutable"

if len(argv) == 1:
  print "Uso: python testGenerator.py <tipo> <parametros>     tipo: Kn, Knm, 3capas"
graphType = argv[1]

nodeTypes = []
edges = []
n = 0
m = 0

if graphType == 'Kn':
  if len(argv) != 5:
    print "Parametros de Kn: n, n de casas, n de escuelas"
    exit()
  n = int(argv[2])
  nHouses = int(argv[3])
  nSchools = int(argv[4])
  if nHouses + nSchools > n:
    print "Demasiadas casas y escuelas %d %d %d" % (n, nHouses, nSchools)
    exit()
  m = n*(n-1)/2
  nodeTypes = ['A'] * nHouses + ['E'] * nSchools + ['X'] * (n - nHouses - nSchools)
  shuffle(nodeTypes)
  edges = [ (i+1, j+1)[::choice([1,-1])] for i in range(n) for j in range(i)]
  shuffle(edges)

if graphType == 'Knm':
  if len(argv) != 4:
    print "Parametros de Knm: n, m"
    exit()
  n1 = int(argv[2])
  n2 = int(argv[3])
  n = n1 + n2
  m = n1 * n2
  nodeTypes = ['A'] * n1 + ['E'] * n2
  shuffle(nodeTypes)
  edges = [ (i+1, j+1)[::choice([1,-1])] for i in range(n) for j in range(n) if nodeTypes[i] != nodeTypes[j]]
  shuffle(edges)

if graphType == 'ncapas':
  "hace un grafo con n capas, cada una completamente conectada con la/s capas vecinas, Casas en la primera y Escuelas en la ultima"
  if len(argv) < 4:
    print "Parametros de Kn: |capa1|, |capa2|, ..."
    exit()
  tamCapas = map(int, argv[2:])
  n = sum(tamCapas)
  # m = sum([tamCapas[i] * tamCapas[i+1] for i in range(len(tamCapas) - 1)])
  nodeTypes = ['A'] * tamCapas[0] + ['X'] * sum(tamCapas[1:-1]) + ['E'] * tamCapas[-1]
  for i in range(len(tamCapas) - 1):
    previos = sum(tamCapas[:i])
    edges += [ (previos + j + 1, previos + k + tamCapas[i] + 1)[::choice([1, -1])] for j in range(tamCapas[i]) for k in range(tamCapas[i+1])]
  m = len(edges)

print "%d %d" % (n, m)
for i in nodeTypes:
  print i
for edge in edges:
    print ("%d %d" % edge)

