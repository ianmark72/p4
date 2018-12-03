#ifndef MALLOC_H
#define MALLOC_H

#include "structs.h"

void * malloc537(size_t size);
static node* findNode(void* ptr, node* node);
void free537(void *ptr);
static void checkNode(void *ptr, size_t size, node* node);
void memcheck537(void *ptr, size_t size);
void * realloc537(void *ptr, size_t size);
void printTuple(tuple* tuple);
void printNode(node* node);
int main();

#endif /* MALLOC_H */
