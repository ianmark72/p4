#ifndef BALANCE_H
#define BALANCE_H
int checkSide(node* child, node* parent);
void leftleftcase(node* parent, node* grandparent);
void leftrightcase(node* child, node* parent, node* grandparent);
void rightrightcase(node* parent, node* grandparent);
void rightleftcase(node* child, node* parent, node* grandparent);
void balanceTree(node* newNode, node* uncle, int path);
#endif /* BALANCE_H */