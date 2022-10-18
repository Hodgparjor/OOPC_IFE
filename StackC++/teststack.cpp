#include "stack.h"
#include <iostream>
using namespace std;

int main()
{
	Stack s1;
	Stack s2;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s2.push(4);
	for (int counter = 0; counter < 17; counter++)
		s2.push(counter);
	while (!s1.isEmpty())
		printf("%d\n", s1.pop());
	// s1.pop();
	return 0;
}
