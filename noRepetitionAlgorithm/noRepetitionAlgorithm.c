#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(0));
  int myArray[12],i,j,uniqueflag,random;

  for(i = 0; i < 13; i++)
  {
      do
      {
          uniqueflag = 1;
          random = rand() % 13+1;

          for (j = 0; j < i && uniqueflag == 1; j++)
          {
              if (myArray[j] == random)
              {
                  uniqueflag = 0;
              }
          }
      } while (uniqueflag != 1);
			myArray[i] = random;
      printf("The number %d is now assigned to the index %d\n", random, myArray[i]);
    }

	return 0;
}
