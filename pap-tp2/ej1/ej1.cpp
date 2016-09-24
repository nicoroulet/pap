#include <iostream>
#include <vector>
#include <queue>
#include <list>

#define source (0)
#define sink (1)
#define in(i) (2*(i))
#define out(i) (2*(i)+1)

using namespace std;

int bfs(int s, int t, vector<list<int> > & grafo) {
  // el grafo va a ser la red residual
  vector<int> padre(grafo.size(), -1); // guarda el padre de cada nodo en el bfs. No visitado = -1, padre de s = -2
  vector<list<int>::iterator> itEnPadre(grafo.size()); // el iterador al eje del grafo que va del padre al nodo
  padre[s] = -2;
  queue<int> q;
  q.push(s);
  bool hayCamino = false;
  while(!q.empty()) {
    int nodoActual = q.front();
    q.pop();
    for (auto vecino = grafo[nodoActual].begin(); vecino != grafo[nodoActual].end(); ++vecino) {
      if (padre[*vecino] == -1) {
        padre[*vecino] = nodoActual;
        itEnPadre[*vecino] = vecino;
        q.push(*vecino);
      }
      if (*vecino == t) {
        q = queue<int>();
        hayCamino = true;
        break;
      }
    }
  }
  if (!hayCamino)
    return 0;
  // como todos los pesos son 1, al usar un eje, lo invierto en la red residual
  for (int n = t; n != s; n = padre[n]) {
    grafo[n].push_back(padre[n]);
    grafo[padre[n]].erase(itEnPadre[n]);
  }
  return 1;
}

int fordFulkerson(int s, int t, vector<list<int> > & grafo) { // ejes con peso 1
  // vector<vector<int> > capacidades(n, vector<int>(n, 1)); //matriz de unos con las capacidades de cada eje (el flujo es 1-capacidad)
  int flujo = 0;
  int m = bfs(s, t, grafo); // tomo el camino de aumento mas corto, actualizando capacidades (pongo en 0 los caminos usados)
  while (m != 0) {
    ++flujo;
    m = bfs(s, t, grafo);
  }
  return flujo;
}


int main() {
  int n, m;
  cin >> n >> m;
  vector<list<int> > grafo(2 * n + 2); // la posicion 2*i es in(i), 2*i+1 es out(i). 0 es source, 1 es sink
  for (int i = 1; i <= n; ++i)
  {
    char tipoDeNodo;
    cin >> tipoDeNodo;
    if (tipoDeNodo == 'A') {
      grafo[source].push_back(in(i));
    }
    if (tipoDeNodo == 'E') {
      grafo[out(i)].push_back(sink);
    }
    grafo[in(i)].push_back(out(i));
  }

  for (int i = 0; i < m; ++i)
  {
    int v1, v2;
    cin >> v1 >> v2;
    grafo[out(v1)].push_back(in(v2));
    grafo[out(v2)].push_back(in(v1));
  }
  int res = fordFulkerson(0, 1, grafo);
  cout << res << endl;
}
