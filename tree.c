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
		if(node->tuple->length > tuple->length) {
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
					if(node->parent->tuple->length > node->tuple->length){
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
		}else if(node->tuple->length <= tuple->length) {
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
					if(node->parent->tuple->length > node->tuple->length){
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
		printf("ROOT: ");
		printf("%p \n",newNode->tuple->address);
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
node* deleteNode(node* node) {
	struct node* root = node;
	while(root->parent != NULL){
		root = root->parent;
	}
	//if node is leaf, just delete node
	if(node->left == NULL && node->right == NULL){
		if(node == node->parent->right){
			node->parent->right = NULL;
		} else {
			node->parent->left = NULL;
		}
		free(node);
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
			free(node->right);
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
			free(node->left);
		}
	}
	//Node to be deleted has two children: Find inorder successor of the node. 
	//Copy contents of the inorder successor to the node and delete the inorder successor. 
	//Note that inorder predecessor can also be used.
	if(node->left != NULL && node->right != NULL){
		struct node* replacement = maxValue(node->left);
		replacement->parent = node->parent;
		node->left = NULL;
		replacement->right = node->right;
		if(node->parent->right == node){
			node->parent->right = replacement;
		} else {
			node->parent->left = replacement;
		}
		free(node);
	}
	while(root->parent != NULL){
		root = root->parent;
	}
	return root;
}