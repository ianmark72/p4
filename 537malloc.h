#ifndef MALLOC_H
#define MALLOC_H

#include "structs.h"

void * malloc537(size_t size);
void free537(void *ptr);
void memcheck537(void *ptr, size_t size);
void * realloc537(void *ptr, size_t size);
void printTuple(tuple* tuple);
void printNode(node* node);

#endif /* MALLOC_H */
