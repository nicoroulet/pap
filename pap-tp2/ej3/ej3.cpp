#include <iostream>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> eje;
#define src(e) (e.first)
#define dst(e) (e.second)

typedef vector<vector<int>> lista_ady;

class block_cut_tree {
    vector<int> depth;
    vector<int> low;
    map<eje, X> comp;

public:

    block_cut_tree(int n, int m, lista_ady ady) : depth(n, -1), low(n) {
        // dfs
        stack<eje> pila;
        dfs(n, m, ady, 0, 0, 0, pila);
    }

    int resolver(query_a q) {
        // q.e1, q.e2
        X d1 = ubicar(q.e1);
        X d2 = ubicar(q.e2);
        auto k = camino(d1, d2);
        int res = 0
        for (auto& c : k) res += (c.size() == 2);
        return res;
    }

    int resolver(query_b q) {
        return comp[q.u].size();
    }

    int resolver(query_c q) {
        X d = ubicar(q.e);
        return d.suma_size_adyacentes();
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    lista_ady ady(n);
    for (int i = 0; i < m; ++i) {
        int e1, e2;
        cin >> e1 >> e2;
        ady[e1-1].push_back(e2-1);
        ady[e2-1].push_back(e1-1);
    }

    block_cut_tree bct(n, m, ady);

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        query x;
        cout << bct.resolver(x) << endl;
    }
}
