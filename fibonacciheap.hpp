#include<bits/stdc++.h>
#include "binomialtree.hpp"
using namespace std;
using element = pair<double, int>;

struct fibheap {
    list<node*> f; // cola de fibonacci
    node* min; // mínimo siempre conocido

    void update_minimum(node* n) {
        if (min != NULL) {
            if(n->data < min->data)
                min = n;
        } else {
            min = n;
        }
    }

    /* insert: Se crea un nuevo árbol binomial B_0 que contiene x y lo añade a la lista */
    void insert(element x) {
        // crear un nuevo árbol binomial
        node* B = newNode(x);
        // añadir el nuevo árbol binomial a la lista
        f.push_back(B);
        // actualizar el mínimo
        update_minimum(B);
    }

    /* find: retorna el mínimo siempre conocido */
    element find() {
        return min->data;
    }

    /* extract: recorre la lista para convertirla en un bosque binomial sumando árboles iguales iterativamente */
    void extract() {
        // eliminamos la raíz del árbol que contiene el mínimo y agregamos sus hijos a f
        node* temp = min;
        f.remove(min);
        if (temp->child != NULL) {
            f.push_back(temp->child);
            if (temp->child->sibling != NULL) f.push_back(temp->child->sibling);
        }

        // convertimos el bosque de árboles binomiales en un bosque binomial:
        // creamos un arreglo A de ⌈log2(n)⌉ punteros donde A[k] apunta a un único Bk si existe
        int arr_size = static_cast<int>(ceil(log2(static_cast<double>(f.size()))));
        node* A[arr_size]; // inicialmente nulos
        // para cada Bk, si A[k] es nulo, A[k] <- Bk
        // sino, unimos Bk al árbol de A[k] en un Bk+1 y dejamos A[k] nulo
        int k = 0;
        for (auto Bk = f.begin(); Bk != f.end(); Bk++) {
            if (A[k] == NULL) {
                A[k] = *Bk;
            } else {
                node* B = merge(A[k],*Bk);
                f.push_back(B);
                A[k] == NULL;
            }
            k++;
        }
        // se tiene un bosque binomial en A y se crea una lista enlazada con sus árboles
        f.clear();
        for (int i = 0; i < arr_size; i++) {
            if (A[i] != NULL)
                f.push_back(A[i]);
        }
        // se calcula el mínimo entre las log(n) raíces
        node* new_min;
        new_min->data = {numeric_limits<double>::max(),NULL};
        for (auto Bk = f.begin(); Bk != f.end(); Bk++) {
            if ((*Bk)->data.first < new_min->data.first) {
                new_min = *Bk;
            }
        }
        min = new_min;
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