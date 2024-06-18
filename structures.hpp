#include <bits/stdc++.h>
using namespace std;

const double infinity = numeric_limits<double>::infinity();
const int undefined = numeric_limits<int>::quiet_NaN();

/* Grafo */
struct graph {
    int V;                                  // vertices
    vector<vector<pair<int, double>>> adj;  // Lista de adyacencia

    graph(int n) : V(n), adj(n) {}

    void addEdge(int u, int v, double weight) {
        adj[u].emplace_back(v, weight);
        adj[v].emplace_back(u, weight);
    }
};

/* Heap */
struct heap {
    using element = pair<double, int>;  // (distance, node)
    set<element> s;
    unordered_map<int, double> pos;  // node -> distance

    void insert(element e) {
        s.insert(e);
        pos[e.second] = e.first;

        // if (s.size() > 1)
        // {
        //     s.first.min_element();
        // }
    }

    element find() {
        return *s.begin();
    }

    void extract() {
        pos.erase(s.begin()->second);
        s.erase(s.begin());
    }

    void decreaseKey(double p, int u) {
        // Primero, eliminamos el antiguo par (distancia, nodo)
        s.erase({pos[u], u});
        // Luego, insertamos el nuevo par (distancia, nodo)
        s.insert({p, u});
        // Finalmente, actualizamos la distancia en el mapa
        pos[u] = p;
    }

    bool isEmpty() {
        return s.empty();
    }
};

