from math import sqrt, atan2, pi
from Llist import *

class point(tuple):
    def __add__(self, other):
        return point(s + o for s, o in zip(self, other))
    def __sub__(self, other):
        return point(s - o for s, o in zip(self, other))
    def __abs__(self):
        return sqrt(sum(s ** 2 for s in self))
    def angle(self, other):
        s = atan2(*reversed(self))
        o = atan2(*reversed(other))
        return (s - o) % (2 * pi)

n = int(input())

p = None
ady = dict()

for _ in range(n-2):
    x1, y1, x2, y2, x3, y3 = map(int, input().split())
    v1, v2, v3 = map(point, [(x1, y1), (x2, y2), (x3, y3)])

    v = min([v1, v2, v3])
    if not p or v < p:
        p = v

    ady.setdefault(v1, set()).update([v2, v3])
    ady.setdefault(v2, set()).update([v1, v3])
    ady.setdefault(v3, set()).update([v1, v2])

poly = Llist([p + (0, 1), p, p])

it = poly.first
for i in range(n):
    v = it.data
    w = it.next.data
    a = sorted(ady[w], key=lambda u: ((v - w).angle(u - w), u[0], u[1]))
    auxIt = it
    for u in (u for u in a if u != v):
        if auxIt.next.next.data == u: break
        auxIt.next.insert(u)
        auxIt = auxIt.next
    it = it.next

poly.first.next.print(n)
