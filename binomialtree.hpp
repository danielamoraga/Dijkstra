#include<bits/stdc++.h>
using namespace std;
using element = pair<double, int>;

// A Binomial Tree node.
struct node {
    element data; // valor del nodo, par (distance, node) del grafo
    int degree;
    node *child, *sibling, *parent;
};

node* newNode(element key) {
  node *temp = new node;
  temp->data = key;
  temp->degree = 0;
  temp->child = temp->parent = temp->sibling = NULL;
  return temp;
}

// This function merge two Binomial Trees.
node* merge(node *b1, node *b2) {
  // Make sure b1 is smaller
  if (b1->data.first > b2->data.first)
    swap(b1, b2);

  // We basically make larger valued tree
  // a child of smaller valued tree
  b2->parent = b1;
  b2->sibling = b1->child;
  b1->child = b2;
  b1->degree++;

  return b1;
}

/* search: busca un nodo de valor x en un árbol binomial */
node* search(int x, node* B) {
    if (B == NULL) return NULL;
    if (x == B->data.second) return B;
    else if (x < B->data.second) search(x, B->child);
  }


/*
Decrease-Key:
1. Select the node to be decreased, x, and change its value to the new value k.
2. If the parent of x, y, is not null and the key of parent is greater than that of the k then call Cut(x) and Cascading-Cut(y) subsequently.
3. If the key of x is smaller than the key of min, then mark x as min.

Cut:
1. Remove x from the current position and add it to the root list.
2. If x is marked, then mark it as false.

Cascading-Cut:
1. If the parent of y is not null then follow the following steps.
2. If y is unmarked, then mark y.
3. Else, call Cut(y) and Cascading-Cut(parent of y).
*/