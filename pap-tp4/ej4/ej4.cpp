#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

int gcd(int a, int b){
	int menosdos = a;
	int menosuno = b;
	int aux;
	while(menosuno != 0){
		aux = menosdos % menosuno;
		menosdos = menosuno;
		menosuno = aux;
	}
	return menosdos;
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
		v[i]--;
	}

	// armado de ciclos
	vector<int> ciclesizes;
	int tamanioCiclo, actual;
	vector<bool> visitados(n, false);
	for (int i = 0; i < n; ++i) {
		//cout << "recorro el " << i << endl;
		if(!visitados[i]){
			// empiezo a ciclar
			tamanioCiclo = 1;
			visitados[i] = true;
			actual = v[i];
			//cout << "Armando ciclo... " << endl;
			//cout << i << " -> " << actual << endl;
			while(actual != i){
				//cout << actual << " -> " << v[actual] << endl;
				// ciclamos
				tamanioCiclo++;
				visitados[actual] = true;
				actual = v[actual];
			}

			// si el ciclo es par, devolvemos cero
			if (tamanioCiclo % 2 == 0){
				//cout << "hay un ciclo par" << endl;
				cout << 0 << endl;
				return 0;
			}else{
				ciclesizes.push_back(tamanioCiclo);
			}
		}
	}
	int res = 1;
	int s = ciclesizes.size();
	for (int i = 0; i < s; ++i) {
		if (ciclesizes[i]>1) {
			res *= pow(2,(ciclesizes[i]/2));
			res = res % 1000000007;
		}
		for (int j = i+1; j < s; ++j) {
			res = (res << gcd(ciclesizes[i], ciclesizes[j])) % 1000000007;

			//cout << "i " << i << " j " << j << " gcd " << gcd(ciclesizes[i], ciclesizes[j]) << endl;
		}
	}
	cout << res << endl;

	return 0;
}