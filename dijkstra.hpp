#include "structures.hpp"



// Algoritmo de Dijkstra

// Por ahora retorna vector int porque no estoy seguro
vector<int> dijkstra(graph G, int algorithm){

    /* Definimos dos arreglos de tamaño |V|, distancias y previos */
    vector<int> dists;
    vector<int> prevs;
    for (int i=0; i<G.V.size(); i++) {
        dists[i] = G.E[i].w;
        // prevs[i] =
    }
    
    // Definir una estructura Q
    if (algorithm == heap) 
    heap Q;

    // Definir distancia del nodo raiz como 0
    // Definir su nodo previo como -1
    // Agregar el par (distancia = 0, nodo = raiz) a Q
}


// Dijkstra con heap
vector<int> dijkstraHeapFib(graph G){

    /* Definimos dos arreglos de tamaño |V|, distancias y previos */
    vector<int> dists;
    vector<int> prevs;
    for (int i=0; i<G.V.size(); i++) {
        dists[i] = G.E[i].w;
        // prevs[i] =
    }
    
    // Definir una estructura Q
    heap Q;

    // Definir distancia del nodo raiz como 0
    // Definir su nodo previo como -1
    // Agregar el par (distancia = 0, nodo = raiz) a Q
}
