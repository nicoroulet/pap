#include <iostream>
using namespace std;
int main() {
  int n, b, a = 0, m = 0;
  cin >> n; // n es positivo
  for(int i = 0; i < n; ++i) {
    cin >> b;
    a = max(0, a + b);
    m = max(m, a);
  }
  cout << m << endl;
  return 0;
}
