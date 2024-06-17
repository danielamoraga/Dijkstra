#include<bits/stdc++.h>
using namespace std;
using element = pair<double, int>;

// A Binomial Tree node.
struct Node {
    element data; // (distance, node)
    int degree;
    Node *child, *sibling, *parent;
};

Node* newNode(element key) {
  Node *temp = new Node;
  temp->data = key;
  temp->degree = 0;
  temp->child = temp->parent = temp->sibling = NULL;
  return temp;
}

// This function merge two Binomial Trees.
Node* merge(Node *b1, Node *b2) {
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