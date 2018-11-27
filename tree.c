#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    tuple* tuple;
    int color; // 0 as black, 1 as red
    node* left;
    node* right;
    node* parent;
    int status; //0 if malloc, 1 if freed
} node;
typedef struct rootNode {
    node* root;
} rootNode;

rootNode* createTree(tuple* tuple) {
    node firstNode;
    firstNode = calloc(sizeof(node), 1);
    firstNode.color = 0;
    firstNode.left = NULL;
    firstNode.right = NULL;
    firstNode.parent = NULL;
    firstNode.tuple = tuple;
    firstNode.status = 0;

    rootNode root = calloc(sizeof(rootNode), 1);
    root.root = firstNode;
    return root;
}