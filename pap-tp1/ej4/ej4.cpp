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

Matriz gimme(int i, int j, vector<vector<Matriz> > & pi){
  if (pi[i][j].valid) {
    return pi[i][j];
  } else {
    return pi[i][j] = gimme(i-1, j, pi) * gimme(i-1, j + (1<<(i-1)), pi);
  }
}

int main(){
  int n, l;
  Matriz m;
  cin >> n >> l;
  int logl = (int) log2(l) + 1;
  vector<vector<Matriz> > pi = vector<vector<Matriz> >(logl); // pi es la parte inferior de una piramide
  // las Matrices por default tienen valid = false
  for(int i = 0; i < pi.size(); ++i) {
    pi[i] = vector<Matriz>(n - (1 << i) + 1); // la base de la piramide es pi[0]
  }

  vector<int> lDescompuesto = descomponer(l);   // los productos a buscar

  for(int i = 0; i <= n-l; ++i) {
    int partialsum = 0;
    Matriz acum = id();
    for(int j = 0; j < lDescompuesto.size(); ++j){
      acum *= gimme(lDescompuesto[j], i + partialsum, pi);
      // pi[j][partialsum+i] = ;
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
