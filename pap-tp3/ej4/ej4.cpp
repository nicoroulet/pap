#include <vector>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

pair<int,int> id(){
	return make_pair(0,0);
}

pair<int,int> mejores(pair<int,int> p1, pair<int,int>p2) {
	pair<int,int> res = id();
	if (p1.first >= p2.first) {
		res.first = p1.first;
		res.second = max(p1.second, p2.first);
	} else {
		res.first = p2.first;
		res.second = max(p2.second, p1.first);
	}
	return res;
}

pair<int,int> query(vector<pair<int,int> > &e, int left, int right, int i, int j, int k){
	// quiero resolver la query [left, right). Le estoy preguntando al elemento del vector que guarda [i,j).
	// k es el índice en el vector que tiene al [i,j)
	if (left <= i && j <= right) {
		// i,j contiene al que estoy pidiendo
		return e[k];
	} else if (j <= left || i >= right) {
		// i,j es disjunto al rango pedido
		return id();
	} else {
		// parte dentro parte afuera. Divido y tomo mejores dos de ambos lados:
		return mejores(query(e,left,right, i, (i+j)/2, 2*k), query(e, left, right, (i+j)/2, j, 2*k+1));
	}
}


int main() {
	int d, r;
	cin >> d >> r;
	int k = 31 - __builtin_clz(d);
	int dd = (1 << (k+1));
	vector<pair<int,int> > e(2*dd, id()); // armamos un heap de tamaño suficiente.
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

	// leemos pedidos:
	vector<pair<int,int> > pedidos(r);
	int p,u;
	for (int i = 0; i < r; ++i) {
		cin >> p >> u;
		pedidos[i] = make_pair(p,u);
	}

	pair<int,int> res = id();
	for (int i = 0; i < r; ++i) {
		p = pedidos[i].first;
		u = pedidos[i].second;
		res = query(e, p, u, 0, dd, 1);
		cout << res.first + res.second << endl;
	}
	return 0;
}