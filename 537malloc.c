#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "structs.h"

static node* root = NULL;

void * malloc537(size_t size) {
		//printf("inside malloc\n");
        tuple* tuple = malloc(sizeof(*tuple));
        tuple->address = malloc(size);
		printf("%li\n", sizeof(*tuple));
		printf("%li\n", sizeof(int*));
		printf("%li\n", sizeof(size_t));
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

void free537(void *ptr) {
	
	free(ptr);
}

void memcheck537(void *ptr, size_t size) {

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
	printf("Address: %i\n", node->tuple->address);
	printf("Length: %i\n", node->tuple->length);
	printf("Color: %i\n", node->color);
	printf("Status: %i\n", node->status);

	if(node->parent != NULL){
		printf("Parent's Address: %i\n", node->parent->tuple->address);
	}
	if(node->left != NULL) {
		printf("Left Address: %i\n", node->left->tuple->address);
	}
	if(node->right != NULL) {
		printf("Right Address: %i\n", node->right->tuple->address);
	}

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

	//Test Printing 
	printNode(root);
}
