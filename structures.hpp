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
    void insert(element e) {
        h.push_back(e);
        heapify();
    }

    element find() {
        return h.front();
    }

    void extract() {
        if (h.empty()) return;
        pos.erase(h.front().second);
        h.front() = h.back();
        h.pop_back();
        heapify();
    }

    void decreaseKey(double p, int u) {
        int index = pos[u];
        h[index].first = p;
        heapify();
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
};

// Creating a structure to represent a node in the heap
struct node {
    node* p;  // Parent pointer
    node* child;   // Child pointer
    node* left;    // Pointer to the node on the left
    node* right;   // Pointer to the node on the right
    element key;   // Value of the node
    int degree;    // Degree of the node
    bool mark;     // Black or white mark of the node
    bool c;        // Flag for assisting in the Find node function
};

struct fibheap {
    node* min = NULL; // creating min pointer
    int n = 0; // declare an integer for number of nodes in the heap
    unordered_map<int, node*> node_map;

   public:
    /* inserts element val creating a node x with that key */
    void insert(element e) {
        struct node* x = new node();
        x->key = e;
        x->degree = 0;
        x->p = NULL;
        x->child = NULL;
        x->mark = false;
        x->c = false;
        x->left = x;
        x->right = x;
		if (min == NULL)
			min = x; // create min containing just x
        else {
			// insert x into min
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
   public:
    /* returns the key of the node containing the minimum */
    element find() {
        return min->key;
    }
   private:
    /* new heap containing all the elements of two heaps */
    void fiblink(struct node* y, struct node* x) {
        node_map.erase(y->key.second);
        node_map.erase(x->key.second);
		// remove y from min
        (y->left)->right = y->right;
        (y->right)->left = y->left;
        if (x->right == x)
            min = x;
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
        x->degree++; // incrementing x->degree
		y->mark = false;
        node_map[x->key.second] = x;
        node_map[y->key.second] = y;
    }
   private:
    void consolidate() {
        node_map.erase(min->key.second);
		float phi = (1+sqrt(5)) / 2; // golden ratio
        int d;
        float temp = (log(n)) / (log(phi));
        int D = floor(temp) + 1; // upper bound
        struct node* A[D];
        for (int i = 0; i < D; i++)
            A[i] = NULL;
        node* w = min; // for each node in min list
        node* y;
        node* swap; // pointer to swap x and y places
        node* x;
        do {
			x = w;
            d = x->degree;
            while (A[d] != NULL) {
                y = A[d];
				// exchange x and y places
                if (x->key.first > y->key.first) {
                    swap = x;
                    x = y;
                    y = swap;
                }
                if (y == min)
                    min = x;
                fiblink(y, x);
                if (x->right == x)
                    min = x;
                A[d] = NULL;
                d++;
            }
            A[d] = x;
            w = w->right; // move on w list
        } while (w != min); // while not first element in w list
        min = NULL;
        for (int i = 0; i < D; i++) {
            if (A[i] != NULL) {
                A[i]->left = A[i]; // make A[i] a circular list
                A[i]->right = A[i];
				if (min == NULL) {
					min = A[i]; // min list just contains A[i]
				} else {
					// add A[i] to min list
                    (min->left)->right = A[i];
                    A[i]->right = min;
                    A[i]->left = min->left;
                    min->left = A[i];
                    node_map[A[i]->key.second] = A[i];
					// update min
                    if (A[i]->key.first < min->key.first)
                        min = A[i];
                }
            }
        }
        node_map[min->key.second] = min;
    }
   public:
    /* deletes the element from heap whose key is minimum*/
    void extract() {
		node* z = min;
		node* x;
		x = z;
		node* childlist = NULL; // interpetrates child list
		if (z->child != NULL) {
			childlist = z->child;
			do {
				x = childlist->right;
				// add x to the rootlist min
                node_map.erase(childlist->key.second);
				(min->left)->right = childlist;
				childlist->right = min;
				childlist->left = min->left;
				min->left = childlist;
                node_map[childlist->key.second] = childlist;
				// update min
				if (childlist->key.first < min->key.first)
					min = childlist;
				childlist->p = NULL;
				childlist = x;
			} while (x != z->child); // while not the first element of childlist
		}
		// remove z from min
		(z->left)->right = z->right;
		(z->right)->left = z->left;
		min = z->right;
		if (z == z->right && z->child == NULL)
			min = NULL;
		else {
			min = z->right;
			consolidate();
		}
		n--;
        node_map.erase(z->key.second);
        delete z;
    }
   private:
    void cut(struct node* x, struct node* y) {
        node_map.erase(y->key.second);
        node_map.erase(x->key.second);
		// removing x from y childs
        if (x == x->right) // if found doesn't have siblings
            y->child = NULL; // temp doesn't have children
		// otherwise, remove x from y childlist
        (x->left)->right = x->right;
        (x->right)->left = x->left;
        if (x == y->child)
            y->child = x->right;
        y->degree = y->degree - 1; // decrementing y->degree
		// insert x in min (root list)
        x->right = x;
        x->left = x;
        (min->left)->right = x;
        x->right = min;
        x->left = min->left;
        min->left = x;
        x->p = NULL;
        x->mark = false;
        node_map[x->key.second] = x;
        node_map[y->key.second] = y;
    }
   private:
    void cascade_cut(struct node* y) {
        node* z = y->p;
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
    /* assigns the new key.first p to the node x, assuming is not greater than its current value */
    void decreaseKey(double p, int u) {
        node* x = node_map[u];
        x->key.first = p;
        struct node* y = x->p;
        if (y != NULL && x->key.first < y->key.first) {
            cut(x, y);
            cascade_cut(y);
        }
        if (x->key.first < min->key.first)
            min = x;
    }
   public:
    /* determine if the fibheap is empty */
    bool isEmpty() {
        if (min == NULL)
            return true;
        else
            return false;
    }
};