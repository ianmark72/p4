#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct tuple {
        int* address;
        int length;
} tuple;
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
#endif /* STRUCTS_H */