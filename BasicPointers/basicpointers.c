#include <stdio.h>

int main()
{
	int a = 5;
	int* ptr = NULL;

	ptr = &a;

	printf("&A = %p, PTR = %p\n", &a, ptr);
	printf("A = %d, *PTR = %p\n", a, *ptr);

	*ptr = 10;

	printf("&A = %p, PTR = %p\n", &a, ptr);

	a = 20;
	printf("A = %d, *PTR = %d\n", a, *ptr);


	return 0;
}
