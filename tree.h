#ifndef TREE_H
#define TREE_H

#include "537malloc.h"
#include "structs.h"


node* addNode(node* node, struct tuple* tuple);
node* findRoot(node* node);
node* maxValue(node* node);
node* deleteNode(node* node);

#endif /* TREE_H */

