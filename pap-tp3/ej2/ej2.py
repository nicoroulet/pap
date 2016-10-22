class Trie:
  def __init__(self):
    self.childs = {}
    self.nWords = 0
    self.isMemoryTop = False

root = Trie()
n = int(raw_input())
res = 0
root.nWords = n
for _ in range(n):
  linea = raw_input().strip().split()
  mail = linea[0]
  p = int(linea[1])
  current = root
  for c in mail:
    if not c in current.childs:
      current.childs[c] = Trie()
    current = current.childs[c]
    current.nWords += 1
    p -= 1
    current.isMemoryTop |= (p == 0)
    if current.isMemoryTop:
      res = max(res, current.nWords)

print res
