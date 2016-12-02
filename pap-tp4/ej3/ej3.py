from math import atan2, pi # atan2(y,x): angulo en radianes del vector (x,y) con respecto a la horizontal, en sentido antihorario
from sys import exit

class point(tuple):
    def __add__(self, other):
        return point(s + o for (s, o) in zip(self, other))
    def __sub__(self, other):
        return point(s - o for (s, o) in zip(self, other))
    def __abs__(self):
        return sqrt(sum(s ** 2 for s in self))
    def angle(self, other):
        vx, vy = self
        wx, wy = other
        return (atan2(vy, vx) - atan2(wy, wx)) % (2 * pi)

def readPoint():
    return point(map(int, input().strip().split()))

class triangle(tuple):
    def __new__(self, points):
        a, b, c = tuple(sorted(points))
        return super(triangle, self).__new__(self, (a,b,c) if ((b-a).angle(c-a) < pi) else (a,c,b))
    def __contains__(self, point):
        if point in tuple(self): return False
        a, b, c = self
        ab = b - a
        ac = c - a
        bc = c - b
        ba = a - b
        ap = point - a
        bp = point - b
        return ab.angle(ap) <= ab.angle(ac) and bc.angle(bp) <= bc.angle(ba)


h, e = readPoint()
puntosBuenos = sorted([readPoint() for _ in range(h)])
puntosMalos = [readPoint() for _ in range(e)]

triangulos = {} # diccionario punto inferior -> [(triangulo, cant de puntos internos)]
for i in range(h):
    for j in range(i+1, h):
        for k in range(j+1, h):
            t = triangle([puntosBuenos[x] for x in [i,j,k]])
            if all(not x in t for x in puntosMalos):
                cantBuenos = sum(x in t for x in puntosBuenos) # puntos internos buenos
                triangulos.setdefault(t[0], []).append((t, cantBuenos + 1))

if not triangulos:
    print(min(2, h))
    exit()

maximo = 0
for i in range(h):
    actual = puntosBuenos[i]
    if not actual in triangulos: continue
    sucesores = {}
    valor = {}
    for (a, b, c), cant in triangulos[actual]:
        sucesores.setdefault(b, []).append(c)
        valor[(b,c)] = cant
    sucesoresConvexos = {}
    for (a, b, c), cant in triangulos[actual]:
        sucesoresConvexos[(b,c)] = [x for x in sucesores[c] if (b - c).angle(x - c) > pi] if c in sucesores else []
    for (b,c) in reversed(sorted(valor.keys(), key = lambda t : (point((0,1)).angle(t[1]-a), point((0,1)).angle(t[0]-a)))):
        valor[(b,c)] += max([0] + [valor[(c,d)] for d in sucesoresConvexos[(b,c)]])
    maximo = max([maximo] + list(valor.values()))
print(maximo + 2)
