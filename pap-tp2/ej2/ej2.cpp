#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <cassert>

#define DBG(x) cerr << #x << " = " << (x) << endl
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

int edmondsKarp(int s, int t, vector<list<int> > & grafo) { // ejes con peso 1
	// vector<vector<int> > capacidades(n, vector<int>(n, 1)); //matriz de unos con las capacidades de cada eje (el flujo es 1-capacidad)
	int flujo = 0;
	int m = bfs(s, t, grafo); // tomo el camino de aumento mas corto, actualizando capacidades (pongo en 0 los caminos usados)
	while (m != 0) {
		++flujo;
		m = bfs(s, t, grafo);
	}
	return flujo;
}


bool menor(vector<int> &v1, vector<int> &v2){
	// llamame con dos vectores del mismo tamaño man
	assert(v1.size() == v2.size());

	for (int i = 0; i < v1.size(); ++i) {
		if (v1[i] >= v2[i]) {
			return false;
		}
	}
	return true;
}

int comp(vector<int> &v1, vector<int> &v2){
	// 0 si es menor, 1 si es mayor, -1 si no son comparables (se cruzan)
	if (menor(v1,v2)) return 0;
	if (menor(v2,v1)) return 1;
	return -1;
}


int main(){
	int a, d;
	// a acciones, durante d días.
	cin >> a >> d;
	vector<vector<int> > acciones(a, vector<int>(d));

	// leo todo
	for (int i = 0; i < a; ++i) {
		for (int j = 0; j < d; ++j) {
			cin >> acciones[i][j];
		}
	}

	// Armo el grafo. {in(i) -> out(j)} sii {acción i < acción j}.
	// Reviso todos los pares de acciones A^2, y los comparo en O(D). --> A^2 \times D

	vector<list<int> > grafo(2 * a + 2); // la posicion 2*i es in(i), 2*i+1 es out(i). 0 es source, 1 es sink
	for (int i = 0; i < a; ++i) {
		grafo[source].push_back(in(i));
		grafo[out(i)].push_back(sink);
		for (int j = 0; j < a; ++j) {
			if (menor(acciones[i], acciones[j])){
				grafo[in(i)].push_back(out(j));
			}
		}
	}

	// por König, hay que encontrar el tamaño m de un matching máximo en el grafo armado. Luego, A-m será el número buscado
	// Flujo!

	int m = edmondsKarp(source, sink, grafo);
	cout << a-m << endl;

	return 0;
}
