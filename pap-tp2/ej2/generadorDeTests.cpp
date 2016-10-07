#include <iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>



using namespace std;


int randomint(int min, int max){
	return min + (rand() % (int)(max - min));
}


void todosConTodosTodoElTiempo(int mina, int maxa, int mind, int maxd, char * nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);

	int a = randomint(mina, maxa);
	int d = randomint(mind, maxd);

	int posicionDeCruce = randomint(1, 100);
	
	input << a << " " << d << endl;
	for (int i = 0; i < a; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			input << posicionDeCruce << " ";
		}
		input << endl;
	}

	correctoutput << a << endl;
}

void todosConTodosEnUnDia(int mina, int maxa, int mind, int maxd, char * nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);

	int a = randomint(mina, maxa);
	int d = randomint(mind, maxd);

	int posicionDeCruce = randomint(1, 100);
	int diaDeCruce = randomint(1, d);
	
	input << a << " " << d << endl;
	for (int i = 0; i < a; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			if (j == diaDeCruce){
				input << posicionDeCruce << " "; 		 // este unico valor va a dar igual para todas las acciones
			}else{
				input << (posicionDeCruce + i+1) << " "; // estos valores dan distinto para cada accion
			}
		}
		input << endl;
	}

	correctoutput << a << endl;
}


void ningunoSeCruza(int mina, int maxa, int mind, int maxd, char * nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);

	int a = randomint(mina, maxa);
	int d = randomint(mind, maxd);

	int puntoRandom = randomint(1, 100);
	
	input << a << " " << d << endl;
	for (int i = 0; i < a; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			input << (puntoRandom + i) << " "; // estos valores dan distinto para cada accion
		}
		input << endl;
	}

	correctoutput << 1 << endl;
}

void unoCruzaTodos(int mina, int maxa, int mind, int maxd, char * nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);

	int a = randomint(mina, maxa);
	int d = randomint(mind, maxd);

	int puntoRandom = randomint(1, 100);
	
	input << a << " " << d << endl;
	for (int i = 0; i < a-1; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			input << (puntoRandom + i) << " "; // estos valores dan distinto para cada accion
		}
		input << endl;
	}

	// agrego el que cruza al resto
	for(int j = 0; j < d-1; ++j){
		input << (puntoRandom - 1 + j) << " "; // arranca abajo de todo, y va subiendo
	}

	input << (puntoRandom + a); // termina arriba de todo

	correctoutput << 2 << endl;
}

void unoCruzaTodosInverso(int mina, int maxa, int mind, int maxd, char * nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);

	int a = randomint(mina, maxa);
	int d = randomint(mind, maxd);

	int puntoRandom = randomint(1, 100);
	
	input << a << " " << d << endl;
	for (int i = 0; i < a-1; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			input << (puntoRandom + i) << " "; // estos valores dan distinto para cada accion
		}
		input << endl;
	}

	// agrego el que cruza al resto
	for(int j = d-1; j > 0; --j){
		input << (puntoRandom + a + j) << " "; // arranca arriba de todo, y va bajando
	}

	input << (puntoRandom - 2); // termina abajo de todo

	correctoutput << 2 << endl;
}


void cruceDeAPares(int mina, int maxa, int mind, int maxd, char * nameIn, char* nameOut){
	remove(nameIn);
	remove(nameOut);
	ofstream input(nameIn);
	ofstream correctoutput(nameOut);

	int a = randomint(mina, maxa);
	// lo hago par
	if (a%2 == 1){ a = a - 1; }
	int d = 100;

	int contador = 0;
	input << a << " " << d << endl;
	for (int i = 0; i < a/2; ++i)
	{
		for (int j = 0; j < d; ++j)
		{
			input << (contador + j) << " "; // sube desde contador hasta contador + 99
		}

		for (int j = d-1; j >= 0; --j)
		{
			input << (contador + j) << " "; // baja desde contador +99 hasta contador
		}

		input << endl;

		contador = contador + 120;
	}

	correctoutput << 2 << endl;
}


int main(){
	srand(time(NULL));

	// El caso en el que se crucen todas las acciones en todos los días. La respuesta correcta sería A.
	todosConTodosTodoElTiempo(900, 1000, 90, 100, "tests/testTodosConTodosTodoElTiempo.in", "tests/testTodosConTodosTodoElTiempoRes.out");

    // El caso en el que se crucen todas las acciones en algún día. La respuesta correcta sería A.
	todosConTodosEnUnDia(900, 1000, 90, 100, "tests/todosConTodosUnDia.in", "tests/todosConTodosUnDiaRes.out");

    // El caso en el que no se cruce ninguna acción en ningún día. La respuesta correcta sería 1.
	ningunoSeCruza(900, 1000, 90, 100, "tests/ningunoSeCruza.in", "tests/ningunoSeCruzaRes.out");

    // El mismo caso anterior, pero agregando una acción que comience abajo de todas las otras y termine arriba de todas las otras. La respuesta correcta sería 2.
	unoCruzaTodos(900, 1000, 90, 100, "tests/unoCruzaTodos.in", "tests/unoCruzaTodosRes.out");

    // El mismo caso anterior, sólo que la acción que cubre todo el gráfico comience arriba de todas las otras y termina abajo de todas las otras. La respuesta correcta seguiría siendo 2.
    unoCruzaTodosInverso(900, 1000, 90, 100, "tests/unoCruzaTodosInverso.in", "tests/unoCruzaTodosInversoRes.out");

    // El caso en el que se crucen de a pares. O sea, dados A cantidad par de acciones,
    // $\forall A_{i}$ (1 <= i <= A/2) $A_{2i}$ se cruza solamente con $A_{2i-1}$. El resultado correcto sería 2.
    cruceDeAPares(900, 1000, 90, 100, "tests/cruceDeAPares.in", "tests/cruceDeAParesRes.out");



	return 0;
}