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

}

void memcheck537(void *ptr, size_t size) {

}

void realloc537(void *ptr, size_t size) {

}

int main() {

}
