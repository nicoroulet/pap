#include <iostream>
#include <vector>
#include <stack>

#define DBG(x) cerr << #x << " = " << (x) << endl

using namespace std;
// n = aulas, m = pasillos


// la idea es usar Kosaraju para identificar las componentes fuertemente conexas, enumerarlas,
// y tener en un vector "componentes" de n posiciones, donde la posición componentes[i] indique el número de componente del nodo i

void dfsArmadorDeStack(int64_t noditoActual, vector<bool> &visitado, vector<vector<int64_t> > &ady, stack<int64_t> &stackFinalizados){
    // recorro los alcanzables desde noditoActual
    visitado[noditoActual] = true;
    for (int64_t j = 0; j < ady[noditoActual].size(); ++j) {
        int64_t vecino = ady[noditoActual][j];
        if (!visitado[vecino]) {
            dfsArmadorDeStack(vecino, visitado, ady, stackFinalizados);
        }
    }
    // cuanto termine el dfs desde este nodo, este nodo finalizo y ahora lo pusheo al stack
    stackFinalizados.push(noditoActual);
}

int main() {
    int64_t n, m;
    cin >> n;
    cin >> m;
    // ady contiene los ejes de G (el grafo)
    vector<vector<int64_t> > ady = vector<vector<int64_t> >(n);

    // adyT contiene los ejes de Gt (el grafo transpuesto)
    vector<vector<int64_t> > adyT = vector<vector<int64_t> >(n);

    // componentes contiene el numero de componente de cada nodo
    vector<int64_t> componentes = vector<int64_t> (n,-1);

    // stackFinalizados pushea a los nodos por orden de aparición, de esta forma al hacer DFS(Gt) los recorro en orden decreciente de tiempo de finalizacion
    stack<int64_t> stackFinalizados = stack<int64_t>();

    // visitado es suficientemente descriptivo como para que lo explique
    vector<bool> visitado = vector<bool>(n, false);


    for (int64_t i = 0; i < m; ++i) {
        int64_t nodo1, nodo2;
        cin >> nodo1;
        cin >> nodo2;
        nodo1--;
        nodo2--;
        ady[nodo1].push_back(nodo2);
        adyT[nodo2].push_back(nodo1);
    }

    // TODO: verificar que el grafo no sea vacio?

    // hago dfs(G)
    for (int64_t i = 0; i < n; ++i) {
        if (!visitado[i]){
            dfsArmadorDeStack(i, visitado, ady, stackFinalizados);
        }
    }
    


    // hago dfs(Gt), en el orden inverso que los stackee en stackFinalizados
    visitado = vector<bool>(n, false);

    int64_t componenteActual = 0;
    while(!stackFinalizados.empty()) {
        int64_t i = stackFinalizados.top();

        stackFinalizados.pop();
        if (!visitado[i]){

            // recorro los alcanzables desde i
            stack<int64_t> s = stack<int64_t>();
            s.push(i);
            while(!s.empty()) {
                int64_t nodito = s.top();
                componentes[nodito] = componenteActual;
                s.pop();
                visitado[nodito] = true;
                for (int64_t j = 0; j < adyT[nodito].size(); ++j) {
                    int64_t vecino = adyT[nodito][j];
                    if (!visitado[vecino]) {
                        s.push(vecino);
                    }
                }
            }
            // cuanto termina el while recorri una componente
            componenteActual++;
        }
    }


    // inputeo las queries
    int64_t q;
    cin >> q;
    //este cout extremadamente util para debugguear, no lo borro
    /*for (int64_t i = 0; i < n; ++i){
        cout << "nodo " << i+1 << " - componente " << componentes[i] << endl;
    }*/

    for (int64_t i = 0; i < q; ++i) {
        int64_t nodo1, nodo2;

        cin >> nodo1;
        cin >> nodo2;
        nodo1--;
        nodo2--;

        


        // me fijo si pertecen a la misma componente fuertemente conexa
        if(componentes[nodo1] == componentes[nodo2]){
            cout << "S" << endl;
        } else {
            cout << "N" << endl;
        }
    }
}