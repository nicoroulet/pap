#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <utility>
#include <functional>

using namespace std;

typedef int ver;
typedef pair<ver, ver> eje;

struct block_cut_tree {
    struct comp {
        int cant_ver = 1;
        int cant_eje;
        int cant_ver_ady;
        vector<comp*> ady;
    };

    vector<comp*> comp_ver; // vertice v -> nodo correspondiente a v en bct
    vector<comp*> comp_calle;
    deque<comp> comps;

    block_cut_tree(int n, int m, const vector<vector<ver> >& ady_g, const vector<vector<int> >& calle)
        : comp_ver(n), comp_calle(m) {

        stack<eje> pila;
        vector<int> depth(n, -1);
        vector<int> low(n);

        function<int(ver, ver, int)> dfs = [&] (ver v, ver p, int d) -> int {
            depth.at(v) = d;
            low.at(v) = d;

            for (ver w : ady_g.at(v)) if (w != p) {
                if (depth.at(w) == -1) {
                    pila.push({v, w});

                    low.at(v) = min(low.at(v), dfs(w, v, d+1));

                    if (low.at(w) >= depth.at(v)) {
                        // v pto articulacion
                        if (comp_ver.at(v) == nullptr) {
                            comps.emplace_back();
                            comp_ver.at(v) = &comps.back();

                        }

                        comp* pto_art = comp_ver.at(v);

                        // reportar componente
                        comps.emplace_back();
                        comp* nueva_comp = &comps.back();

                        while (true) {
                            eje e = pila.top();
                            pila.pop();
                            comp_calle.at(calle.at(e.first).at(e.second)) = nueva_comp;

                            for (comp** c : {&comp_ver.at(e.first), &comp_ver.at(e.second)}) {
                                if (*c == nullptr) {
                                    *c = nueva_comp;
                                    ++nueva_comp->cant_ver;
                                }
                            }

                            ++nueva_comp->cant_eje;

                            if (e == make_pair(v, w)) break;
                        }

                        nueva_comp->ady.push_back(pto_art);
                        pto_art->ady.push_back(nueva_comp);
                    }
                } else if (depth.at(w) < depth.at(v)) {
                    pila.push({v, w});
                    low.at(v) = min(low.at(v), depth.at(w));
                }
            }

            return low.at(v);
        };

        dfs(0, 0, 0);

        for (comp* cp : comp_ver) {
            cerr << cp << " ";
        } cerr << "\n";

        for (comp& c : comps) {
            cerr << &c << " " << c.cant_ver << " " << c.cant_eje << "\n";
        }
    }

    int resolver_a(ver v1, ver v2) {
        int res = 0;

        function<int(comp*, comp*)> dfs = [&] (comp* c, comp* p) -> int {
            for (comp* w : c->ady) if (w != p) {
                if (w == comp_ver.at(v2) || dfs(w, c)) {
                    res += (comp_ver.at(v2)->cant_eje == 1);
                    return true;
                }
            }
            return false;
        };

        dfs(comp_ver.at(v1), 0);

        return res;
    }

    int resolver_b(int e) {
        return comp_calle.at(e)->cant_eje == 1;
    }

    int resolver_c(ver v) {
        throw;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int> > calle(n, vector<int>(n));
    vector<vector<ver> > ady(n);
    for (int i = 0; i < m; ++i) {
        int j1, j2;
        cin >> j1 >> j2;
        ady.at(j1-1).push_back(j2-1);
        ady.at(j2-1).push_back(j1-1);
        calle.at(j1-1).at(j2-1) = i;
        calle.at(j2-1).at(j1-1) = i;
    }

    block_cut_tree bct(n, m, ady, calle);

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        char tipo;
        cin >> tipo;

        if (tipo == 'A') {
            int j1, j2;
            cin >> j1 >> j2;
            cout << bct.resolver_a(j1-1, j2-1);
        }

        if (tipo == 'B') {
            int c;
            cin >> c;
            cout << bct.resolver_b(c-1);
        }

        if (tipo == 'C') {
            int j;
            cin >> j;
            cout << bct.resolver_c(j-1);
        }
    }
}
