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

// Creating a structure to represent a node in the heap
struct node {
    node* parent;  // Parent pointer
    node* child;   // Child pointer
    node* left;    // Pointer to the node on the left
    node* right;   // Pointer to the node on the right
    element key;   // Value of the node
    int degree;    // Degree of the node
    char mark;     // Black or white mark of the node
    char c;        // Flag for assisting in the Find node function
};

struct fibheap {
    // Creating min pointer as "mini"
    node* mini = NULL;
    // Declare an integer for number of nodes in the heap
    int no_of_nodes = 0;

    // Function to insert a node in heap
   public:
    void insert(element val) {
        struct node* new_node = new node();
        new_node->key = val;
        new_node->degree = 0;
        new_node->mark = 'W';
        new_node->c = 'N';
        new_node->parent = NULL;
        new_node->child = NULL;
        new_node->left = new_node;
        new_node->right = new_node;
        if (mini != NULL) {
            (mini->left)->right = new_node;
            new_node->right = mini;
            new_node->left = mini->left;
            mini->left = new_node;
            if (new_node->key.first < mini->key.first)
                mini = new_node;
        } else {
            mini = new_node;
        }
        no_of_nodes++;
    }
    // Finding the minimum distance value node
   public:
    element find() {
        return mini->key;
    }
    // Linking the heap nodes in parent child relationship
   private:
    void fiblink(struct node* ptr2, struct node* ptr1) {
        (ptr2->left)->right = ptr2->right;
        (ptr2->right)->left = ptr2->left;
        if (ptr1->right == ptr1)
            mini = ptr1;
        ptr2->left = ptr2;
        ptr2->right = ptr2;
        ptr2->parent = ptr1;
        if (ptr1->child == NULL)
            ptr1->child = ptr2;
        ptr2->right = ptr1->child;
        ptr2->left = (ptr1->child)->left;
        ((ptr1->child)->left)->right = ptr2;
        (ptr1->child)->left = ptr2;
        if (ptr2->key.first < (ptr1->child)->key.first)
            ptr1->child = ptr2;
        ptr1->degree++;
    }
    // Consolidating the heap
   private:
    void consolidate() {
        int temp1;
        float temp2 = (log(no_of_nodes)) / (log(2));
        int temp3 = temp2;
        struct node* arr[temp3 + 1];
        for (int i = 0; i <= temp3; i++)
            arr[i] = NULL;
        node* ptr1 = mini;
        node* ptr2;
        node* ptr3;
        node* ptr4 = ptr1;
        do {
            ptr4 = ptr4->right;
            temp1 = ptr1->degree;
            while (arr[temp1] != NULL) {
                ptr2 = arr[temp1];
                if (ptr1->key.first > ptr2->key.first) {
                    ptr3 = ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr3;
                }
                if (ptr2 == mini)
                    mini = ptr1;
                fiblink(ptr2, ptr1);
                if (ptr1->right == ptr1)
                    mini = ptr1;
                arr[temp1] = NULL;
                temp1++;
            }
            arr[temp1] = ptr1;
            ptr1 = ptr1->right;
        } while (ptr1 != mini);
        mini = NULL;
        for (int j = 0; j <= temp3; j++) {
            if (arr[j] != NULL) {
                arr[j]->left = arr[j];
                arr[j]->right = arr[j];
                if (mini != NULL) {
                    (mini->left)->right = arr[j];
                    arr[j]->right = mini;
                    arr[j]->left = mini->left;
                    mini->left = arr[j];
                    if (arr[j]->key.first < mini->key.first)
                        mini = arr[j];
                } else {
                    mini = arr[j];
                }
                if (mini == NULL)
                    mini = arr[j];
                else if (arr[j]->key.first < mini->key.first)
                    mini = arr[j];
            }
        }
    }
    // Function to extract minimum node in the heap
   public:
    void extract() {
        if (mini == NULL)
            cout << "The heap is empty" << endl;
        else {
            node* temp = mini;
            node* pntr;
            pntr = temp;
            node* x = NULL;
            if (temp->child != NULL) {
                x = temp->child;
                do {
                    pntr = x->right;
                    (mini->left)->right = x;
                    x->right = mini;
                    x->left = mini->left;
                    mini->left = x;
                    if (x->key.first < mini->key.first)
                        mini = x;
                    x->parent = NULL;
                    x = pntr;
                } while (pntr != temp->child);
            }
            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            mini = temp->right;
            if (temp == temp->right && temp->child == NULL)
                mini = NULL;
            else {
                mini = temp->right;
                consolidate();
            }
            no_of_nodes--;
        }
    }
    // Cutting a node in the heap to be placed in the root list
   private:
    void cut(struct node* found, struct node* temp) {
        if (found == found->right)
            temp->child = NULL;

        (found->left)->right = found->right;
        (found->right)->left = found->left;
        if (found == temp->child)
            temp->child = found->right;

        temp->degree = temp->degree - 1;
        found->right = found;
        found->left = found;
        (mini->left)->right = found;
        found->right = mini;
        found->left = mini->left;
        mini->left = found;
        found->parent = NULL;
        found->mark = 'B';
    }
    // Recursive cascade cutting function
   private:
    void cascade_cut(struct node* temp) {
        node* ptr5 = temp->parent;
        if (ptr5 != NULL) {
            if (temp->mark == 'W') {
                temp->mark = 'B';
            } else {
                cut(temp, ptr5);
                cascade_cut(ptr5);
            }
        }
    }
    // Function to decrease the value of a node in the heap
   private:
    void decrease_key(struct node* found, double val) {
        if (mini == NULL)
            cout << "The Heap is Empty" << endl;

        if (found == NULL)
            cout << "Node not found in the Heap" << endl;

        found->key.first = val;

        struct node* temp = found->parent;
        if (temp != NULL && found->key.first < temp->key.first) {
            cut(found, temp);
            cascade_cut(temp);
        }
        if (found->key.first < mini->key.first)
            mini = found;
    }
    // Function to find the given node
   private:
    void find(struct node* mini, int old_val, double val) {
        struct node* found = NULL;
        node* temp5 = mini;
        temp5->c = 'Y';
        node* found_ptr = NULL;
        if (temp5->key.second == old_val) {
            found_ptr = temp5;
            temp5->c = 'N';
            found = found_ptr;
            decrease_key(found, val);
        }
        if (found_ptr == NULL) {
            if (temp5->child != NULL)
                find(temp5->child, old_val, val);
            if ((temp5->right)->c != 'Y')
                find(temp5->right, old_val, val);
        }
        temp5->c = 'N';
        found = found_ptr;
    }
    // Decreasing the distance key if node with key u
   public:
    void decreaseKey(double p, int u) {
        find(mini, u, p);
    }
    // Deleting a node from the heap
   private:
    void deletion(int val) {
        if (mini == NULL)
            cout << "The heap is empty" << endl;
        else {
            // Decreasing the value of the node to 0
            find(mini, val, 0);
            // Calling Extract_min function to
            // delete minimum value node, which is 0
            extract();
            cout << "Key Deleted" << endl;
        }
    }
    // See if a fibheap is empty
   public:
    bool isEmpty() {
        if (mini == NULL)
            return true;
        else
            return false;
    }
};

// Fuente: https://www.geeksforgeeks.org/fibonacci-heap-deletion-extract-min-and-decrease-key/