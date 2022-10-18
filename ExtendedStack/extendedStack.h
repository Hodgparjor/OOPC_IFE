#pragma once
#include <stdlib.h>

class Stack {
  public:
	Stack();
	~Stack();
	Stack(const Stack& s1);
	Stack& operator=(const Stack& s1);
	int pop();
	void push(int element);
	bool isEmpty();

  private:
	size_t size;
	int* data;
	int top;
	void increaseStackSize();
};
