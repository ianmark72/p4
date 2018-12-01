#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"
#include "structs.h"

static node* root = NULL;

void * malloc537(size_t size) {
		//printf("inside malloc\n");
        tuple* tuple = malloc(sizeof(*tuple));
        tuple->address = malloc(size);
        tuple->length = size;

		//printf("tuple created\n");
		if(root != NULL) {
			addNode(root, tuple);
		}else{
			root = addNode(NULL, tuple);
		}
		//printf("End of malloc537\n");
		return tuple->address;
}

static node* findNode(void* ptr, node* node) {
	node* matchingNode = NULL;

	if(ptr == node->address) {
		matchingNode = node;
	}else{
		if(node->left != NULL) {
			matchingNode = findNode(ptr, node->left);
			if(matchingNode != NULL) {
				return matchingNode;
			}
		}
		if(node->right != NULL) {
			matchingNode = findNode(ptr, node->right);
			if(matchingNode != NULL) {
				return matchingNode;
			}
		}
	}

	return matchingNode;
}

void free537(void *ptr) {
	node* node = NULL;

	if(root != NULL) {
		node = findNode(ptr, root);
		if(node == NULL) {
			printf("Error: memory was not allocated by malloc537.\n");
			exit(-1);
		}
	} else {
		printf("Error: nothing has been allocated yet.\n");
		exit(-1);
	}

	if(node->status == 0) {
		printf("Error: memory has already been freed.\n");
		exit(-1);
	}

	free(ptr);
}

void memcheck537(void *ptr, size_t size) {
	if() {

	}
}

void * realloc537(void *ptr, size_t size) {


	if(ptr == NULL){
		if(size == 0) {
			malloc537(size);
		}else{
			free537(ptr);
		}
	}else {
		tuple* tuple = malloc(sizeof(tuple));

		tuple->address = realloc(ptr, size);
		tuple->length = size;
	}

	return NULL;
}
 
void printNode(node* node){ 
	printf("Address: %p\n",node->tuple->address);
	printf("Length: %li\n", node->tuple->length);
	printf("Color: %i\n", node->color);
	printf("Status: %i\n", node->status);

	if(node->parent != NULL){
		printf("Parent's Address: %p\n", node->parent->tuple->address);
	}
	else {
		printf("Parent's Address: NULL\n");
	}
	if(node->left != NULL) {
		printf("Left Address: %p\n", node->left->tuple->address);
	}
	else {
                printf("Left Address: NULL\n");
        }
	if(node->right != NULL) {
		printf("Right Address: %p\n", node->right->tuple->address);
	}
	else {
                printf("Right Address: NULL\n");
        }
	printf("========================================\n");
	if(node->left != NULL) {
		printNode(node->left);
	}

	if(node->right != NULL) {
		printNode(node->right);
	}
}

int main() {
	//printf("Start\n");
	malloc537(40);
	malloc537(40);
	malloc537(25);
	malloc537(30);
	malloc537(69);

	//Test Printing 
	printNode(root);
}
