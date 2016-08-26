#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int>::iterator it;

int suma(it begin, it end, int64_t mask) {
    int s = 0;
    for (auto d = begin; d != end; ++d) {
        if (mask & (1 << (d - begin))) {
            s += *d;
        }
    }
    return s;
}

vector<int> soluciones(it begin, it end, int p) {
    vector<int> sol;
    for (int64_t i = 0; i < (1 << (end - begin)); i++) {
        int s = suma(begin, end, i);
        if (s <= p) {
            sol.push_back(s);
        }
    }
    return sol;
}

int main() {
    int p, n;
    cin >> p >> n;

    vector<int> ds(n);

    for (int& d : ds) cin >> d;

    auto sol1 = soluciones(ds.begin(), ds.begin() + n/2, p);
    auto sol2 = soluciones(ds.begin() + n/2, ds.end(), p);

    sort(sol1.begin(), sol1.end());
    sort(sol2.begin(), sol2.end());

    auto it1 = sol1.begin();
    auto it2 = sol2.rbegin();

    int max_sum = 0;

    while (it1 != sol1.end() && it2 != sol2.rend()) {
        int sum = (*it1) + (*it2);
        if (sum <= p) { // = p shortcut
            if (sum > max_sum) {
                max_sum = sum;
            }
            ++it1;
        } else {
            ++it2;
        }
    }

    cout << max_sum << endl;
}
