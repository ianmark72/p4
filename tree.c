#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"

typedef struct node {
    tuple* tuple;
    int color; // 0 as black, 1 as red
    node* left;
    node* right;
    node* parent;
    int status; //0 if malloc, 1 if freed
} node;

typedef struct rootNode {
    node* root;
} rootNode;

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

rootNode* createTree(tuple* tuple) {
    node firstNode;
    firstNode = calloc(sizeof(node), 1);
    firstNode.color = 0;
    firstNode.left = NULL;
    firstNode.right = NULL;
    firstNode.parent = NULL;
    firstNode.tuple = tuple;
    firstNode.status = 0;

    rootNode root = calloc(sizeof(rootNode), 1);
    root.root = firstNode;
    return root;
}
