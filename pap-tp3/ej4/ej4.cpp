#include <vector>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

pair<int,int> mejores(pair<int,int> p1, pair<int,int>p2) {
	pair<int,int> res;
	if (p1.first >= p2.first) {
		res.first = p1.first;
		res.second = max(p1.second, p2.first);
	} else {
		res.first = p2.first;
		res.second = max(p2.second, p1.first);
	}
	return res;
}


int main() {
	int d, r;
	cin >> d >> r;
	int k = 31 - __builtin_clz(d);
	int dd = (1 << k);
	// cout << dd << endl;		// armamos un heap
	vector<pair<int,int> > e(2*dd, make_pair(0,0)); // armamos un heap de tamaño suficiente.
	// dd es donde arranca la última fila del heap. en dd+i el iésimo elemento del arreglo  (0 < i < d-1)

	// inicializamos el heap. el fin tiene todos ceros.
	int aux;
	for (int i = dd; i < dd+d; ++i) {
		cin >> aux;
		e[i] = make_pair(aux,0);
	}
	// calculamos los máximos por encima.
	for (int i = dd-1; i>=1; --i) {
		e[i] = mejores(e[2*i], e[2*i+1]);
	}
	//cout << e[1].first << " " << e[1].second << endl;
	int p,u;
	for (int i = 0; i < r; ++i) {
		cin >> p >> u;
		// TODO: resolver recursivamente. cout << res ;)
	}

	return 0;
}