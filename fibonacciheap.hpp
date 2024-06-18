#include<bits/stdc++.h>
#include "binomialtree.hpp"
using namespace std;
using element = pair<double, int>;

struct fibheap {
    list<node*> f; // cola de fibonacci
    element min; // mínimo siempre conocido
    int n = static_cast<int>(f.size());

    void update_minimum(element e) {
        if (min == nullptr)
        if (min.first == nullptr || min.first > e.first) {
            min.first = e.first;
        }
    }

    /* insert: Se crea un nuevo árbol binomial B_0 que contiene x y lo añade a la lista */
    void insert(element x) {
        // crear un nuevo árbol binomial
        node* B = newNode(x);
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
                node* B = (*it);
                f.remove(*it);
                f.push_back(B->child); // ! revisar: agrega solo un hijo?
                //f.push_back((*it)->child->sibling); // esto agregaría al hermano del hijo
            }
        }
        // convertimos el bosque de árboles binomiales en un bosque binomial:
        // creamos un arreglo A de ⌈log2(n)⌉ punteros donde A[k] apunta a un único Bk si existe
        int arr_size = static_cast<int>(ceil(double(log2(n))));
        node* A[arr_size]; // inicialmente nulos
        // para cada Bk, si A[k] es nulo, A[k] <- Bk
        // sino, unimos Bk al árbol de A[k] en un Bk+1 y dejamos A[k] nulo
        int k = 0;
        for (auto it = f.begin(); it != f.end(); it++) {
            if (A[k] == NULL) {
                A[k] = *it;
                f.remove(*it);
            } else {
                node* B = merge(A[k],*it);
                A[k] == NULL;
            }
            k++;
        }
        // se tiene un bosque binomial en A y se crea una lista enlazada con sus árboles
        for (int i = 0; i < arr_size; i++) {
            if (A[i] != NULL) f.push_back(A[i]);
        }
        // se calcula el mínimo entre las log(n) raíces
        element new_min = {numeric_limits<double>::max(),NULL};
        for (auto it = f.begin(); it != f.end(); it++) {
            if ((*it)->data.first < new_min.first) {
                new_min = (*it)->data;
            }
        }
    }

    void decreaseKey(double p, int u) {
        // decrease the value of the node 'x' to the new chosen value.
        ;
        // if min-heap property is not violated, update min pointer if necessary.

        // if min-heap property is violated and parent of ‘x’ is unmarked, 
        // cut off the link between ‘x’ and its parent.
        // mark the parent of ‘x’.
        // add tree rooted at ‘x’ to the root list and update min pointer if necessary.

        // if min-heap property is violated and parent of ‘x’ is marked, 
        // cut off the link between ‘x’ and its parent p[x].
        // add ‘x’ to the root list, updating min pointer if necessary.
        // cut off link between p[x] and p[p[x]].
        // add p[x] to the root list, updating min pointer if necessary.
        // if p[p[x]] is unmarked, mark it.
        // else, cut off p[p[x]] and repeat steps 4.2 to 4.5, taking p[p[x]] as ‘x’.
    }

    bool isEmpty() {
        return f.empty();
    }
};