#include <bits/stdc++.h>
using namespace std;
using element = pair<double, int>;  // (distance, node)

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
    vector<element> h;
    unordered_map<int, int> pos;  // node -> index in vector

   public:
    void build(vector<element> &array) {
        h = array;
        heapify();
    }

    element find() {
        return h.front();
    }

    void extract() {
        if (h.empty())
            return;
        pos.erase(h.front().second);
        h.front() = h.back();
        h.pop_back();
        bubbleDown(0);
    }

    void decreaseKey(double p, int u) {
        int index = pos[u];
        h[index].first = p;
        bubbleUp(index);
    }

    bool isEmpty() {
        return h.empty();
    }

   private:
    void heapify() {
        int n = h.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            bubbleDown(i);
        }

        // Update positions
        for (int i = 0; i < n; ++i) {
            pos[h[i].second] = i;
        }
    }

    void bubbleDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        int n = h.size();

        if (left < n && h[left] < h[smallest]) {
            smallest = left;
        }
        if (right < n && h[right] < h[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            swap(h[i], h[smallest]);
            pos[h[i].second] = i;
            pos[h[smallest].second] = smallest;
            bubbleDown(smallest);
        }
    }

    void bubbleUp(int i) {
        while (i > 0 && h[i] < h[(i - 1) / 2]) {
            int parent = (i - 1) / 2;
            swap(h[i], h[parent]);
            pos[h[i].second] = i;
            pos[h[parent].second] = parent;
            i = parent;
        }
    }
};

// Creating a structure to represent a node in the heap
struct node {
    node *p;      // parent pointer
    node *child;  // child pointer
    node *left;   // pointer to the node on the left
    node *right;  // pointer to the node on the right
    element key;  // value of the node
    int degree;   // degree of the node
    bool mark;    // mark of the node
};

struct fibheap {
    node *min = NULL;                     // creating min pointer
    int n = 0;                            // declare an integer for number of nodes in the heap
    unordered_map<int, node *> node_map;  // map to keep pointers associated to node numbers

   public:
    /* inserts element e creating a node x with that key */
    void insert(element e) {
        struct node *x = new node();
        x->key = e;
        x->degree = 0;
        x->p = NULL;
        x->child = NULL;
        x->mark = false;
        x->left = x;
        x->right = x;
        if (min == NULL)
            min = x;  // create min containing just x
        else {
            // add x to min
            (min->left)->right = x;
            x->right = min;
            x->left = min->left;
            min->left = x;
            if (x->key.first < min->key.first)
                min = x;
        }
        node_map[e.second] = x;
        n++;
    }

    /* build a fibonacci tree */
   public:
    void build(vector<element> v) {
        for (int i=0; i<(int)v.size(); i++) {
            insert(v[i]);
        }
    }

   public:
    /* returns the key of the node containing the minimum */
    element find() {
        return min->key;
    }

   private:
    /* new heap containing all the elements of two heaps */
    void fiblink(struct node *y, struct node *x) {
        // remove y from min
        if (y == y->right)
            min = x;
        else {
            (y->left)->right = y->right;
            (y->right)->left = y->left;
            // if (x->right == x)
            //     min = x;
            if (min == y)
                min = y->right;
        }
        // make y a child of x
        y->left = y;
        y->right = y;
        y->p = x;
        if (x->child == NULL)
            x->child = y;
        y->right = x->child;
        y->left = (x->child)->left;
        ((x->child)->left)->right = y;
        (x->child)->left = y;
        if (y->key.first < (x->child)->key.first)
            x->child = y;
        x->degree++;  // incrementing x->degree
        y->mark = false;
        node_map[x->key.second] = x;
        node_map[y->key.second] = y;
    }

   private:
    void consolidate() {
        int d;
        const double phi = (1.0 + sqrt(5.0)) / 2.0;       // golden ratio
        int D = static_cast<int>(log(n) / log(phi)) + 1;  // upper bound
        std::vector<node *> A(D, nullptr);                // use vector for dynamic array size

        std::vector<node *> rootList;
        node *w = min;
        if (w != nullptr) {
            do {
                rootList.push_back(w);
                w = w->right;
            } while (w != min);
        }

        for (node *w : rootList) {
            node *x = w;
            d = x->degree;
            while (A[d] != nullptr) {
                node *y = A[d];
                if (x->key.first > y->key.first) {
                    std::swap(x, y);
                }
                fiblink(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }

        min = nullptr;
        for (node *nodePtr : A) {
            if (nodePtr != nullptr) {
                if (min == nullptr) {
                    min = nodePtr;
                    min->left = min;
                    min->right = min;
                } else {
                    nodePtr->left = min->left;
                    nodePtr->right = min;
                    min->left->right = nodePtr;
                    min->left = nodePtr;
                    if (nodePtr->key.first < min->key.first) {
                        min = nodePtr;
                    }
                }
            }
        }
    }

   public:
    /* deletes the element from heap whose key is minimum*/
    void extract() {
        node *z = min;
        node *childlist;
        childlist = z;
        node *x = NULL;  // interpetrates child list
        if (z->child != NULL) {
            x = z->child;
            do {
                childlist = x->right;
                // add x to the rootlist min
                (min->left)->right = x;
                x->right = min;
                x->left = min->left;
                min->left = x;
                if (x->key.first < min->key.first)
                    min = x;
                node_map[x->key.second] = x;
                x->p = NULL;
                x = childlist;
            } while (childlist != z->child);  // while not the first element of childlist
        }
        // remove z from min
        (z->left)->right = z->right;
        (z->right)->left = z->left;
        if (z == z->right)
            min = NULL;
        else {
            min = z->right;
            consolidate();
        }
        n--;
        node_map.erase(z->key.second);
    }

   private:
    void cut(struct node *x, struct node *y) {
        // removing x from y childs
        if (x == x->right)
            y->child = NULL;
        else {
            (x->left)->right = x->right;
            (x->right)->left = x->left;
            if (x == y->child)
                y->child = x->right;
        }
        y->degree--;  // decrementing y->degree
                      // add x to min (root list)
        (min->left)->right = x;
        x->right = min;
        x->left = min->left;
        min->left = x;
        if (x->key.first < min->key.first)
            min = x;
        x->p = NULL;
        x->mark = false;
        node_map[x->key.second] = x;
        node_map[y->key.second] = y;
    }

   private:
    void cascade_cut(struct node *y) {
        node *z = y->p;
        if (z != NULL) {
            if (y->mark == false) {
                y->mark = true;
            } else {
                cut(y, z);
                cascade_cut(z);
            }
        }
    }

   public:
    /* assigns the new key.first value to the node u, assuming is not greater than its current value */
    void decreaseKey(double p, int u) {
        node *x = node_map[u];
        x->key.first = p;
        struct node *y = x->p;
        if (y != NULL && x->key.first < y->key.first) {
            cut(x, y);
            cascade_cut(y);
        }
        if (x->key.first < min->key.first)
            min = x;
    }
    /* determine if the fibheap is empty */
   public:
    bool isEmpty() {
        if (min == NULL)
            return true;
        else
            return false;
    }
};