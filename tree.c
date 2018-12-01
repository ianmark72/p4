#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include "structs.h"


node* addNode(node* node, tuple* tuple) {
	struct node* newNode = malloc(sizeof(node));

	if(node != NULL) {
		if(node->tuple->address > tuple->address) {
			//Left
			if(node->left == NULL) {

				newNode->color = 0;
				newNode->parent = node;
				newNode->left = NULL;
				newNode->right = NULL;
				newNode->tuple = tuple;
				node->left = newNode;
				newNode->status = 1;
			}else{
				addNode(node->left, tuple);
			}
		}else if(node->tuple->address <= tuple->address) {
			//Right
			if(node->right == NULL) {
                newNode->color = 0;
                newNode->parent = node;
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->tuple = tuple;
                node->right = newNode;
				newNode->status = 1;
			}else{
				addNode(node->right, tuple);
			}
		}
	} else {
		//Root Node
		newNode->color = 0;
		//newNode->parent = NULL;
		//newNode->left = NULL;
		//newNode->right = NULL;
		newNode->tuple = tuple;
		newNode->status = 1;
	}
	
	return newNode;
}

int checkSide(node* child, node* parent) {
	//0 = left, 1 = right, -1 = error
	int returnValue = -1;
	
	if(child == parent->left) {
		returnValue = 0;
	}else if(child == parent->right) {
		returnValue = 1;
	}

	return returnValue;
}

void leftleftcase(node* parent, node* grandparent) {
	if(grandparent->parent != NULL) {
		parent->parent = grandparent->parent;
	}else{
		parent->parent = NULL;
	}
	parent->right = grandparent;
        parent->color = 0;

	grandparent->parent = parent;
	grandparent->left = NULL;
	grandparent->color = 1;
}

void leftrightcase(node* child, node* parent, node* grandparent) {
	grandparent->left = child;
	child->parent = grandparent;

	parent->right = NULL;
	parent->parent = child;

	leftleftcase(child, grandparent);
}

void rightrightcase(node* parent, node* grandparent) {
	if(grandparent->parent != NULL) {
                parent->parent = grandparent->parent;
        }else{
                parent->parent = NULL;
        }
	parent->left = grandparent;
        parent->color = 0;

        grandparent->parent = parent;
	grandparent->right = NULL;
        grandparent->color = 1;
}

void rightleftcase(node* child, node* parent, node* grandparent) {
	grandparent->right = child;
        child->parent = grandparent;

        parent->left = NULL;
        parent->parent = child;

        rightrightcase(child, grandparent);
}

void balanceTree(node* newNode, node* uncle, int path, node* rootNode) {
	//Path 0 = left-left, 1 = left-right, 2 = right-left, 3 = right-right 

	//Check if uncle exists.
	if(uncle != NULL) {
		if(uncle->color == 0) {
			//Uncle is black
			switch(path) {
			case 0:
				leftleftcase(newNode->parent, newNode->parent->parent);
				break;
			case 1:
				leftrightcase(newNode, newNode->parent, newNode->parent->parent);
				break;
			case 2:
				rightleftcase(newNode, newNode->parent, newNode->parent->parent);
				break;
			case 3:
				rightrightcase(newNode->parent, newNode->parent->parent);
				break;
			}
		}else{
			//Uncle is red
			if(newNode->parent->color == 1){
				newNode->parent->color = 0;
			}	
			uncle->color = 0;

			if(newNode->parent->parent != rootNode) {
				newNode->parent->parent->color = 1; 
			}
		}
	}
}
