#include <iostream>
using namespace std;
int main() {
  int n, a, b;
  cin >> n >> a; // n es positivo
  int m = a;
  for(int i = 1; i < n; ++i) {
    cin >> b;
    a = max(0, a + b);
    m = max(m, a);
  }
  cout << m << endl;
  return 0;
}
