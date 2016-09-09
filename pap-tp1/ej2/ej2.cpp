#include <vector>
#include <iostream>

using namespace std;

vector<int> div_una;

vector<int> div_fiesta(int n, vector<vector<int> > d) {
    vector<int> div_una(1<<n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int ij = (1 << i) | (1 << j);
            div_una[ij] = d[i][j];
            int mask = ((1 << n) - 1) ^ ij;
            for (int k = mask; k != 0; k = mask & (k-1)) {
                div_una[k | ij] += d[i][j];
            }
        }
    }

    return div_una;
}

int maximizar_diversion_total(int n, vector<int>& div_tot, int mask) {
    if (div_tot[mask] != - 1) {
        return div_tot[mask];
    }

    int res = 0;

    for (int i = mask; i != 0; i = mask & (i-1)) {
        res = max(res, maximizar_diversion_total(n, div_tot, mask ^ i) + div_una[i]);
    }

    div_tot[mask] = res;

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

    div_una = div_fiesta(n, d);

    vector<int> div_tot(1<<n, -1);
    div_tot[0] = 0;

    int res = maximizar_diversion_total(n, div_tot, (1<<n) - 1);

    cout << res << endl;

    return 0;
}
