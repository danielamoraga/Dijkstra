#include<bits/stdc++.h>
#include "binomialtree.hpp"
using namespace std;
using element = pair<double, int>;

struct fibheap {
    list<Node*> f; // cola de fibonacci
    element min; // mínimo siempre conocido
    int n = f.size();

    void update_minimum(element e) {
        if (min.first == NULL || min.first > e.first) {
            min.first = e.first;
        }
    }

    /* insert: Se crea un nuevo árbol binomial B_0 que contiene x y lo añade a la lista */
    void insert(element x) {
        // crear un nuevo árbol binomial
        Node* B = newNode(x);
        // añadir el nuevo árbol binomial a la lista
        f.push_back(B);
        // actializar el mínimo
        update_minimum(x);
    }

    /* find: retorna el mínimo siempre conocido */
    element find() {
        return min;
    }

    /* extract: recorre la lista para convertirla en un bosque binomial sumando árboles iguales iterativamente */
    void extract() {
        // eliminamos la raíz del árbol que contiene el mínimo y agregamos sus hijos a f
        for (auto it = f.begin(); it != f.end(); it++ ) {
            if ((*it)->data.first == min.first) {
                Node* B = (*it);
                f.remove(*it);
                f.push_back(B->child); // ! revisar: agrega solo un hijo?
                //f.push_back((*it)->child->sibling); // esto agregaría al hermano del hijo
            }
        }
        // convertimos el bosque de árboles binomiales en un bosque binomial:
        // creamos un arreglo A de ⌈log2(n)⌉ punteros donde A[k] apunta a un único Bk si existe
        int arr_size = static_cast<int>(ceil(double(log2(n))));
        Node* A[arr_size]; // inicialmente nulos
        // para cada Bk, si A[k] es nulo, A[k] <- Bk
        // sino, unimos Bk al árbol de A[k] en un Bk+1 y dejamos A[k] nulo
        int k = 0;
        for (auto it = f.begin(); it != f.end(); it++) {
            if (A[k] == NULL) {
                A[k] = *it;
                f.remove(*it);
            } else {
                Node* B = merge(A[k],*it);
                A[k] == NULL;
            }
            k++;
        }
        // se tiene un bosque binomial en A y se crea una lista enlazada con sus árboles
        for (int i = 0; i < arr_size; i++) {
            f.push_back(A[i]);
        }
        // se calcula el mínimo entre las log(n) raíces
        element new_min = {numeric_limits<double>::max(),NULL};
        for (auto it = f.begin(); it != f.end(); it++) {
            if ((*it)->data.first < new_min.first) {
                new_min = (*it)->data;
            }
        }
    }
};