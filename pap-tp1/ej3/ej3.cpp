#include <iostream>

using namespace std;

int main() {
  int n;
  int64_t b, a = 0, m = 0;

  cin >> n; // n es positivo

  for(int i = 0; i < n; ++i) {
    cin >> b;
    a = max((int64_t)0, a + b);
    m = max(m, a);
  }

  cout << m << endl;

  return 0;
}
