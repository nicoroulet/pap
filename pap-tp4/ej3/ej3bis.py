from math import atan2, pi # atan2(y,x): angulo en radianes del vector (x,y) con respecto a la horizontal, en sentido antihorario

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
        # print(tuple(points))
        a, b, c = tuple(sorted(points))
        # print("etuple ", (a,b,c), (b-a).angle(c-a), atan2(b-a), atan2(c-a))
        print("building ", (a,b,c) if ((b-a).angle(c-a) < pi) else (a,c,b))
        return super(triangle, self).__new__(self, (a,b,c) if ((b-a).angle(c-a) < pi) else (a,c,b))
    def __contains__(self, point):
        if point in tuple(self): return False
        print(self)
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
            print(i,j,k)
            # print(triangle([puntosBuenos[x] for x in [i,j,k]]))
            # t = (puntosBuenos[i],) + tuple(sorted((puntosBuenos[j], puntosBuenos[k]), key = lambda v: (v.angulo((0,1)), abs(v))))
            t = triangle([puntosBuenos[x] for x in [i,j,k]])
            print("t:",t, "ijk:", [puntosBuenos[x] for x in [i,j,k]])
            if all(not x in t for x in puntosMalos):
                cantBuenos = sum(x in t for x in puntosBuenos) # puntos internos buenos
                triangulos[t] = cantBuenos + 1 # +1 porque contamos uno de los vertices del triangulo

# for k in triangulos:
#     triangulos[k].sort(key = lambda k: point((0,1)).angle(k[0][1] - k[0][0]))
    # for t in triangulos[k]
maximo = 0
for i in range(h):
    actual = puntosBuenos[i]
    vecinos = sorted(puntosBuenos[i+1:], key = lambda v : point((0,1)).angle(v - actual)) #ordeno los puntos de la derecha en sentido horario desde la vertical
    for j in range(len(vecinos)): #chequear estos rangos
        for k in range(j+1, len(vecinos)):
            t = triangle(actual, vecinos[j], vecinos[k])
            if t in triangulos:
# print(triangulos)
