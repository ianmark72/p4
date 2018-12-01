#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "structs.h"


void malloc537(size_t size) {
        tuple* tuple = malloc(sizeof(tuple));

        tuple->address = malloc(size);
        tuple->length = size;

		return tuple->address;
}

void free537(void *ptr) {
	
	free(ptr);
}

void memcheck537(void *ptr, size_t size) {

}

void realloc537(void *ptr, size_t size) {


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
}

int main() {

}
