#include <bits/stdc++.h>
using namespace std;

/* Arista */
struct edge {
    pair<int, int> v; // par de vertices conectados por la arista
    int w; // peso de la arista
};

/* Grafo */
struct graph {
    vector<int> V; // vertices
    vector<edge> E; // aristas con peso wi
};

/* Heap */
struct heap {
    pair< 

};

/* Cola de Fibonacci */
struct fibheap {

};

enum class Algorithm { heap, fibheap };