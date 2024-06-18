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