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
		printf("New ");
		printTuple(tuple);
		//printf("tuple created\n");
		if(root != NULL) {
			 addNode(root, tuple);
		}else{
			root = addNode(NULL, tuple);
		}
		root = findRoot(root);
		return tuple->address;
}

static node* findNode(void* ptr, node* node) {
	struct node* matchingNode = NULL;

	if(node->tuple->address <= ptr && (node->tuple->address + node->tuple->length) > ptr) {
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
		if(ptr != node->tuple->address) {
			printf("Error: address is not the start of block of allocated memory.\n");
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

	node->status = 0;
	deleteNode(node);
	free(ptr);
}

static void checkNode(void *ptr, size_t size, node* node) {
	if(ptr < node->tuple->address || ptr >= (node->tuple->address + node->tuple->length)) {
		printf("Error: Memory allocated outside of range.\n");
		exit(-1);
	}

	if(node->left != NULL) {
		checkNode(ptr, size, node->left);
	}
	if(node->right != NULL) {
		checkNode(ptr, size, node->right);
	}
}

void memcheck537(void *ptr, size_t size) {
	checkNode(ptr, size, root);
}

void * realloc537(void *ptr, size_t size) {
	node* node = NULL;

	if(ptr == NULL){
		//Not an error but worth reporting(piazza).
		if(size == 0) {
			printf("Warning: size equal to zero.\n");
		}
		malloc537(size);
	}else {
		if(size == 0) {
			//Not an error but worth reporting(piazza).
			printf("Warning: size equal to zero.\n");
			free(ptr);
		}else{
			node = findNode(ptr, root);
			int oldSize = node->tuple->length;
			//Delete node

			tuple* tuple = malloc(sizeof(tuple));

			tuple->address = realloc(ptr, size);
			tuple->length = size;
		}
	}

	return NULL;
}
 void printTuple(tuple* tuple) {
	 printf("Tuple: (%ld,%p)\n",tuple->length,tuple->address);
 }
void printNode(node* node){ 
	printf("========================================\n");
	printf("Address: %p\n",node->tuple->address);
	printf("Length: %li\n", node->tuple->length);
	printf("Color: %i\n", node->color);
	printf("Status: %i\n", node->status);

	if(node->parent != NULL){
		printf("Parent ");
		printTuple(node->parent->tuple);
	}
	else {
		printf("Parent's Address: NULL\n");
	}
	if(node->left != NULL) {
		printf("Left ");
		printTuple(node->left->tuple);
	}
	else {
                printf("Left Address: NULL\n");
        }
	if(node->right != NULL) {
		printf("Right ");
		printTuple(node->right->tuple);
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
	void * ptr0;
	void* ptr1;
	//void* ptr2;
	//void* ptr3;
	//void* ptr4;

	//printf("Start\n");
	ptr1 = malloc537(40);
	ptr0 = malloc537(39);
	//ptr2 = malloc537(41);
	//ptr3 = malloc537(42);
	//ptr4 = malloc537(43);
	
	free537(ptr0);

	
	//Test Printing 
	printNode(root);
}
