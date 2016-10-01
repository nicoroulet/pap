#include <iostream>
#include <vector>
#include <stack>

#define DBG(x) cerr << #x << " = " << (x) << endl


using namespace std;
// n = aulas, m = pasillos


// la idea es usar Kosaraju para identificar las componentes fuertemente conexas, enumerarlas,
// y tener en un vector "componentes" de n posiciones, donde la posición componentes[i] indique el número de componente del nodo i

int main() {
    int n, m;
    cin >> n;
    cin >> m;
    // ady contiene los ejes de G (el grafo)
    vector<vector<int> > ady = vector<vector<int> >(n);

    // adyT contiene los ejes de Gt (el grafo transpuesto)
    vector<vector<int> > adyT = vector<vector<int> >(n);

    // componentes contiene el numero de componente de cada nodo
    vector<int> componentes = vector<int> (n,-1);

    // stackFinalizados pushea a los nodos por orden de aparición, de esta forma al hacer DFS(Gt) los recorro en orden decreciente de tiempo de finalizacion
    stack<int> stackFinalizados = stack<int>();

    // visitado es suficientemente descriptivo como para que lo explique
    vector<bool> visitado = vector<bool>(n, false);


    for (int i = 0; i < m; ++i) {
        int nodo1, nodo2;
        cin >> nodo1;
        cin >> nodo2;
        nodo1--;
        nodo2--;
        ady[nodo1].push_back(nodo2);
        adyT[nodo2].push_back(nodo1);
    }

    // TODO: verificar que el grafo no sea vacio

    // hago dfs(G)
    stack<int> s = stack<int>();

    for (int i = 0; i < n; ++i) {
        if (!visitado[i]){

            // recorro los alcanzables desde i
            s.push(i);
            while(!s.empty()){
                int nodito = s.top();
                s.pop();
                visitado[nodito] = true;
                for (int j = 0; j < ady[nodito].size(); ++j) {
                    int vecino = ady[nodito][j];
                    if (!visitado[vecino]) {
                        s.push(vecino);
                    }
                }
                // este nodo finalizo, asi que lo pusheo al stack de finalizados
                stackFinalizados.push(nodito);
            }
            // cuanto termina el while recorri una componente
        }
    }


    // hago dfs(Gt), en el orden inverso que los stackee en stackFinalizados
    visitado = vector<bool>(n, false);

    int componenteActual = 0;
    while(!stackFinalizados.empty()) {
        int i = stackFinalizados.top();
        
        stackFinalizados.pop();
        if (!visitado[i]){

            // recorro los alcanzables desde i
            s = stack<int>();
            s.push(i);
            while(!s.empty()) {
                int nodito = s.top();
                componentes[nodito] = componenteActual;
                s.pop();
                visitado[nodito] = true;
                for (int j = 0; j < adyT[nodito].size(); ++j) {
                    int vecino = adyT[nodito][j];
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
    int q;
    cin >> q;
    for (int i = 0; i < n; ++i){
        cout << "nodo " << i+1 << " - componente " << componentes[i] << endl;
    }

    for (int i = 0; i < q; ++i) {
        int nodo1, nodo2;

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