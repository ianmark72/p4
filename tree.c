#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include "structs.h"
#include "balance.h"


node* addNode(node* node, tuple* tuple) {
	//Path 0 = left-left, 1 = left-right, 2 = right-left, 3 = right-right
	struct node* newNode = malloc(sizeof(*node));
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
				// if(node->parent->tuple->address > node->tuple->address){
				// //	balanceTree(newNode, node->right,0);
				// }
				// else {
				// //	balanceTree(newNode, node->right,2);
				// }
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
				// if(node->parent->tuple->address > node->tuple->address){
				// 	balanceTree(newNode, node->left,1);
				// }
				// else {
				// 	balanceTree(newNode, node->left,3);
				// }
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
