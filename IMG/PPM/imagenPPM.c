#include <stdio.h>
#include <stdlib.h>

#define MAX 300

struct imagePPM {
  char MagicNumber [3];
  int Rx;
  int Ry;
  int MaxValue;
  char rgbValues[MAX][MAX][3];
};

void readFile(struct imagePPM *readStructure)
{
	FILE *fe;
	fe = fopen("Bayo.ppm", "r");
	if (fe == NULL) {
		printf("Error al abrir archivo\n"); exit(1);
	}
  else {
    fscanf(fe, "%s", readStructure->MagicNumber);
    readStructure->Rx =  fgetc(fe);
    readStructure->Ry =  fgetc(fe);
    readStructure->MaxValue =  fgetc(fe);

  	for (int y = 0; y < readStructure->Rx; y++) {
  		for (int x = 0; x < readStructure->Ry; x++) {
  			readStructure->rgbValues[x][y][0] = fgetc(fe);
  			readStructure->rgbValues[x][y][1] = fgetc(fe);
  			readStructure->rgbValues[x][y][2] = fgetc(fe);
  		}
  	}
  }
	fclose(fe);
}

void printIMG(struct imagePPM img2print)
{
  printf("Magic Number   : %s\n", img2print.MagicNumber);
  printf("Dimension in X : %d\n", img2print.Rx);
  printf("Dimension in Y : %d\n", img2print.Ry);
  printf("Maximum value  : %d\n", img2print.MaxValue);
  for (int y = 0; y < img2print.Rx; y++) {
    for (int x = 0; x < img2print.Ry; x++) {
      printf("%d ", img2print.rgbValues[x][y][0]);
      printf("%d ", img2print.rgbValues[x][y][1]);
      printf("%d - ", img2print.rgbValues[x][y][2]);
    }
    printf("\n");
  }
}


int main(int argc, char const *argv[]) {
  struct imagePPM img1;
  readFile(&img1);
  printIMG(img1);

  return 0;
}
