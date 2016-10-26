c, a, q = (int(w) for w in input().split())

M = []
for _ in range(c):
    M.append(list(int(w) for w in input().split()))

S = [[0] * (a+1) for _ in range(c+1)]

for i in range(c):
    for j in range(a):
        S[i+1][j+1] = M[i][j] + S[i][j+1] + S[i+1][j] - S[i][j] 

def query(c1, a1, c2, a2):
    return S[c2][a2] - S[c1][a2] - S[c2][a1] + S[c1][a1]

for _ in range(q):
    q0 = (int(w) for w in input().split())
    print(query(*q0))
