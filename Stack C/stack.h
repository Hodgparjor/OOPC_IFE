#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
	int top;
	int* data;
	size_t size;
} Stack;

void init(struct Stack* s);
void destroy(struct Stack* s);
void push(struct Stack* s, int element);
void increaseStackSize(Stack* s);
int pop(struct Stack* s);
bool isEmpty(struct Stack* s);
