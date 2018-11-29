#ifndef TREE_H
#define TREE_H

#include "537malloc.h"

typedef struct node {
    struct tuple* tuple;
    int color;
    struct node* left;
    struct node* right;
    struct node* parent;
    int status;
} node;

typedef struct rootNode {
    node* root;
} rootNode;

void addNode(node* node, struct tuple* tuple);
rootNode* createTree(struct tuple* tuple); 

#endif /* TREE_H */

