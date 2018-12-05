#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "structs.h"

static node* root = NULL;

static node* findNode(void* ptr, node* node) {
	struct node* matchingNode = NULL;

	if((node->tuple->address <= ptr && (node->tuple->address + node->tuple->length) > ptr)) {
		matchingNode = node;
	}else{
		if(node->left != NULL && node->tuple->address > ptr ) {
			matchingNode = findNode(ptr, node->left);
			if(matchingNode != NULL) {
				return matchingNode;
			}
		}
		if(node->right != NULL && node->tuple->address < ptr) {
			matchingNode = findNode(ptr, node->right);
			if(matchingNode != NULL) {
				return matchingNode;
			}
		}
	}

	return matchingNode;
}

//(node->tuple->address <= ptr && (node->tuple->address + node->tuple->length) > ptr) || (node->tuple->address <= (ptr + size) && (node->tuple->address + node->tuple->length) > (ptr + size))

static int findNodeRange(void* ptr, size_t size, node* node) {
	int found = 0;
	//FIX NEWLINE

	if(ptr <= node->tuple->address && node->tuple->address < (ptr + size) ) {
		root = deleteNode(node);
		return 1;
	}else if(ptr > node->tuple->address && ptr < (node->tuple->address + node->tuple->length)) {
		node->tuple->length = ptr - node->tuple->address;
		return 1;
	}else{
		if(node->left != NULL && node->tuple->address > ptr ) {
			found = findNodeRange(ptr, size, node->left);
			if(found == 1) {
				return 1;
			}
		}
		if(node->right != NULL && node->tuple->address < ptr) {
			found = findNodeRange(ptr, size, node->right);
			if(found == 1) {
				return 1;
			}
		}
	}

	return found;
}

void * malloc537(size_t size) {
	// if malloc returns an address of a freed node, delete the free node 
	// mallocs return, if that malloc return overlaps with a free node, we need to delete 
		//printf("inside malloc\n");
		int found = 1;

		if(size == 0) {
			printf("Warning: Allocating block of size 0\n");
		}
        tuple* tuple = malloc(sizeof(*tuple));
        tuple->address = malloc(size);
        tuple->length = size;
		// printf("New ");
		// printTuple(tuple);
		if(root != NULL) {
			while(found == 1) {
				found = findNodeRange(tuple->address, size, root);
			}
		}
		if(root != NULL) {
			 addNode(root, tuple);
		}else{
			root = addNode(NULL, tuple);
		}
		root = findRoot(root);
		return tuple->address;
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
	free(ptr);
}

void memcheck537(void *ptr, size_t size) {
	//checkNode(ptr, size, root);
	struct node* node = findNode(ptr, root);

	if(ptr < node->tuple->address || (ptr + size) > (node->tuple->address + node->tuple->length)) {
		printf("Error: Memory allocated outside of range.\n");
		exit(-1);
	}
}

void * realloc537(void *ptr, size_t size) {
	node* node = NULL;
	int found = 0;
	tuple* tuple = malloc(sizeof(tuple));

	if(ptr == NULL){
		tuple->address = malloc537(size);
	}else {
		if(size == 0) {
			//Not an error but worth reporting(piazza).
			printf("Warning: size equal to zero.\n");
			free(ptr);
			ptr = NULL;
		}else{
			node = findNode(ptr, root);
			if(node->status == 0) {
					printf("Error: memory has already been freed");
					exit(-1);
			}
			if(ptr != node->tuple->address) {
				printf("Error: realloc not at the start of an allocation");
				exit(-1);
			}

			//two ways: one: update node if adress doesnt change or delete and make new Two: always delete and make new			
			root = deleteNode(node);

			tuple->address = realloc(ptr, size);
			tuple->length = size;
			while(found == 1) {
				found = findNodeRange(tuple->address, size, root);
			}
			if(root != NULL) {
				addNode(root, tuple);
			}else{
				root = addNode(NULL, tuple);
			}
			root = findRoot(root);
		}
	}

	return tuple->address;
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
