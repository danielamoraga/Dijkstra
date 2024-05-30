#include "dijkstra.hpp"
#include <random>

// Función para generar un número aleatorio en el rango (0..1]
double get_random_weight() {
    return (double)rand() / RAND_MAX;
}
int main(){
    // Semilla para números aleatorios
    srand(time(0));

    vector<int> i_values = {10, 12, 14};
    vector<int> j_values = {16, 17, 18, 19, 20, 21, 22};

    // Elegir i y j aleatoriamente de los valores permitidos
    int i = 2;
    int j = 3;

    int v = 1 << i; // Número de nodos: 2^i = 4
    int e = 1 << j; // Número de aristas: 2^j = 8

    // Crear el grafo
    graph g;
    g.V.resize(v);
    iota(g.V.begin(), g.V.end(), 0); // Inicializar los nodos de 0 a v-1

    // Generar el árbol de expansión
    for (int node = 1; node < v; node++) {
        int random_node = rand() % node;
        g.E.resize(node);
        edge e = edge(); // ola dani perdon le saque el "new" por mientras
        e.v = {node, random_node};
        e.w = get_random_weight();
        g.E.push_back(e);
    }

    // Agregar las aristas restantes
    set<pair<int, int>> existing_edges;
    for (const auto& e : g.E) {
        existing_edges.insert(e.v);
        existing_edges.insert({e.v.second, e.v.first});
    }
    int node = v;
    
    while (g.E.size() < e) { // ahora se queda en un loop infinito por que g.E.size() no cambia
        int u = rand() % (v + 1); // rand() % v da entre 0 y 3 , por eso le sume + 1 a ambos
        int v = rand() % (v + 1);
        if (u != v && existing_edges.find({u, v}) == existing_edges.end()) {
            edge new_edge = { {u, v}, get_random_weight() };    
            g.E.push_back(new_edge); // Agregar la nueva arista al grafo
            existing_edges.insert({u, v});
            existing_edges.insert({v, u});
            node++;
        }
    }

    // Mostrar el grafo
    cout << "Nodos (v = " << v << "):" << endl;
    for (int node : g.V) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Aristas (e = " << e << "):" << endl;
    for (const auto& edge : g.E) {
        cout << edge.v.first << " - " << edge.v.second << " : " << edge.w << endl;
    }

    // Dijstra usando Q como heap
    

    return 0;
}