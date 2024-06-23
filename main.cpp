#include <random>

#include "dijkstra.hpp"
using namespace std::chrono;

int debug(int root)
{
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

    graph G3(16);
    G3.addEdge(0, 1, 0.8);
    G3.addEdge(0, 2, 0.5);
    G3.addEdge(1, 3, 0.9);
    G3.addEdge(1, 4, 0.6);
    G3.addEdge(2, 5, 0.7);
    G3.addEdge(2, 6, 0.4);
    G3.addEdge(3, 7, 0.3);
    G3.addEdge(3, 8, 0.2);
    G3.addEdge(4, 9, 0.5);
    G3.addEdge(4, 10, 0.8);
    G3.addEdge(5, 11, 0.6);
    G3.addEdge(5, 12, 0.3);
    G3.addEdge(6, 13, 0.7);
    G3.addEdge(6, 14, 0.9);
    G3.addEdge(7, 15, 0.4);
    G3.addEdge(8, 9, 0.6);
    G3.addEdge(9, 10, 0.2);
    G3.addEdge(10, 11, 0.5);
    G3.addEdge(11, 12, 0.9);
    G3.addEdge(12, 13, 0.8);
    G3.addEdge(13, 14, 0.3);
    G3.addEdge(14, 15, 0.4);

    vector<graph> test_graphs = {G0, G1, G2};
    int size = test_graphs.size();

    cout << "Usando Heap: " << endl;
    for (int i = 0; i < size; i++)
    {
        auto result = dijkstra<heap>(test_graphs[i], root);
        vector<double> dist = result.first;

        printf("-- Grafo %d --\n", i);
        for (int k = 0; k < test_graphs[i].V; k++)
        {
            printf("Distancia desde %d a %d: %f\n", root, k, dist[k]);
        }
    }
    cout << "---------------------------------" << endl;

    cout << "Usando Colas de Fibonacci: " << endl;
    for (int i = 0; i < size; i++)
    {
        auto result = dijkstra<fibheap>(test_graphs[i], root);
        vector<double> dist = result.first;

        printf("-- Grafo %d --\n", i);
        for (int k = 0; k < test_graphs[i].V; k++)
        {
            printf("Distancia desde %d a %d: %f\n", root, k, dist[k]);
        }
        cout << "---------------------------------" << endl;
    }

    cout << "--- SPECIAL CASE ---" << endl;

    auto result_sp = dijkstra<fibheap>(G3, root);
    return 0;
}

int main(int argc, char *argv[])
{
    int DEBUG = 0; // Valor por defecto
    int root = 0;  // Valor por defecto para root

    if (argc > 1)
    {
        DEBUG = std::stoi(argv[1]);
    }

    if (argc > 2)
    {
        root = std::stoi(argv[2]);
    }

    if (DEBUG)
    {
        debug(root);
        return 0;
    }

    // Inicializar la semilla aleatoria
    random_device rd;
    mt19937 gen(rd());

    vector<int> i_values = {10, 12, 14};
    vector<int> j_values = {16, 17, 18, 19, 20, 21, 22};

    // Inicializar distribuciones
    uniform_real_distribution<> distrib_weight(1e-6, 1); // (0, 1]

    for (int i : i_values)
    {
        for (int j : j_values)
        {
            int v = 1 << i; // Número de nodos
            int e = 1 << j;
            // Crear el grafo
            graph g(v);
            // Agregar v − 1 aristas al grafo
            for (int node = 1; node < v; node++)
            {
                int random_node;
                if (node == 1)
                {
                    random_node = 0;
                }
                else
                {
                    // Distribución uniforme en el rango [1, node-1]
                    uniform_int_distribution<> distrib_node(1, node - 1);
                    random_node = distrib_node(gen);
                }

                double weight = distrib_weight(gen);
                g.addEdge(node, random_node, weight);
            }
            // Agregar las aristas restantes
            int added_edges = v - 1; // Ya se han añadido v - 1 aristas
            while (added_edges < e)
            {
                int u = uniform_int_distribution<>(0, v - 1)(gen);
                int t = uniform_int_distribution<>(0, v - 1)(gen);

                if (u != t)
                {
                    double weight = distrib_weight(gen);
                    g.addEdge(u, t, weight);
                    added_edges++;
                }
            }

            cout << "Pares (i, j) utilizados:  i: " << i << " j: " << j << endl;
            cout << "Cantidad de aristas (e): " << e << endl;
            cout << "Cantidad de vertices (v): " << v << endl;

            cout << "Ejecutando dijkstra con Heap..." << endl;
            auto heap_time_start = high_resolution_clock::now();
            auto heap_result = dijkstra<heap>(g, 0);
            auto heap_time_stop = high_resolution_clock::now();
            auto heap_time_total = duration_cast<milliseconds>(heap_time_stop - heap_time_start);


            cout << "Ejecutando dijkstra con Colas de Fibonacci..." << endl;
            auto fibheap_time_start = high_resolution_clock::now();
            auto fibheap_result = dijkstra<fibheap>(g, 0);
            auto fibheap_time_stop = high_resolution_clock::now();
            auto fibheap_time_total = duration_cast<milliseconds>(fibheap_time_stop - fibheap_time_start);

            cout << "Tiempo que tardó con Heap: " << heap_time_total.count() << "ms" << endl;
            cout << "Tiempo que tardó con Colas de Fibonacci: " << fibheap_time_total.count() << "ms" << endl;
        }
    }

    return 0;
}
