#include <iostream>
#include <vector>

#define source (0)
#define sink (1)
#define in(i) (2*(i))
#define out(i) (2*(i)+1)

using namespace std;

int fordFulkerson(int s, int t, vector<vector<int> > & grafo) { // ejes con peso 1
  // vector<vector<int> > capacidades(n, vector<int>(n, 1)); //matriz de unos con las capacidades de cada eje (el flujo es 1-capacidad)
  // while (1) {
  //   int m = bfs(grafo, capacidades); // tomo el camino de aumento mas corto, actualizando capacidades (pongo en 0 los caminos usados)


  // }
  return 124;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > grafo(2 * n + 2); // la posicion 2*i es in(i), 2*i+1 es out(i). 0 es source, 1 es sink
  for (int i = 0; i < n; ++i)
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

}
