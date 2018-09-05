/* Lee un tga de 24 bits, hace un proceso básico y escribe un tga out.tga      */
/* out.tga se puede visualizar con photoshop                                   */
/* Para generar un tga, con photoshop coger cualquier imagen, y guardarla como */
/* tga a 24 bits sin compresion, a menor resolucion de 1200x1200               */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SALIDA "out.tga"            // el archivo de salida
#define MAXRX 1200                  // el tamaño máximo del array en x
#define MAXRY 1200                  // y en y

unsigned char Img[MAXRX][MAXRY][3];
unsigned char Img2[MAXRX][MAXRY][3];
int Rx, Ry, Rx2, Ry2;

void LeeTga()               // Lee un tga 24 de bits.
{
	FILE *fe;
	int x, y, i;
	unsigned char c, resto, cociente;
	fe = fopen("a.tga", "r");
	if (fe == NULL) {
		printf("Error al abrir archivo\n Pulsa..."); exit(1);
	}

	for (i = 0; i < 12; i++) {                              //leo 12 bytes de la cabecera que no se usan para nada
		c = fgetc(fe);
	}

	resto = fgetc(fe);                               //La resolucion se codifica en dos bytes
	cociente = fgetc(fe);                            //el primero es el resto de dividir por 256
	Rx = cociente * 256 + resto;                         //y el segundo el cociente. Y lo recompongo

	resto = fgetc(fe);                               // igual para la Ry
	cociente = fgetc(fe);
	Ry = cociente * 256 + resto;

	c = fgetc(fe);
	c = fgetc(fe);                                   //los ultimos 2 bytes de la cabecera

	for (y = 0; y < Ry; y++)                            //aqui leo la imagen
	{
		for (x = 0; x < Rx; x++)
		{
			Img[x][y][2] = fgetc(fe);                     //lee en orden B, G, R
			Img[x][y][1] = fgetc(fe);
			Img[x][y][0] = fgetc(fe);
		}
	}
	fclose(fe);
}

void LeeTga2(char na[])               // Lee un tga 24 de bits.
{
	FILE *fe;
	int x, y, i;
	unsigned char c, resto, cociente;

	fe = fopen(na, "r");
	if (fe == NULL)
	{
		printf("Error al abrir archivo %s\nPulsa...", na); exit(1);
	}

	for (i = 0; i<12; i++)                              //leo 12 bytes de la cabecera que no se usan para nada
		c = fgetc(fe);

	resto = fgetc(fe);                               //La resolucion se codifica en dos bytes
	cociente = fgetc(fe);                            //el primero es el resto de dividir por 256
	Rx2 = cociente * 256 + resto;                    //y el segundo el cociente. Y lo recompongo

	resto = fgetc(fe);                               // igual para la Ry
	cociente = fgetc(fe);
	Ry2 = cociente * 256 + resto;

	c = fgetc(fe);
	c = fgetc(fe);                                   //los ultimos 2 bytes de la cabecera

	for (y = 0; y<Ry2; y++)                          //Aqui leo la imagen
	for (x = 0; x<Rx2; x++)
	{
		Img2[x][y][2] = fgetc(fe);                     //lee en orden B, G, R
		Img2[x][y][1] = fgetc(fe);
		Img2[x][y][0] = fgetc(fe);
	}

	fclose(fe);
}


void GuardaTga(char ng[100])                                // Escribe un TGA guardado en memoria, a 24 bits
{
	FILE *fs;
	int x, y;

	fs = fopen(ng, "wb");                        //abro para escritura binaria
	if (fs == NULL)
	{
		printf("Error al crear archivo %s\nPulsa...", SALIDA); exit(1);
	}

	fputc(0, fs); /* 0 */                          // guardo valores de cebecera: la mayoria son ceros
	fputc(0, fs); /* 1 */
	fputc(2, fs); /* 2 */
	fputc(0, fs); /* 3 */
	fputc(0, fs); /* 4 */
	fputc(0, fs); /* 5 */
	fputc(0, fs); /* 6 */
	fputc(0, fs); /* 7 */
	fputc(0, fs); /* 8 */
	fputc(0, fs); /* 9 */
	fputc(0, fs); /* 10 */
	fputc(0, fs); /* 11 */
	fputc(Rx % 256, fs); /* 12 */                   //La resolucion x en dos bytes
	fputc(Rx / 256, fs); /* 13 */
	fputc(Ry % 256, fs); /* 14 */                   //la resolucion y en dos bytes
	fputc(Ry / 256, fs); /* 15 */
	fputc(24, fs); /* 16 */                       //indica 24 bits por pixel
	fputc(0, fs); /* 17 */                        // acabo la cabecera

	for (y = 0; y<Ry; y++)                        // y aqui guardo la imagen por filas horizontales
	{
		for (x = 0; x<Rx; x++)
		{
			fputc((char)Img[x][y][2], fs);             //tres bytes por pixel, R, G, B
			fputc((char)Img[x][y][1], fs);
			fputc((char)Img[x][y][0], fs);
		}
	}

	fclose(fs);
}

void histograma()
{
	int x, y, r, g, b, med, i, i2;
	int hist[256];

	for (int i3 = 0; i3 < 256; i3++)
		hist[i3] = 0;

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			r = Img[x][y][0]; g = Img[x][y][1]; b = Img[x][y][2];
			med=((r + g + b) / 3);
			hist[med]++;
		}
	}

	for (int i3 = 0; i3 < 256; i3++)
		hist[i3] = (hist[i3] * 0.01);

	for (i = 0; i < 256; i++)
	{
		if (i < 10)
			printf("%d   | ", i);
		else if (i < 100 && i > 9)
			printf("%d  | ", i);
		else
			printf("%d | ", i);
		for (i2 = 0; i2 < hist[i]; i2++)
		{
			printf("*");
		}
		printf("\n");
	}

}


void bn()
{
	char ng[100] = "out_bn.tga";
	int x, y;
	int r, g, b, med;

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			r = Img[x][y][0]; g = Img[x][y][1]; b = Img[x][y][2];
			med = (r + g + b) / 3;
			Img[x][y][0] = Img[x][y][1] = Img[x][y][2] = med;
		}
	}
	GuardaTga(ng);
}

void suma()
{
	char ng[100] = "out_suma.tga";
	int x, y, var = 0, newP;

	printf(" ¿Que valor deseas sumarle a tu imagen? ");
	scanf("%d", &var);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = Img[x][y][i] + var;
				if (newP > 255) newP = 255;
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void resta()
{
	char ng[100] = "out_resta.tga";
	int x, y, var = 0, newP;

	printf(" ¿Que valor deseas restarle a tu imagen? ");
	scanf("%d", &var);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = Img[x][y][i] - var;
				if (newP < 0) newP = 0;
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void multiplicacion()
{
	char ng[100] = "out_multiplicacion.tga";
	int x, y, newP;
	float var = 0;
	printf(" ¿Por que valor deseas multiplicar tu imagen? ");
	scanf("%f", &var);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = Img[x][y][i] * var;
				if (newP > 255) newP = 255;
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void division()
{
	char ng[100] = "out_division.tga";
	int x, y, newP;
	float var = 0;

	printf(" ¿Por que valor deseas dividir tu imagen? ");
	scanf("%f", &var);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = Img[x][y][i] / var;
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void invert()
{
	char ng[100] = "out_invert.tga";
	int x, y, newP;

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = 255 - Img[x][y][i];
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void ajusteLineal()
{

	char ng[100] = "out_ajusteLineal.tga";
	int x, y, m[3] = {125,125,125}, M[3] = {125,125,125}, newP;

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				if(Img[x][y][i] < m[i])
					m[i] = Img[x][y][i];
				if(Img[x][y][i] > M[i])
					M[i] = Img[x][y][i];
			}
		}
	}

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = ((Img[x][y][i]-m[i])*255)/(M[i]-m[i]);
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void ajusteNolineal()
{
	char ng[100] = "out_ajustenoLineal.tga";
	int x, y, opcion = 0;
	float newP, high = 255, middle = 128;

	printf("Que ajuste lineal deseas hacer?\n\n\t1. Oscurecer medios tonos\n\t2. Aclarar medios tonos\n\t3. Aclarar tonos oscuros y oscurecer los claros\n\nOpcion: ");
	scanf("%d", &opcion);

	switch (opcion)
	{
	case 1:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					newP = (pow(Img[x][y][i], 2) / 255);
					Img[x][y][i] = newP;
				}
			}
		}

		GuardaTga(ng);
		break;

	case 2:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					newP = (sqrt(Img[x][y][i] / high) * high);
					Img[x][y][i] = newP;
				}
			}
		}
		GuardaTga(ng);
		break;

	case 3:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					if (Img[x][y][i] < 128)
						newP = (sqrt(Img[x][y][i] / middle) * middle);
					else if (Img[x][y][i] > 128)
						newP = middle + (pow((Img[x][y][i]/high), 2) * middle);
					else
						newP = Img[x][y][i];
					Img[x][y][i] = newP;
				}
			}
		}

		GuardaTga(ng);
		break;

	default:
		printf("\nValor invalido intentalo denuevo\n");
		break;
	}
}

void gama()
{
	float gama;
	int x, y, newP;

	printf(" ¿Por que valor de gama deseas convertir tu imagen? ");
	scanf("%f", &gama);

	char ng[100] = "out_gama.tga";

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = (255 * pow((Img[x][y][i]/255), (1/gama)));
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void umbralLineal()
{
	char ng[100] = "out_umbralLineal.tga";
	int x, y, var = 0;
	int r, g, b, med;

	printf(" ¿En que valor deseas hacer el umbral? ");
	scanf("%d", &var);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			r = Img[x][y][0]; g = Img[x][y][1]; b = Img[x][y][2];
			med = (r + g + b) / 3;
			if (med <= var)
				Img[x][y][0] = Img[x][y][1] = Img[x][y][2] = 0;
			else if (med > var)
				Img[x][y][0] = Img[x][y][1] = Img[x][y][2] = 255;
		}
	}
	GuardaTga(ng);
}

void umbralRango()
{
	char ng[100] = "out_umbralRango.tga";
	int x, y, var = 0;
	int r, g, b, med;

	printf(" ¿En que valor deseas hacer el umbral de rango? ");
	scanf("%d", &var);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			r = Img[x][y][0]; g = Img[x][y][1]; b = Img[x][y][2];
			med = (r + g + b) / 3;
			if (med > var)
				Img[x][y][0] = Img[x][y][1] = Img[x][y][2] = 255;
		}
	}
	GuardaTga(ng);
}

void umbralTramo()
{
	char ng[100] = "out_umbralTramo.tga";
	int x, y, var = 0, var2 = 0;
	int r, g, b, med;

	printf(" ¿En que valor deseas comenza el umbral?");
	scanf("%d", &var);

	printf(" ¿En que valor deseas terminar el umbral?");
	scanf("%d", &var2);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			r = Img[x][y][0]; g = Img[x][y][1]; b = Img[x][y][2];
			med = (r + g + b) / 3;
			if (med < var)
				Img[x][y][0] = Img[x][y][1] = Img[x][y][2] = 255;
			else if (var2 > med && med > var)
				Img[x][y][0] = Img[x][y][1] = Img[x][y][2] = 0;
			else if (med > var2)
				Img[x][y][0] = Img[x][y][1] = Img[x][y][2] = 255;
		}
	}
	GuardaTga(ng);
}

void booleanas()
{
	char n2[100];
	printf("Nombre del archivo nuevo que desees utilizar: ");
	scanf("%s", n2);
	LeeTga2(n2);

	char ng[100] = "out_booleana1.tga";
	int x, y, opcion = 0, newP;

	printf("Que operacion booleana deseas hacer?\n\n\t1. AND\n\t2. OR\n\nOpcion: ");
	scanf("%d", &opcion);

	printf("Como deseas que se llame el archivo?");
	scanf("%s", ng);

	switch (opcion)
	{
		case 1:
			for (y = 0; y < Ry; y++)
			{
				for (x = 0; x < Rx; x++)
				{
					for (int i = 0; i <= 2; i++)
					{
						newP = (Img[x][y][i] & Img2[x][y][i]);
						Img[x][y][i] = newP;
					}
				}
			}
			GuardaTga(ng);
			break;

		case 2:
			for (y = 0; y < Ry; y++)
			{
				for (x = 0; x < Rx; x++)
				{
					for (int i = 0; i <= 2; i++)
					{
						newP = (Img[x][y][i] | Img2[x][y][i]);
						Img[x][y][i] = newP;
					}
				}
			}
			GuardaTga(ng);
			break;

	default:
		printf("\nValor invalido intentalo denuevo\n");
		break;
	}
}

void aritmeticas()
{
	char n2[100];
	printf("Nombre del archivo nuevo que desees utilizar: ");
	scanf("%s", n2);
	LeeTga2(n2);

	char ng[100] = "out_aritmeticas.tga";
	int x, y, opcion = 0, newP;
	float pond = 0;

	printf("Que operacion booleana deseas hacer?\n\n\t1. Suma\n\t2. Suma ponderada\n\t3. Resta\n\t4. Multiplicacion\n\t5. Division\n\nOpcion: ");
	scanf("%d", &opcion);
	printf("Como deseas que se llame el archivo? (Al final pon .tga)\n Nombre: ");
	scanf("%s", ng);

	switch (opcion)
	{
	case 1:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					newP = (Img[x][y][i] + Img2[x][y][i])/2;
					Img[x][y][i] = newP;
				}
			}
		}
		GuardaTga(ng);
		break;

	case 2:
		printf("Que valor de ponderacion deseas? : ");
		scanf("%f", &pond);
		if (pond > 1)
			pond = pond / 100;

		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					newP = ((pond * Img[x][y][i]) + ((1-pond)*Img2[x][y][i]));
					Img[x][y][i] = newP;
				}
			}
		}
		GuardaTga(ng);
		break;

	case 3:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					newP = (Img[x][y][i] - Img2[x][y][i]);
					if (newP < 0)
						newP = 0;
					Img[x][y][i] = newP;
				}
			}
		}
		GuardaTga(ng);
		break;

	case 4:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					newP = ((Img[x][y][i] * Img2[x][y][i])/255);
					Img[x][y][i] = newP;
				}
			}
		}
		GuardaTga(ng);
		break;

	case 5:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					if (Img[x][y][i] == 0 || Img2[x][y][i] == 0)
						newP = 0;
					else
						newP = (Img[x][y][i] / Img2[x][y][i]);
					Img[x][y][i] = newP;
				}
			}
		}
		GuardaTga(ng);
		break;

	default:
		printf("\nValor invalido intentalo denuevo\n");
		break;
	}
}


void viraje()
{
	char ng[100] = "out_viraje.tga";
	int x, y, newP, RGB[3] = {0,0,0};
	printf("Que color deseas utilizae para hacer el viraje?\n\n");
	printf("R = ");
	scanf("%d", &RGB[0]);
	printf("G = ");
	scanf("%d", &RGB[1]);
	printf("B = ");
	scanf("%d", &RGB[2]);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				if (Img[x][y][i] < 128)
					newP = RGB[i] * (Img[x][y][i] / 128);
				else
					newP = RGB[i] + ((255 - RGB[i])*(Img[x][y][i]-128)) / 128;
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void balanceblancos()
{
	char ng[100] = "out_balanceblancos.tga";
	int x, y, newP;
	float RGB[3] = { 0, 0, 0 };
	printf("Que porcentajes deseas utilizar para hacer el balance de blancos? \n\n");
	printf("R = ");
	scanf("%f", &RGB[0]);
	printf("G = ");
	scanf("%f", &RGB[1]);
	printf("B = ");
	scanf("%f", &RGB[2]);

	for (y = 0; y < Ry; y++)
	{
		for (x = 0; x < Rx; x++)
		{
			for (int i = 0; i <= 2; i++)
			{
				newP = RGB[i] * Img[x][y][i];
				if (newP < 0)
					newP = 0;
				else if (newP > 255)
					newP = 255;
				Img[x][y][i] = newP;
			}
		}
	}
	GuardaTga(ng);
}

void suavizado()
{
	char ng[100] = "out_suavizado.tga";
	int x, y, opcion = 0, pixel1, pixel2, pixel3, pixel4, pixel5, pixel6, pixel7, pixel8, pixel9;
	float newP;

	printf("Que tipo de suavizado deseas hacer?\n\n\t1. 1/4\n\t2. 1/9\n\t3. Lateral\n\t4. Vertical\n\t5. Gaussiano\n\nOpcion: ");
	scanf("%d", &opcion);
	printf("Como deseas que se llame el archivo? (Al final pon .tga)\n Nombre: ");
	scanf("%s", ng);

	switch (opcion)
	{
	case 1:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					if (x == 0 && y == 0)
						Img[x][y][i] = Img[x][y][i];
					else
					{
						if (x == 0)
						{
							pixel1 = Img[x][y][i];
							pixel2 = Img[x][y][i];
							pixel3 = Img[x][y - 1][i];
							pixel4 = Img[x][y][i];
						}

						else if (y == 0)
						{
							pixel1 = Img[x][y][i];
							pixel2 = Img[x - 1][y][i];
							pixel3 = Img[x][y][i];
							pixel4 = Img[x][y][i];
						}

						else
							newP = (Img[x - 1][y - 1][i]/4) + (Img[x - 1][y][i]/4) + (Img[x][y - 1][i]/4) + (Img[x][y][i] / 4);
						Img[x][y][i] = newP;
					}
				}
			}
		}
		GuardaTga(ng);
		break;

	case 2:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					if (x == 0 && y == 0)
						Img2[x][y][i] = Img[x][y][i];
					else
						newP = (Img[x - 1][y + 1][i] / 9) + (Img[x][y + 1][i] / 9) + (Img[x + 1][y + 1][i] / 9) + (Img[x - 1][y][i] / 9) + (Img[x][y][i] / 9) + (Img[x + 1][y][i] / 9) + (Img[x - 1][y - 1][i] / 9) + (Img[x][y - 1][i] / 9) + (Img[x + 1][y - 1][i] / 9);
					Img2[x][y][i] = newP;
				}
			}
		}

		for (y = 0; y < Ry; y++){
			for (x = 0; x < Rx; x++){
				for (int i = 0; i <= 2; i++){
					Img[x][y][i] = Img2[x][y][i];
				}
			}
		}
		GuardaTga(ng);
		break;

	case 3:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					if (x == 0)
						newP = (Img[x][y][i] / 3) + (Img[x][y][i] / 3) + (Img[x + 1][y][i] / 3);
					else
						newP = (Img[x-1][y][i] / 3) + (Img[x][y][i] / 3) + (Img[x+1][y][i] / 3);
					Img2[x][y][i] = newP;
				}
			}
		}
		for (y = 0; y < Ry; y++){
			for (x = 0; x < Rx; x++){
				for (int i = 0; i <= 2; i++){
					Img[x][y][i] = Img2[x][y][i];
				}
			}
		}
		GuardaTga(ng);
		break;

	case 4:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					if (y == 0)
						newP = (Img[x][y][i] / 3) + (Img[x][y][i] / 3) + (Img[x][y + 1][i] / 3);
					else
						newP = (Img[x][y - 1][i] / 3) + (Img[x][y][i] / 3) + (Img[x][y + 1][i] / 3);
					Img2[x][y][i] = newP;
				}
			}
		}

		for (y = 0; y < Ry; y++){
			for (x = 0; x < Rx; x++){
				for (int i = 0; i <= 2; i++){
					Img[x][y][i] = Img2[x][y][i];
				}
			}
		}
		GuardaTga(ng);
		break;

	case 5:
		for (y = 0; y < Ry; y++)
		{
			for (x = 0; x < Rx; x++)
			{
				for (int i = 0; i <= 2; i++)
				{
					if (x == 0 && y == 0)
						Img2[x][y][i] = Img[x][y][i];
					else
						newP = (Img[x - 1][y + 1][i] / 16) + (Img[x][y + 1][i] / 8) + (Img[x + 1][y + 1][i] / 16) + (Img[x - 1][y][i] / 8) + (Img[x][y][i] / 4) + (Img[x + 1][y][i] / 8) + (Img[x - 1][y - 1][i] / 16) + (Img[x][y - 1][i] / 8) + (Img[x + 1][y - 1][i] / 16);
					Img2[x][y][i] = newP;
				}
			}
		}

		for (y = 0; y < Ry; y++){
			for (x = 0; x < Rx; x++){
				for (int i = 0; i <= 2; i++){
					Img[x][y][i] = Img2[x][y][i];
				}
			}
		}
		GuardaTga(ng);
		break;

	default:
		printf("\nValor invalido intentalo denuevo\n");
		break;
	}
}


int main(int argC, char *argV[])
{
	int opcion = 1, chang = 0;

	while (opcion != 0)
	{
		printf("Im here\n" );
		LeeTga();
		printf("Resolucion de %d x %d\n", Rx, Ry);

		printf("Escoge una de las transfonmaciones que desees para la imagen\n\n");

		printf("\t1.  Ver histograma de luminosidad\n");
		printf("\t2.  Sumar una constante\n");
		printf("\t3.  Restar una constante\n");
		printf("\t4.  Multiplicar por una constante\n");
		printf("\t5.  Divir entre una constante\n");
		printf("\t6.  Transformacion lineal generica\n");
		printf("\t7.  Ajuste lineal\n");
		printf("\t8.  Ajuste no lineal\n");
		printf("\t9.  Tranformacion de Gama\n");
		printf("\t10. Umbral lineal\n");
		printf("\t11. Umbral rango\n");
		printf("\t12. Umbral solo un tramo\n");
		printf("\t13. Operaciones booleanas dos imagenes\n");
		printf("\t14. Operaciones aritmeticas con dos imagenes\n");
		printf("\t15. Blanco y negro\n");
		printf("\t16. Viraje\n");
		printf("\t17. Balance de blancos\n");
		printf("\t18. Suavizado\n");
		printf("\t100. Cambiar imagen para trabajar\n");
		printf("\t0. Salir del programa\n\n");
		printf("Escoge una opcion: ");
		scanf("%d", &opcion);
		switch (opcion)
		{
		case 1:
			histograma();
			break;
		case 2:
			suma();
			break;
		case 3:
			resta();
			break;
		case 4:
			multiplicacion();
			break;
		case 5:
			division();
			break;
		case 6:
			invert();
			break;
		case 7:
			ajusteLineal();
			break;
		case 8:
			ajusteNolineal();
			break;
		case 9:
			gama();
			break;
		case 10:
			umbralLineal();
			break;
		case 11:
			umbralRango();
			break;
		case 12:
			umbralTramo();
			break;
		case 13:
			booleanas();
			break;
		case 14:
			aritmeticas();
			break;
		case 15:
			bn();
			break;
		case 16:
			viraje();
			break;
		case 17:
			balanceblancos();
			break;
		case 18:
			suavizado();
			break;

		case 100:
			printf("Deseas cambiar de imagen? (Si:1 | No:0) : ");
			scanf("%d", &chang);
			if (chang == 1)
			{
				printf("\nNombre del nuevo archivo con el que deseas trabajar : ");
				//scanf("%s", na);

			}
			break;

		case 0:
			printf("Gracias por usar el programa que tengas buen dia.\n\n");
			opcion = 0;
			break;

		default:
			printf("Error de tecla pulsa denuevo lo que desees hacer.\n\n");
			break;
		}
	}
	return 0;
}
