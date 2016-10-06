#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>



using namespace std;

int64_t randomint64_t(int64_t min, int64_t max){
	return min + (rand() % (int64_t)(max - min));
}

void testLista(int64_t minn, int64_t maxn, int64_t minm, int64_t maxm, int64_t minq, int64_t maxq, char* nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);
	// caso lista enlazada, y queries random. todas deberian ser N, salvo que sean el mismo nodo.
	int64_t n = randomint64_t(minn, maxn);
	int64_t q = randomint64_t(minq, maxq);

	input << n << " " << n-1 << endl;
	for (int64_t i = 1; i < n; ++i) {
		input << i << " " << i+1 << endl;
	}
	input << q << endl;
	for (int64_t i = 0; i < q; ++i) {
		int64_t a = randomint64_t(1, n);
		int64_t b = randomint64_t(1, n);
		input << a << " " << b << endl;
		if (a == b){
			correctoutput << "S" << endl;
		}else{
			correctoutput << "N" << endl;
		}
	}
}

bool hayMultiploMayor(int64_t x, int64_t n, int tamanioComp){
	// devuelve true sii hay algun y >= x TQ y%tamanioComp == 0 && y <=n
	// o sea, devuelve false sii x esta al final de la lista, y su SCC consiste en solamente el
	if (x % tamanioComp == 0){
		return true;
	}
	if (((x/tamanioComp)+1)*tamanioComp <= n){
		return true;
	}else{
		return false;
	}
}

void testListadeSCC(int64_t minn, int64_t maxn, int64_t minm, int64_t maxm, int64_t minq, int64_t maxq, int tamanioComp, char* nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);
	// caso lista enlazada, con un eje desde todos los nodos i%tamanioComp == 0 hacia i-2
	// las queries deberian ser S sii div(j-1, tamanioComp) == div(i-1,tamanioComp)
	// donde div es division entera
	int64_t n = randomint64_t(minn, maxn);
	int64_t q = randomint64_t(minq, maxq);

	input << n << " " << (n-1) + (n/ tamanioComp) << endl;

	// armo la lista
	for (int64_t i = 1; i < n; ++i) {
		input << i << " " << i+1 << endl;
	}

	// tiro ejes desde cada i%tamanioComp == 0 hasta i-(tamanioComp-1)
	for(int64_t i = tamanioComp; i < n; i = i + tamanioComp){
		input << i << " " << i-(tamanioComp-1) << endl;
	}

	input << q << endl;
	for (int64_t i = 0; i < q; ++i) {
		int64_t a = randomint64_t(1, n);
		int64_t b = randomint64_t(1, n);
		input << a << " " << b << endl;

		if ((a-1)/tamanioComp == (b-1)/tamanioComp && hayMultiploMayor(a, n, tamanioComp) && hayMultiploMayor(b,n, tamanioComp) || a == b){
			correctoutput << "S" << endl;
		}else{
			correctoutput << "N" << endl;
		}
	}

}

void testClique(int64_t minn, int64_t maxn, int64_t minm, int64_t maxm, int64_t minq, int64_t maxq, char* nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);
	// caso clique/grafo completo y queries random. todas deberian ser S
	int64_t n = randomint64_t(minn, maxn);
	int64_t q = randomint64_t(minq, maxq);
	int64_t m = n*(n-1);
	input << n << " " << m << endl;
	for (int64_t i = 1; i < n; ++i) {
		for (int64_t j = i; j < n; ++j) {
			input << i << " " << j << endl;
			input << j << " " << i << endl;
		}
	}
	input << q << endl;
	for (int64_t i = 0; i < q; ++i) {
		int64_t a = randomint64_t(1, n);
		int64_t b = randomint64_t(1, n);
		input << a << " " << b << endl;
		correctoutput << "S" << endl;
	}
}


int main(){
	srand(time(NULL));


	// en estos casos no usamos minm ni maxm porque dependen de n, pero los dejamos por si surgen futuras modificaciones
	testLista(9000, 10000, 1, 1, 99000, 100000, "tests/lista.in", "tests/listares.out");

	testListadeSCC(9000, 10000, 1, 1, 99000, 100000, 3, "tests/listadescc3.in", "tests/listadescc3res.out");
	testListadeSCC(9000, 10000, 1, 1, 99000, 100000, 10, "tests/listadescc10.in", "tests/listadescc10res.out");
	testListadeSCC(9000, 10000, 1, 1, 99000, 100000, 50, "tests/listadescc50.in", "tests/listadescc50res.out");
	testListadeSCC(9000, 10000, 1, 1, 99000, 100000, 100, "tests/listadescc100.in", "tests/listadescc100res.out");
	testListadeSCC(9000, 10000, 1, 1, 99000, 100000, 500, "tests/listadescc500.in", "tests/listadescc500res.out");
	testListadeSCC(9000, 10000, 1, 1, 99000, 100000, 1000, "tests/listadescc1000.in", "tests/listadescc1000res.out");

	testClique(90, 100, 1, 1, 99000, 100000, "tests/clique.in", "tests/cliqueres.out");



	return 0;
}