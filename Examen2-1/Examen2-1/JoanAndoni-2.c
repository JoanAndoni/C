#include <stdio.h>
#include <stdlib.h>

void arreglos()
{
	int x = 0, i = 1, z = 1, y;
	int numeros[1000];

	for (x = 0; x < 1000;x++)
	{
		numeros[z] = i++;
	}

	for (y = numeros[z]; y >= 1; y--)
	{
		printf("%d\n", numeros[z]);
	}
}

int main()
{
	arreglos();
	return 0;
}