#pragma once

#include <stdlib.h>

class Stack {
  public:
	Stack();
	~Stack();
	int pop();
	void push(int element);
	bool isEmpty();

  private:
	size_t size;
	int* data;
	int top;
	void increaseStackSize();
};
