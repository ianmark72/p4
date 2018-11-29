#ifndef TREE_H
#define TREE_H

#include "537malloc.h"
#include "structs.h"


void addNode(node* node, struct tuple* tuple);
rootNode* createTree(struct tuple* tuple); 

#endif /* TREE_H */

