#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
        int* address;
        int length;
} tuple;

void malloc537(size_t size) {
        tuple* memInfo = malloc(sizeof(tuple));

        memInfo->address = malloc(size);
        memInfo->length = size;
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
	}else if(){
		realloc(ptr, size);
	}
}

int main() {

}
