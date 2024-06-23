#include<bits/stdc++.h>
using namespace std;
using element = pair<double, int>;

// Fuente: https://www.geeksforgeeks.org/fibonacci-heap-deletion-extract-min-and-decrease-key/

// Creating a structure to represent a node in the heap
struct node {
    node* p;  // parent pointer
    node* child;   // child pointer
    node* left;    // pointer to the node on the left
    node* right;   // pointer to the node on the right
    element key;   // value of the node
    int degree;    // degree of the node
    bool mark;     // true or false mark of the node
};

struct fibheap {
    node* min = NULL; // creating min pointer
    int n = 0; // declare an integer for number of nodes in the heap
    unordered_map<int, node*> node_map; // map to keep pointers associated to node numbers

   public:
    /* inserts element e creating a node x with that key */
    void insert(element e) {
        struct node* x = new node();
        x->key = e;
        x->degree = 0;
        x->p = NULL;
        x->child = NULL;
        x->mark = false;
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
    }
   private:
    void cut(struct node* x, struct node* y) {
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
    /* assigns the new key.first value to the node u, assuming is not greater than its current value */
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