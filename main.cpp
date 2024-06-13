#include <random>

#include "dijkstra.hpp"

int DEBUG = 1;
int debug() {
    int root = 0;

    graph G0(5);
    G0.addEdge(0, 1, 10);
    G0.addEdge(0, 4, 5);
    G0.addEdge(1, 2, 1);
    G0.addEdge(4, 1, 3);
    G0.addEdge(4, 2, 9);
    G0.addEdge(4, 3, 2);
    G0.addEdge(2, 3, 4);
    G0.addEdge(3, 0, 7);

    graph G1(6);
    G1.addEdge(0, 1, 0.2);
    G1.addEdge(0, 2, 0.3);
    G1.addEdge(1, 3, 0.3);
    G1.addEdge(2, 4, 0.4);
    G1.addEdge(3, 4, 0.5);
    G1.addEdge(4, 5, 0.8);

    graph G2(6);
    G2.addEdge(0, 1, 1);
    G2.addEdge(0, 3, 10);
    G2.addEdge(1, 2, 8);
    G2.addEdge(2, 4, 3);
    G2.addEdge(3, 4, 1);
    G2.addEdge(3, 5, 2);
    G2.addEdge(5, 4, 4);

    vector<graph> test_graphs = {G0, G1, G2};
    int size = test_graphs.size();

    for (int i = 0; i < size; i++) {
        auto result = dijkstra<heap>(test_graphs[i], root);
        vector<double> dist = result.first;
        vector<int> prev = result.second;

        printf("-- Grafo %d --\n", i);
        for (int k = 0; k < test_graphs[i].V; k++) {
            printf("Distancia desde %d a %d usando Heap:, %f\n", root, k, dist[k]);
        }
    }
    return 0;
}

// Función para generar un número aleatorio en el rango (0..1]
double get_random_weight() {
    return (double)rand() / RAND_MAX;
}
int main() {
    if (DEBUG) {
        debug();
        return 0;
    }

    // Semilla para números aleatorios
    srand(time(0));

    vector<int> i_values = {10, 12, 14};
    vector<int> j_values = {16, 17, 18, 19, 20, 21, 22};

    // Elegir i y j aleatoriamente de los valores permitidos
    int i = 2;
    int j = 3;

    int v = 1 << i;  // Número de nodos: 2^i = 4
    int e = 1 << j;  // Número de aristas: 2^j = 8

    // Crear el grafo
    graph g(v);
    // iota(g.V.begin(), g.V.end(), 0);  // Inicializar los nodos de 0 a v-1

    // Generar el árbol de expansión
    for (int node = 1; node < v; node++) {
        int random_node = rand() % node;
        g.addEdge(node, random_node, get_random_weight());
    }

    // Agregar las aristas restantes
    set<pair<int, int>> existing_edges;
    for (int u = 0; u < v; ++u) {
        for (auto& edge : g.adj[u]) {
            int v = edge.first;
            existing_edges.insert({min(u, v), max(u, v)});
        }
    }

    while (static_cast<int>(existing_edges.size()) < e) {
        int u = rand() % v;
        int v = rand() % v;
        if (u != v && !existing_edges.count({min(u, v), max(u, v)})) {
            g.addEdge(u, v, get_random_weight());
            existing_edges.insert({min(u, v), max(u, v)});
        }
    }

    // Mostrar el grafo
    cout << "Nodos (v = " << v << "):" << endl;
    for (int node = 0; node < v; ++node) {
        cout << node << " ";
    }
    cout << endl;

    cout << "Aristas (e = " << e << "):" << endl;
    for (int u = 0; u < v; ++u) {
        for (auto& edge : g.adj[u]) {
            int v = edge.first;
            double w = edge.second;
            cout << u << " - " << v << " : " << w << endl;
        }
    }

    return 0;
}
