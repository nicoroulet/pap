from sys import argv

ns = list(map(int, argv[1:]))
k = len(ns)

N = sum(ns)
M = sum(ns) + k - 1

print(N, M)

for i, n in enumerate(ns):
    for e in range(n):
        p = sum(ns[:i])
        e1, e2 = e, (e + 1) % n
        print(1+ p + e1, 1 + p + e2)

for i, n in enumerate(ns[:-1]):
    p = sum(ns[:i])
    print(1 + p, 1 + p + n)

print(N*N + M + N)

for e1 in range(N):
    for e2 in range(N):
        print("A {} {}".format(e1 + 1, e2 + 1))

for c in range(M):
    print("B {}".format(c + 1))

for e1 in range(N):
    print("C {}".format(e1 + 1))
