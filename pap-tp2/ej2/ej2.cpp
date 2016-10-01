#include <iostream>
#include <vector>
#include <cassert>

#define DBG(x) cerr << #x << " = " << (x) << endl

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


	return 0;
}
