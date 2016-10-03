#include <iostream>
#include <vector>
#include <list>
#include <cassert>

#define DBG(x) cerr << #x << " = " << (x) << endl
#define source (0)
#define sink (1)
#define in(i) (2*(i))
#define out(i) (2*(i)+1)


using namespace std;

bool menor(vector<int> &v1, vector<int> &v2){
	// llamame con dos vectores del mismo tamaño man
	assert(v1.size() == v2.size());

	for (int i = 0; i < v1.size(); ++i) {
		if (v1[i] >= v2[i]) {
			return false;
		}
	return true;
	}
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

	// Armo el grafo. {out(i) -> in(j)} sii {acción i < acción j}.
	// Reviso todos los pares de acciones A^2, y los comparo en O(D). --> A^2 \times D

	vector<list<int> > grafo(2 * a + 2); // la posicion 2*i es in(i), 2*i+1 es out(i). 0 es source, 1 es sink
	for (int i = 0; i < a; ++i) {
		grafo[source].push_back(in(i));
		grafo[out(i)].push_back(sink);
		for (int j = 0; j < a; ++j) {
			if menor(acciones[i], acciones[j]){
				grafo[out(i)].push_back(in(j));
			}
		}
	}

	// por König, hay que encontrar el tamaño m de un matching máximo en el grafo armado. Luego, A-m será el número buscado
	// Flujo!

	m = matching(grafo);
	cout << a-m << endl;

	return 0;
}
