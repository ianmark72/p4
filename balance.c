#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include "tree.h"
#include "structs.h"

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
		grandparent->parent->left = parent;
		parent->parent = grandparent->parent;
		grandparent->parent = parent;
	}else{
		grandparent->parent = parent;
		parent->parent = NULL;
	}

	if(parent->right != NULL) {
		grandparent->left = parent->right;
	}else{
		grandparent->left = NULL;
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
	child->left = parent;

	parent->right = NULL;
	parent->parent = child;
        
	leftleftcase(child, grandparent);
}

void rightrightcase(node* parent, node* grandparent) {     
	if(grandparent->parent != NULL) {
		grandparent->parent->right = parent;
                parent->parent = grandparent->parent;
                grandparent->parent = parent;
        }else{
                grandparent->parent = parent;
                parent->parent = NULL;
        }

	if(parent->left != NULL) {
		grandparent->right = parent->left;
	}else{
		grandparent->right = NULL;
	}

	parent->left = grandparent;
        parent->color = 0;

        grandparent->color = 1;
        }

void rightleftcase(node* child, node* parent, node* grandparent) {
	grandparent->right = child;
        child->parent = grandparent;
	child->right = parent;

        parent->left = NULL;
        parent->parent = child;

        rightrightcase(child, grandparent);
}

void balanceTree(node* newNode, int path){
        while(newNode->parent != NULL && newNode->parent->color == 1) {
	//Check if uncle exists.
                struct node* uncle;
                if(newNode->parent == newNode->parent->parent->left){
                        uncle = newNode->parent->parent->right;
                }
                else {
                        uncle = newNode->parent->parent->left;
                }
                //Case: Recoloring
                //Change color of parent and uncle to black and grandparent to red, move newnode to grandparent
                if(uncle != NULL) {
			if(uncle->color == 1) {
				uncle->color = 0;
				newNode->parent->color = 0;
				newNode->parent->parent->color = 1;
				newNode = newNode->parent->parent;
			}else{
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
			}
                }else{
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
                }
        }
        struct node* root;
        root = findRoot(newNode);
        root->color = 0; //paint root black
	}
