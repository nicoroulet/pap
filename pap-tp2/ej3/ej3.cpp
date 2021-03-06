#include <iostream>
#include <vector>
#include <array>
#include <functional>

using namespace std;

typedef int ver;
typedef array<ver, 2> eje;

struct motor {
    int n, m;
    const vector<vector<ver> >& ady;

    vector<vector<bool> > es_puente;
    vector<int*> vecinitos;
    vector<int> vecindades;

    motor(int n, int m, const vector<vector<ver> >& ady)
        : n(n), m(m), ady(ady), es_puente(n, vector<bool>(n, false)), vecinitos(n, nullptr)
    {
        { // puentes
            vector<int> depth(n, -1);
            vector<int> low(n);

            function<void(ver, ver, int)> dfs_puentes = [&] (ver v, ver p, int d) {
                depth.at(v) = d;
                low.at(v) = d;

                for (ver w : ady.at(v)) if (w != p) {
                    if (depth.at(w) == -1) {
                        dfs_puentes(w, v, d+1);
                        low.at(v) = min(low.at(v), low.at(w));
                        if (low.at(w) >= depth.at(w)) {
                            es_puente.at(v).at(w) = true;
                            es_puente.at(w).at(v) = true;
                        }
                    } else if (depth.at(w) < depth.at(v)) {
                        low.at(v) = min(low.at(v), depth.at(w));
                    }
                }
            };

            dfs_puentes(0, 0, 0);
        }

        { // vecinitos (precálculo query C)
            vecindades.reserve(n);
            vector<bool> visitado(n, false);

            function<void(ver)> dfs_vecinitos = [&] (ver v) {
                visitado.at(v) = true;

                if (vecinitos.at(v) == nullptr) {
                    vecindades.push_back(0);
                    vecinitos.at(v) = &vecindades.back();
                }

                *vecinitos.at(v) += 1;

                for (ver w : ady.at(v)) if (!visitado.at(w)) {
                    if (!es_puente.at(v).at(w)) vecinitos.at(w) = vecinitos.at(v);
                    dfs_vecinitos(w);
                }
            };

            dfs_vecinitos(0);
        }
    }

    int resolver_a(const ver v1, const ver v2) {
        int res = 0;
        vector<bool> visitado(n, false);

        // contar puentes en un camino cualquiera entre v1 y v2

        function<bool(ver)> dfs_camino = [&] (ver w1) -> bool {
            visitado.at(w1) = true;
            for (ver w2 : ady.at(w1)) if (!visitado.at(w2)) {
                if (w2 == v2 || dfs_camino(w2)) {
                    res += es_puente.at(w1).at(w2);
                    return true;
                }
            }
            return false;
        };

        dfs_camino(v1);

        return res;
    }

    int resolver_b(const eje e) {
        // ver si eje es puente
        return es_puente.at(e.at(0)).at(e.at(1));
    }

    int resolver_c(ver v) {
        return *vecinitos.at(v) - 1;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<eje> calles(m);
    vector<vector<ver> > ady(n);
    for (int i = 0; i < m; ++i) {
        int j1, j2;
        cin >> j1 >> j2;
        j1 -= 1; j2 -= 1;
        ady.at(j1).push_back(j2);
        ady.at(j2).push_back(j1);
        calles.at(i) = {j1, j2};
    }

    motor bct(n, m, ady);

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        char tipo_query;
        cin >> tipo_query;

        if (tipo_query == 'A') {
            int j1, j2;
            cin >> j1 >> j2;
            j1 -= 1; j2 -= 1;
            cout << bct.resolver_a(j1, j2) << endl;
        }

        if (tipo_query == 'B') {
            int c;
            cin >> c;
            c -= 1;
            cout << bct.resolver_b(calles.at(c)) << endl;
        }

        if (tipo_query == 'C') {
            int j;
            cin >> j;
            j -= 1;
            cout << bct.resolver_c(j) << endl;
        }
    }
}
