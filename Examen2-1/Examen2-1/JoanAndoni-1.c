#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

void numeros()
{
	float x = 0, y = 0, z = 0;
	printf("Dame tres numeros\n\n");
	scanf("%f\n", &x);
	scanf("%f\n", &y);
	scanf("%f", &z);
	printf("\nValor de x = %.01f, y = %.01f, z = %.01f\n", x, y, z);

	if (x, z < y)
	{
		printf("Y: %f es el numero mas grande\n", y);
	}
	if (y, z < x)
	{
		printf("X: %f es el numero mas grande\n", x);
	}
	if (x, y < z)
	{
		printf("Z: %f es el numero mas grande\n", z);
	}
}


int main()
{
	numeros();
	return 0;
}