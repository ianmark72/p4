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

int main() {

}
