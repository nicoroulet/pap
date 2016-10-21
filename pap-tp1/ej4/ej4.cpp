#include <iostream>
#include <vector>
#include <math.h>
#include "matriz.h"

using namespace std;

#define ith_bit(n, i) ((n >> i) & 1)

// descomponer toma un entero y devuelve su decomposicion en potencias de 2, de menor a mayor
vector<int> descomponer(int n){
  vector<int> res;
  int logi = 0;
  for(int i = 1; i <= n; i <<= 1, ++logi) {
    if (n & i){
      res.push_back(logi);
    }
  }
  return res;
}

Matriz obtener_o_calcular_P(int i, int j, vector<vector<Matriz> > & P){
  if (P[i][j].valid) {
    return P[i][j];
  } else {
    return P[i][j] = obtener_o_calcular_P(i-1, j, P) * obtener_o_calcular_P(i-1, j + (1<<(i-1)), P);
  }
}

int main(){
  int n, l;
  Matriz m;
  cin >> n >> l;
  cin >> m;
  int logl = (int) log2(l) + 1;
  vector<vector<Matriz> > P = vector<vector<Matriz> >(logl); // P es la parte inferior de una piramide
  // las Matrices por default tienen valid = false
  for(int i = 0; i < P.size(); ++i) {
    P[i] = vector<Matriz>(n - (1 << i) + 1); // la base de la piramide es P[0]
  }

  for(int i = 0; i < n; ++i) {
    cin >> P[0][i];
  }

  vector<int> lDescompuesto = descomponer(l);   // los productos a buscar

  for(int i = 0; i <= n-l; ++i) {
    int partialsum = 0;
    Matriz acum = id();
    for(int j = 0; j < lDescompuesto.size(); ++j){
      acum *= obtener_o_calcular_P(lDescompuesto[j], i + partialsum, P);
      // P[j][partialsum+i] = ;
      partialsum += (1 << lDescompuesto[j]);
    }
    if (acum == m){
      cout << "SI" << endl;
      return 0;
    }
  }
  cout << "NO" << endl;
  return 0;
}
