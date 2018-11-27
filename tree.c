#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    tuple* tuple;
    int color;
    node* left;
    node* right;
    node* parent;
} node;

void addNode(node* node, tuple* tuple) {
	if(node->tuple->address > tuple->address) {
		//Left
		if(node->left == NULL) {
			node* newNode = calloc(1, sizeof(node));
			newNode->color = 0;
			newNode->parent = node;
			newNode->left = NULL;
			newNode->right = NULL;
			newNode->tuple = tuple;
			node->left = newNode;
		}else{
			addNode(node->left, tuple);
		}
	}else if(node->tuple->address <= tuple->address) {
		//Right
		if(node->right == NULL) {
			node* newNode = calloc(1, sizeof(node));
                        newNode->color = 0;
                        newNode->parent = node;
                        newNode->left = NULL;
                        newNode->right = NULL;
                        newNode->tuple = tuple;
                        node->right = newNode;
		}else{
			addNode(node->right, tuple);
		}
	}
}
