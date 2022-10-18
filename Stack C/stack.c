#include "stack.h"

void init(Stack* s)
{
	s->top = 0;
	s->data = 0;
	s->size = 0;
}

void destroy(Stack* s)
{
	free(s->data);
}

void push(Stack* s, int element)
{
	printf("Before: current size: %ld, current top: %d\n", s->size, s->top);
	if (s->top >= s->size) {
		increaseStackSize(s);
	}
	s->data[s->top++] = element;
	printf("After: current size: %ld, current top: %d\n\n", s->size, s->top);
}

void increaseStackSize(Stack* s)
{
	size_t newSize = (s->size + 1) * 2;
	int* tmpData = realloc(s->data, newSize * sizeof(int));
	if (tmpData)
		s->data = tmpData;		
	else {
		printf("Failed to reallocate memory, aborting.\n");
		abort();
	}
	s->size = newSize;
}

int pop(Stack* s)
{
	if (isEmpty(s)) {
		printf("Tried to pop from empty stack, aborting.\n");
		abort();
	}
	return s->data[--s->top];
}

bool isEmpty(Stack* s)
{
	if (s->top == 0)
		return true;
	else
		return false;
}
