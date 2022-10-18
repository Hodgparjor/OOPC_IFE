#include "extendedStack.h"
#include <iostream>
using namespace std;

int main()
{
	Stack s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	for (int counter = 0; counter < 17; counter++)
		s1.push(counter);
	Stack s2 = s1;
	while (!s2.isEmpty())
		printf("%d\n", s2.pop());
	// s1.pop();
	return 0;
}
