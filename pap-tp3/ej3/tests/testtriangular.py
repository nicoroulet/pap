from sys import argv, stderr
from random import seed, randrange

seed(0)

c = int(argv[2])
a = int(argv[1])
q = int(argv[3])

print(c, a, q)

for i in range(a):
    print(* [i+1]*c)

for _ in range(q):
    c1 = randrange(c-1)+1
    a1 = randrange(a-1)+1
    c2 = randrange(c1, c)+1
    a2 = randrange(a1, a)+1
    print(c1, a1, c2, a2)

    s = (((c2*(c2+1))//2) - ((c1*(c1+1))//2)) * (a2 - a1)
    print(s, file=stderr)
