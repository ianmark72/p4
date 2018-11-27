#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    tuple* tuple;
    int color;
    node* left;
    node* right;
    node* parent;
} node;