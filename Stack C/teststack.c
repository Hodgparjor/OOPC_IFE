#include "stack.h"

int main()
{
	Stack s1;
	Stack s2;
	init(&s1);
	init(&s2);
	push(&s1, 1);
	push(&s1, 2);
	pop(&s1);
	push(&s1, 3);
	push(&s1, 5);
	push(&s1, 6);
	for (int counter = 0; counter < 17; counter++)
		push(&s2, counter);
	while (!isEmpty(&s1))
		printf("%d\n", pop(&s1));
	//pop(&s1);
	destroy(&s1);
	destroy(&s2);
	return 0;
}
