class Trie:
  def __init__(self):
    self.hijos = {}
    self.nPalabras = 0
    self.esPR = False

root = Trie()
n = int(input())
res = 0
root.nPalabras = n
for _ in range(n):
  linea = input().strip().split()
  mail = linea[0]
  p = int(linea[1])
  actual = root
  for c in mail:
    if not c in actual.hijos:
      actual.hijos[c] = Trie()
    actual = actual.hijos[c]
    actual.nPalabras += 1
    p -= 1
    actual.esPR |= (p == 0)
    if actual.esPR:
      res = max(res, actual.nPalabras)

print(res)
