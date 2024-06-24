#include "structures.hpp"

// Algoritmo de Dijkstra
template <typename Structure>
pair<vector<double>, vector<int>> dijkstra(graph G, int root)
{
    int n = G.V;

    // 1. Definimos dos arreglos de tamaño |V|, distancias y previos
    vector<double> dist(n);
    vector<int> prev(n);

    // 2. Definir estructura Q
    Structure Q;

    // 3. Definir distancia del nodo raiz como 0
    dist[root] = 0;

    // Definir su nodo previo como -1
    prev[root] = -1;

    // Agregar el par (distancia = 0, nodo = raiz) a Q
    Q.insert({0, root});

    // 4. Por cada nodo v
    for (int v = 0; v < n; v++)
    {
        // distinto de la raíz en el grafo
        if (v != root)
        {
            // Definimos distancias[v] como infinita
            dist[v] = infinity;

            // Definimos previos[v] como indefinido
            prev[v] = undefined;

            // Agregamos el par (distancia = ∞, nodo = v) a Q
            Q.insert({infinity, v});
        }
    }

    // 6. Mientras Q no se encuentre vacío, repetimos:
    while (!Q.isEmpty())
    {
        // Obtenemos el par (d, v) con menor distancia en Q
        pair<double, int> dv = Q.find();
        // lo eliminamos
        Q.extract();

        int v = dv.second;
        // Por cada vecino u del nodo v:
        for (pair<int, double> nu : G.adj[v])
        {
            int u = nu.first;      // vecino u
            double wu = nu.second; // peso de la arista (u, v)
            // Si la distancia guardada para u (distancias[u]) es mayor a la distancia guardada para v (distancias[v])
            // más el peso de la arista (u, v)
            double p = dist[v] + wu;
            if (dist[u] > p)
            {
                // actualizamos el valor de la distancia de u
                dist[u] = p;
                // guardamos v como el nodo previo de u
                prev[u] = v;

                // actualizamos la distancia del par que representa al nodo u en Q utilizando decreaseKey
                Q.decreaseKey(p, u);
            }
        }
    }

    // 7. Retornamos el arreglo de previos y distancias
    return {dist, prev};
}
