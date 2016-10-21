#include <vector>
#include <iostream>

using namespace std;

vector<int> diversion_fiesta;

void calcular_diversion_fiestas(int n, vector<vector<int> > d) {
    diversion_fiesta = vector<int>(1<<n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int ij = (1 << i) | (1 << j);
            diversion_fiesta[ij] = d[i][j];
            int mask = ((1 << n) - 1) ^ ij;
            for (int k = mask; k != 0; k = mask & (k-1)) {
                diversion_fiesta[k | ij] += d[i][j];
            }
        }
    }
}

int maximizar_diversion_total(int n, vector<int>& diversion_subcjto, int mask) {
    if (diversion_subcjto[mask] != - 1) {
        return diversion_subcjto[mask];
    }

    int res = 0;
    int k = 31 - __builtin_clz(mask);
    int tope = 1 << k;

    for (int i = mask; i >= tope; i = mask & (i-1)) { // usar i > tope asegura iterar solo sobre los subconjuntos que contienen a la primer amiga.
        // luego, cada combinación es iterada una sola vez. 
        res = max(res, maximizar_diversion_total(n, diversion_subcjto, mask ^ i) + diversion_fiesta[i]);
    }

    diversion_subcjto[mask] = res;

    return res;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int> > d(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> d[i][j];
        }
    }

    calcular_diversion_fiestas(n, d);

    vector<int> diversion_subcjto(1<<n, -1);
    diversion_subcjto[0] = 0;

    int res = maximizar_diversion_total(n, diversion_subcjto, (1<<n) - 1);

    cout << res << endl;

    return 0;
}
