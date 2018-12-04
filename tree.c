#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include "structs.h"
#include "balance.h"


node* addNode(node* node, tuple* tuple) {
	//Path 0 = left-left, 1 = left-right, 2 = right-left, 3 = right-right
	struct node* newNode = calloc(1,sizeof(*node));
	if(node != NULL) {
		// MAKE SURE TO CHANGE BACK TO ADDRESS
		if(node->tuple->address > tuple->address) {
			//Left
			if(node->left == NULL) {

				newNode->color = 1;
				newNode->parent = node;
				newNode->left = NULL;
				newNode->right = NULL;
				newNode->tuple = tuple;
				node->left = newNode;
				newNode->status = 1;
				if (node->parent != NULL){
					// MAKE SURE TO CHANGE BACK TO ADDRESS
					if(node->parent->tuple->address > node->tuple->address){
						balanceTree(newNode, 0);
					}
					else {
						balanceTree(newNode, 2);
					}
				}
			}else{
				addNode(node->left, tuple);
			}
			// MAKE SURE TO CHANGE BACK TO ADDRESS
		}else if(node->tuple->address <= tuple->address) {
			//Right
			if(node->right == NULL) {
                		newNode->color = 1;
                		newNode->parent = node;
                		newNode->left = NULL;
                		newNode->right = NULL;
                		newNode->tuple = tuple;
                		node->right = newNode;
				newNode->status = 1;
				if (node->parent != NULL) {
					// MAKE SURE TO CHANGE BACK TO ADDRESS
					if(node->parent->tuple->address > node->tuple->address){
						balanceTree(newNode, 1);
						//printf("%p ",newNode->tuple->address);
					}
					else {
						balanceTree(newNode, 3);
						// printf("%p ",newNode->tuple->address);
					}
				}
			}else{
				addNode(node->right, tuple);
			}
		}
	} else {
		//Root Node
		newNode->color = 0;
		newNode->parent = NULL;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->tuple = tuple;
		newNode->status = 1;
		// printf("ROOT: ");
		// printf("%p \n",newNode->tuple->address);
	}
	
	return newNode;
}
node* findRoot(node* node){
	while(node->parent != NULL){
		node = node->parent;
	}
	return node;
}

node* maxValue(node* node){
	struct node* curr = node;
	while(curr->right != NULL){
		curr = curr->right;
	}
	return curr;
}

void llRotation(node* parent, node* sibling, node* childR) {
	parent->parent = sibling;
	sibling->parent = NULL;

	if(childR != NULL) {
		parent->left = childR;
		childR->parent = parent;
	}else{
		parent->left = NULL;
	}

	//siblings->left = parent;
	//childL->color = 0;
}

void lrRotation(node* parent, node* sibling, node* childR) {
	parent->left = childR;
	childR->parent = parent;

	childR->left = sibling;
	sibling->parent = childR;

	//childR->color = 0;
	//sibling->color = 1;

	llRotation(parent, childR, sibling);
}

void rrRotation(node* parent, node* sibling, node* childL) {
	parent->parent = sibling;
	sibling->parent = NULL;

	if(childL != NULL) {
		parent->right = childL;
		childL->parent = parent;
	}else{
		parent->right = NULL;
	}

	//siblings->left = parent;
	//childR->color = 0;
}

void rlRotation(node* parent, node* sibling, node* childL) {
	parent->right = childL;
	childL->parent = parent;

	childL->right = sibling;
	sibling->parent = childL;

	//childL->color = 0;
	//sibling->color = 1;

	rrRotation(parent, childL, sibling);
}

void doubleBlack(node* node) {
	if(node->parent == NULL) {
		node->color = 0;
		return;
	}

	int side = checkSide(node, node->parent);

	struct node* parent = node->parent;
	struct node* sibling;
	struct node* childL;
	struct node* childR;
	//0 = no children, 1 = left child only, 2 = right child only, 3 = both children
	int children = 0;

	//Get the parent, sibling, and its children
	if(side == 0) {
		if(parent->right != NULL) {
			sibling	= node->parent->right;
			if(sibling->left != NULL) {
				childL = sibling->left;
				children += 1;
			}
			if(sibling->right != NULL) {
				childR = sibling->right;
				children += 2;
			}
		}else{
			doubleBlack(parent);
			return;
		}

		if(sibling->color == 0) {
			//Sibling is black
			switch(children) {
				case 0:
					//No children exists
					sibling->color = 1;
					doubleBlack(parent);
					return;
					break;
				case 1:
					if(childL->color == 1) {
						rlRotation(parent, sibling, childL);					
						childL->color = 0;
						doubleBlack(childL);
						return;
					}else{
						sibling->color = 1;
						doubleBlack(parent);
						return;
					}
					break;
				case 2:
					if(childR->color == 1) {
						rrRotation(parent, sibling, childL);
						childR->color = 0;
						doubleBlack(sibling);
						return;
					}else{
						sibling->color = 1;
						doubleBlack(parent);
						return;
					}
					break;
				case 3:
					if(childR->color == 1) {
						//Two children, right child is red
						rrRotation(parent, sibling, childL);
						childR->color = 0;
						doubleBlack(sibling);
						return;
					}else if(childL->color == 1) {
						//Two children, right is black but left is red
						rlRotation(parent, sibling, childL);
						childL->color = 0;
						doubleBlack(childL);
						return;
					}else{
						//Both children are black
						sibling->color = 1;
						doubleBlack(parent);
						return;
					}
					break;
				}
		} else {
			//Sibling is red
			parent->color = 1;
			sibling->color = 0;
			rrRotation(parent, sibling, childL);
			doubleBlack(node);
			return;	
		}
	} else {
		if(parent->left != NULL) {
			sibling	= node->parent->left;
			if(sibling->left != NULL) {
				childL = sibling->left;
				children += 1;
			}
			if(sibling->right != NULL) {
				childR = sibling->right;
				children += 2;
			}
		}else{
			doubleBlack(parent);
			return;
		}

		if(sibling->color == 0) {
			//Sibling is black
			switch(children) {
				case 0:
					//No children exists
					sibling->color = 1;
					doubleBlack(parent);
					return;
					break;
				case 1:
					if(childL->color == 1) {
						llRotation(parent, sibling, childR);
						childL->color = 0;
						doubleBlack(sibling);
						return;
					}else{
						sibling->color = 1;
						doubleBlack(parent);
						return;
					}
					break;
				case 2:
					if(childR->color == 1) {
						lrRotation(parent, sibling, childR);
						childR->color = 0;
						doubleBlack(childR);
						return;
					}else{
						sibling->color = 1;
						doubleBlack(parent);
						return;
					}
					break;
				case 3:
					if(childL->color == 1) {
						//Two children, right child is red
						llRotation(parent, sibling, childR);
						childL->color = 0;
						doubleBlack(sibling);
						return;
					}else if(childR->color == 1) {
						//Two children, right is black but left is red
						lrRotation(parent, sibling, childR);
						childR->color = 0;
						doubleBlack(childR);
						return;
					}else{
						//Both children are black
						sibling->color = 1;
						doubleBlack(parent);
						return;
					}
					break;
				}
		} else {
			//Sibling is red
			parent->color = 1;
			sibling->color = 0;
			llRotation(parent, sibling, childR);
			doubleBlack(node);
			return;	
		}		
	}

}

node* deleteNode(node* node) {
	struct node* root = node;
	int side = -1; // 0 if left, 1 if right
	int uColor = 0;

	while(root->parent != NULL){
		root = root->parent;
	}
	//which side ???
	if(node->parent->left == node) {
		side = 0;
	} else {
		side = 1;
	}
	//if node is leaf, just delete node
	if(node->left == NULL && node->right == NULL){
		if(node == node->parent->right){
			node->parent->right = NULL;
		} else {
			node->parent->left = NULL;
		}
	}
	//Node has one child. 
	if((node->left != NULL && node->right ==NULL) || (node->left == NULL && node->right != NULL)){
		if(node->left == NULL){
			//set node parent equal to node child, and set child parent to be grandparent
			if(node->parent->right == node){
				//right side
			node->right->parent = node->parent;
			node->parent->right = node->right;
			}
			else {
				node->right->parent = node->parent;
				node->parent->left = node->right;
			}
		} else {
			//left side
			if(node->parent->right == node){
			node->left->parent = node->parent;
			node->parent->right = node->left;
			}
			else {
				node->left->parent = node->parent;
				node->parent->left = node->left;
			}
		}
	}
	//Node to be deleted has two children: Find inorder successor of the node. 
	//Copy contents of the inorder successor to the node and delete the inorder successor. 
	//Note that inorder predecessor can also be used.
	if(node->left != NULL && node->right != NULL){
		struct node* replacement = maxValue(node->left);
		replacement->parent = node->parent;
		node->left = NULL;
		node->right->parent = replacement;
		replacement->right = node->right;
		if(node->parent->right == node){
			node->parent->right = replacement;
		} else {
			node->parent->left = replacement;
		}
	}

	struct node* u;
	if(node->left == NULL){
		u = node->right;
	} else if(node->right == NULL) {
		u = node->left;
	}
	
	if(u == NULL) {
		uColor = 0;
	}else{
		uColor = u->color;
	}

	if(uColor == 1 || node->color == 1){
		if(u != NULL) {
			if (side == 1) {
				node->parent->right->color = 0;
			} else {
				node->parent->left->color = 1;
			}
		} 
	}
	if (uColor == 0 && node->color == 0){
		doubleBlack(node);
	}

	free(node);
	while(root->parent != NULL){
		root = root->parent;
	}
	return root;
}