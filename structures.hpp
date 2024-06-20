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


/*  Fibonacci heap: collection of rooted trees that are min-heap ordered
    (each tree obeys the min-heap property: the key of a node is greater than or equal to the key of its parent) */

// Creating a structure to represent a node in the heap
struct node {
    using element = pair<double, int>;
    node* p; // pointer to parent
	node* child; // pointer to any children (they're linked together in a circular doubly linked list -> child list)
	node* left; // pointer to the sibling node on the left of a child
	node* right; // pointer to the sibling on the right of a child
    // if a node it's an only child: y.left = y.right = y
	element key; // Value of the node
	int degree; // number of children in the child list
	bool mark; // true if node x lost a child since the last time the node was made child of another node
    // newly created nodes are unmarked and a node becomes unmarked whenever it is made the child of another node
    node* min; // pointer to the root of a tree containing the minimum key
    int n; // number of nodes
    node* rootList; // circular doubly linked list of all tree roots in the heap

    unordered_map<int, node*> pos;

    node() {min = NULL; n = 0; rootList = NULL;}

    private:
        /* operaciones de listas circulares doblemente enlazadas */
        // crear lista vacía
        void clearList(node* &L) {
            L = NULL;
            return;
        }
        // insertar elemento en una lista
        void insertList(node* &L, node* x) {
            if (L == NULL) { // si la lista está vacía
                L = x; // pasa a tener solo el elemento insertado
                L->left = L->right = x;
                return;
            } else {
                (L->left)->right = x;
                x->right = L;
                x->left = L->left;
                L->left = x;
            }
        }
        // concatenar dos listas
        node* concatenateList(node* &L1, node* L2) {
            if (L1 == NULL) return L2;
            if (L2 == NULL) return L1;

            node *next1 = L1->right;
            node *next2 = L2->left;

            L2->left = L1;
            L1->right = L2;
            next2->left = next1;
            next1->right = next2;

            return L1;
        }
        // quitar un nodo de una lista
        void removeList(node* &L, node* x) {
            node* curr = L->right;
            if (L == NULL || x == NULL) return;
            if (L == x) L = x->right;
            else {
                while (curr != L) {
                    if (curr == x) {
                        curr->right->left = curr->left;
                        curr->left->right = curr->right;
                        break;
                    }
                    curr = curr->right;
                }
            }
            return;
        }

        /* operaciones de árboles binomiales */
        // hacer que y sea un hijo de x
        void makeChild(node* x, node* y){
            if (x->child == NULL) {
                x->child = y;
            } else {
                insertList(x->child, y);
            }
            x->degree++;
        }
        // quitar x de la lista de hijos de y
        void removeChild(node* x, node* y) {
            removeList(y->child,x);
            y->degree--;
        }

        /* funciones auxiliares */
        // make an empty fibonacci heap
        node* makefibheap() {
            node* H = new node();
            H->n = 0;
            H->min = NULL; // when a fibheap is empty, min is NULL (default)
            // there are no trees in H
            return H;
        }
        // mergeHeaps
        node* mergeHeaps(node* H1, node* H2) {
            node* H = makefibheap();
            H->min = H1->min;
            H->rootList = concatenateList(H2->rootList,H->rootList);
            if((H1->min == NULL) || (H2->min != NULL && H2->min->key.first < H1->min->key.first))
                H->min = H2->min;
            H->n = H1->n + H2->n;
            return H;
        }
        void fibheaplink(node* H, node* y, node* x) {
            removeList(H->rootList, y); // remove y from the root list of H
            makeChild(x,y); // make y a child of x, incrementing x.degree
            y->mark = false; // y.mark = false
        }
        // logaritmo en base phi de n
        double log_phi(int n) {
            double phi = (1 + sqrt(5)) / 2; // golden ratio
            double res = log(n) / log(phi);
            return res;
        }
        // calculate upper bound D(H->n) on the maxximum degree
        int upper_bound() {
            int D_n = floor(log_phi(n));
            return D_n;
        }
        void consolidate() {
            node* A[upper_bound()];
            for (int i=0; i<upper_bound(); i++) {
                A[i] = NULL;
            }
            node* w = rootList->right;
            while (w != rootList) {
                node* x = w;
                int d = x->degree;
                while (A[d] != NULL) {
                    node* y = A[d];
                    if (x->key.first > y->key.first)
                        swap(x,y);
                    fibheaplink(this,y,x);
                    A[d] = NULL;
                    d++;
                }
                A[d] = x;
                w = w->right;
            }
            min = NULL;
            for (int i=0; i<upper_bound(); i++) {
                if (A[i] != NULL) {
                    if (min == NULL) {
                        clearList(rootList); // create a root list for H containing just A[i]
                        insertList(rootList, A[i]);
                        min = A[i];
                    } else {
                        insertList(rootList, A[i]);
                        if (A[i]->key.first < min->key.first)
                            min = A[i];
                    }
                }
            }
        }
        void cut(node* H, node* x, node* y) {
            removeChild(x, y); // remove x from the child list of y, decrementing y.degree
            insertList(H->rootList, x);
            x->p = NULL;
            x->mark = false;
        }
        void cascading_cut(node* H, node* y) {
            node* z = y->p;
            if (z != NULL) {
                if (y->mark == false)
                    y->mark = true;
                else {
                    cut(H,y,z);
                    cascading_cut(H,z);
                }
            }
        }
        // void deletion(node* x) {
        //     decreaseKey(x,-INFINITY);
        //     extract();
        // }

    public:
        // inserting a node
        void insert(element e) {
            node* x = new node();
            x->key = e;
            x->degree = 0;
            x->p = NULL;
            x->child = NULL;
            x->left = x;
            x->right = x;
            x->mark = false;
            if (min == NULL) {
                rootList = x;
                min = x;
            } else {
                insertList(rootList, x);
                if (x->key.first < min->key.first)
                    min = x;
            }
            n++;

            pos[e.second] = x;
        }

        // find minimum
        element find() {
            return min->key;
        }

        // extract min
        void extract() {
            node* z = min;
            if (z != NULL) {
                if (z->child != NULL) {
                    node* x = z->child->right;
                    cout << "while extract!!" << endl;
                    while (x != z->child) { // for each child x of z
                        insertList(rootList, x); // add x to the root list of H
                        x->p = NULL;
                        x = x->right;
                    }
                }
                cout << "remove list!!" << endl;
                removeList(rootList, z); // remove z from the root list of H
                if (z == z->right)
                    min = NULL;
                else {
                    min = z->right;
                    consolidate();
                }
                n--;
            }
            pos.erase(z->key.second);
            return;
        }

        // void decreaseKey(double p, int u)
        void decreaseKey(double p, int u) {
            node* x = pos[u];
            x->key.first = p;
            node* y = x->p;
            if (y != NULL && x->key.first < y->key.first) {
                cut(this,x,y);
                cascading_cut(this,y);
            }
            if (x->key.first < min->key.first)
                min = x;
        }

        bool isEmpty() {
            return n==0;
        }
};