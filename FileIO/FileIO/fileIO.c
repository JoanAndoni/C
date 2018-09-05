/*
file imput and output

Flie open mode	


*/
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996) //4996

#include <stdio.h>

int main()
{
	FILE* filePtr;

	filePtr = fopen("test.txt", "w");
	if(filePtr == NULL)
	{
		printf("Could not open file. Quit!\n");
		return 1;
	}
	fprintf(filePtr, "Hola mundo\n Atte. %s\n ", "Gil");

	fclose(filePtr);

	return 0;
}
