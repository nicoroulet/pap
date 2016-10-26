#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <queue>


using namespace std;

int64_t randomint64_t(int64_t min, int64_t max){
	return min + (rand() % (int64_t)(max - min));
}

char randomLetra(){
	if (rand() % 2){
		// mayuscula
		return 65 + (rand() % (char)(90-65));
	}else{
		// minuscula
		return 97 + (rand() % (char)(122-97));
	}
}

void testAmbosIguales(uint64_t minn, uint64_t maxn, char* nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);
	// caso en que el apodo es igual al nombre
	int64_t n = randomint64_t(minn, maxn);
	queue<char> q;
	for (int64_t i = 0; i < n; ++i) {
		char letra = randomLetra();
		q.push(letra);
		input << letra;
	}
	input << endl;
	for (int64_t i = 0; i < n; ++i) {
		input << q.front();
		q.pop();
	}
	input << endl;
	correctoutput << "S" << endl;
}

void testApodoPrefijo(uint64_t minn, uint64_t maxn, char* nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);
	// caso en que el apodo es prefijo del nombre
	int64_t n = randomint64_t(minn, maxn);
	int64_t finDelPrefijo = randomint64_t(1, (n-1));
	queue<char> q;
	for (int64_t i = 0; i < finDelPrefijo; ++i) {
		char letra = randomLetra();
		q.push(letra);
		input << letra;
	}
	for(int64_t i = finDelPrefijo; i < n; ++i){
		char letra = randomLetra();
		input << letra;
	}
	input << endl;
	while(!q.empty()){
		input << q.front();
		q.pop();
	}
	input << endl;
	correctoutput << "S" << endl;
}

void testApodoSufijo(uint64_t minn, uint64_t maxn, char* nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);
	// caso en que el apodo es prefijo del nombre
	int64_t n = randomint64_t(minn, maxn);
	int64_t comienzoDelSufijo = randomint64_t(1, (n-1));
	queue<char> q;
	for (int64_t i = 0; i < comienzoDelSufijo; ++i) {
		char letra = randomLetra();
		input << letra;
	}
	for(int64_t i = comienzoDelSufijo; i < n; ++i){
		char letra = randomLetra();
		q.push(letra);
		input << letra;
	}
	input << endl;
	while (!q.empty()){
		input << q.front();
		q.pop();
	}
	input << endl;
	correctoutput << "S" << endl;
}

void testApodoEnMedio(uint64_t minn, uint64_t maxn, char* nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);
	// caso en que el apodo es prefijo del nombre
	int64_t n = randomint64_t(minn, maxn);
	int64_t comienzo = randomint64_t(1, (n-1));
	int64_t final = randomint64_t(comienzo, (n-1));

	queue<char> q;
	for (int64_t i = 0; i < comienzo; ++i) {
		char letra = randomLetra();
		input << letra;
	}
	for(int64_t i = comienzo; i < final; ++i){
		char letra = randomLetra();
		q.push(letra);
		input << letra;
	}
	for(int64_t i = final; i < n; ++i){
		char letra = randomLetra();
		input << letra;
	}

	input << endl;
	while (!q.empty()){
		input << q.front();
		q.pop();
	}
	input << endl;
	correctoutput << "S" << endl;
}


int main(){
	srand(time(NULL));

	testAmbosIguales(99000, 100000, "tests/ambosIguales1.test", "tests/ambosIguales1.test.res");
	testAmbosIguales(99000, 100000, "tests/ambosIguales2.test", "tests/ambosIguales2.test.res");
	testAmbosIguales(99000, 100000, "tests/ambosIguales3.test", "tests/ambosIguales3.test.res");
	testAmbosIguales(99000, 100000, "tests/ambosIguales4.test", "tests/ambosIguales4.test.res");

	testApodoPrefijo(99000, 100000, "tests/apodoPrefijo1.test", "tests/apodoPrefijo1.test.res");	
	testApodoPrefijo(99000, 100000, "tests/apodoPrefijo2.test", "tests/apodoPrefijo2.test.res");	
	testApodoPrefijo(99000, 100000, "tests/apodoPrefijo3.test", "tests/apodoPrefijo3.test.res");	
	testApodoPrefijo(99000, 100000, "tests/apodoPrefijo4.test", "tests/apodoPrefijo4.test.res");	

	testApodoSufijo(99000, 100000, "tests/apodoSufijo1.test", "tests/apodoSufijo1.test.res");	
	testApodoSufijo(99000, 100000, "tests/apodoSufijo2.test", "tests/apodoSufijo2.test.res");	
	testApodoSufijo(99000, 100000, "tests/apodoSufijo3.test", "tests/apodoSufijo3.test.res");	
	testApodoSufijo(99000, 100000, "tests/apodoSufijo4.test", "tests/apodoSufijo4.test.res");	

	testApodoSufijo(99000, 100000, "tests/apodoEnMedio1.test", "tests/apodoEnMedio1.test.res");
	testApodoSufijo(99000, 100000, "tests/apodoEnMedio2.test", "tests/apodoEnMedio2.test.res");
	testApodoSufijo(99000, 100000, "tests/apodoEnMedio3.test", "tests/apodoEnMedio3.test.res");
	testApodoSufijo(99000, 100000, "tests/apodoEnMedio4.test", "tests/apodoEnMedio4.test.res");



	return 0;
}