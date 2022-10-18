#include "stack.h"
#include <iostream>
using namespace std;

Stack::Stack()
{
	this->data = 0;
	this->size = 0;
	this->top = 0;
}

Stack::~Stack()
{
	free(this->data);
}

bool Stack::isEmpty()
{
	return this->top == 0;
}

void Stack::push(int element)
{
	printf("Before: current size: %ld, current top: %d\n", this->size,
		   this->top);
	if ((size_t)this->top >= this->size) {
		this->increaseStackSize();
	}
	this->data[this->top++] = element;
	printf("After: current size: %ld, current top: %d\n\n", this->size,
		   this->top);
}

int Stack::pop()
{
	if (this->isEmpty()) {
		printf("Tried to pop from empty stack, aborting.\n");
		abort();
	}
	return this->data[--this->top];
}

void Stack::increaseStackSize()
{
	size_t newSize = (this->size + 1) * 2;
	int* tmpData = (int*)realloc(this->data, newSize * sizeof(int));
	if (tmpData) {
		this->data = tmpData;
	}
	else {
		printf("Failed to reallocate memory, aborting.\n");
		abort();
	}
	this->size = newSize;
}
