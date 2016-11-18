from math import sqrt

n = int(input())

p = None
ady = dict()

for _ in range(n-2):
    x1, y1, x2, y2, x3, y3 = (int(w) for w in input().split())

    v = min([(x1, y1), (x2, y2), (x3, y3)])
    if not p or v < p:
        p = v

    ady.setdefault((x1, y1), set()).update([(x2, y2), (x3, y3)])
    ady.setdefault((x2, y2), set()).update([(x1, y1), (x3, y3)])
    ady.setdefault((x3, y3), set()).update([(x1, y1), (x2, y2)])

def sign(x):
    return (x > 0) * 2 - 1

def norm(v):
    x, y = v
    return sqrt(x ** 2 + y ** 2)

def angulo(v, w):
    vx, vy = v
    wx, wy = w
    cos = (vx * wx + vy * wy) / (norm(v) * norm(w))
    sin = (vx * wy - vy * wx) / (norm(v) * norm(w))
    return cos * sign(sin) + sign(sin)

poli = [(p[0], p[1] + 1), p, p]

#print(poli[1:-1])
for i in range(n):
    v = poli[i]
    w = poli[i + 1]

    a = sorted(ady[w], key=lambda u: (angulo((v[0] - w[0], v[1] - w[1]), (u[0] - w[0], u[1] - w[1])), u[0], u[1]))
#    print("ady", w, ady[w])
    for j, u in enumerate(u for u in a if u != v):
        if poli[i + j + 2] == u: break
        poli.insert(i + j + 2, u)
#    print(poli[1:-1])

print(poli[1:-1])