#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	int mazo_ordenado[44];
	int mazo_barajado[44];
	int usado[44];

	for (int i = 0; i < 44; i++)
	{
		usado[i] = false;
	}

	int index = 0;
	for (int i = 0; i < 44; i++)
	{
		do
		{
			index = (rand() % 44);
		} while
			(usado[index]);
		mazo[i] = mazo_ordenado[index];
		usado[index] = true;
	}

	for (i = 0; i<52; i++)
	{
		print("Index %d asignacion %d", usado[i], usado[index])
	}
}
