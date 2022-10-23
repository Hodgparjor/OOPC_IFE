#include "extendedStack.h"
#include <iostream>
using namespace std;

int main()
{
	Stack s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);

	Stack s2(s1);

	Stack s3 = s1;

	Stack s4;
	s4.push(10);
	s4 = s1;
}
