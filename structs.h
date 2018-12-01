#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct tuple {
        void* address;
        size_t length;
} tuple;

typedef struct node {
    struct tuple* tuple;
    int color;
    struct node* left;
    struct node* right;
    struct node* parent;
    int status; //1 if allocated, 0 means free
} node;

#endif /* STRUCTS_H */