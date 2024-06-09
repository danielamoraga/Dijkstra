#include <random>

#include "dijkstra.hpp"

int TEST = 0;
int test() {
    graph G(5);
    G.addEdge(0, 1, 10);
    G.addEdge(0, 4, 5);
    G.addEdge(1, 2, 1);
    G.addEdge(4, 1, 3);
    G.addEdge(4, 2, 9);
    G.addEdge(4, 3, 2);
    G.addEdge(2, 3, 4);
    G.addEdge(3, 0, 7);

    auto result1 = dijkstra<heap>(G, 0);
    vector<double> dist1 = result1.first;
    vector<double> prev1 = result1.second;

    for (int i = 0; i < G.V; i++) {
        printf("Distancia desde 0 a %d usando Heap: %f\n", i, dist1[i]);
    }

    return 0;
}

// Función para generar un número aleatorio en el rango (0..1]
double get_random_weight() {
    return (double)rand() / RAND_MAX;
}
int main() {
    if (TEST) {
        test();
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
