#ifndef TREE_H
#define TREE_H

#include "537malloc.h"
#include "structs.h"


node* addNode(node* node, struct tuple* tuple);
node* findRoot(node* node);
node* maxValue(node* node);
void llRotation(node* parent, node* sibling, node* childR);
void lrRotation(node* parent, node* sibling, node* childR);
void rrRotation(node* parent, node* sibling, node* childL);
void rlRotation(node* parent, node* sibling, node* childL);
void doubleBlack(node* node);
node* deleteNode(node* node);

#endif /* TREE_H */

