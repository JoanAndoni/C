#include <stdio.h>

int main()
{
	float ma[3][3] = {{4.6,7.3,1.2},{4.8,8.5,9.7},{1.3,6.8,0.4}}, mb[3][3] = {{2.4,3.8,6.1},{6.7,4.2,5.6},{3.5,4.9,7.3}}, mc [3][3] = {0}, assigment = 0;
	int i1,i2,i3;

	for( i1 = 0 ; i1 < 3; i1++)
	{
		for( i2 = 0 ; i2 < 3; i2++)
		{
			for( i3 = 0 ; i3 < 3; i3++)
			{
				assigment += ma[i1][i3] * mb[i3][i2];
			}
		mc[i1][i2] = assigment;
		assigment = 0;
		}
	assigment = 0;
	}

	for (i1 = 0; i1 < 3; i1++)
	{
		printf("(");
		for (i2 = 0; i2 < 3; i2++)
		{
			printf(" %0.2f ", mc[i1][i2]);
		}
		printf(")\n");
	}

	return 0;
}