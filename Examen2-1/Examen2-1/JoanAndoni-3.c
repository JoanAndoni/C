#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void arreglo()
{
	int x, y;
	int i = 1;
	int numeros[10];

	for (x = 0; x < 10; x++)
	{
		for (x = 0; x < 10; x++)
		{
			i = 5 + rand() % 10;
		}
		numeros[i];
	}

	for (x = 0; x < 10; x++)
	{
		printf("%d\t", i, numeros[i]);
	}
}

int main()
{
	srand(time(NULL));
	arreglo();
	return 0;
}