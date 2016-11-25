class Node:
    def __init__(self, data, next):
        self.data = data
        self.next = next

    def insert(self, x):
        node = Node(x, self.next)
        self.next = node

    def print(self, n):
        aux = self
        l = []
        for i in range(n):
            l.append(str("%d %d" % aux.data))
            aux = aux.next
        print(" ".join(l))


class Llist:
    def __init__(self, xs):
        self.first = Node(xs[0], None)
        aux = self.first
        for x in xs[1:]:
            aux.next = Node(x, None)
            aux = aux.next

    def toList(self):
        aux = self.first
        l = []
        while aux != None:
            l.append(aux.data)
            aux = aux.next
        return l
