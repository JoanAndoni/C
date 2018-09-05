#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)

int baraja[52] /*= { 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14 }*/;
int revol[52], array[20], j1[5], j2[5], j3[5], j4[5],i;

int barajeo () // Funcion que hace que se revuelvan las cartas dandoles el valor de 1, 2,3,4,5,6,7,8,9,10,11,12,13 
{
	srand(time(0)); // Funcion que iniciliza la funcion que sirve para inicializar la funcion de random
	int i2, i3, i4=0, carta, unica = 1, s = 1; // Definicion de las variables de la funcion
	i = 0; 

	for (i = 0; i < 4; i++) // Ciclo que hara que se repitan 4 veces las trece cartas
	{
		for (i2 = 0; i2 < 13; i2++)
		{
			do
			{
				unica = 1;
				carta = rand() % 13 + 1;

				for (i3 = i*13; i3 < (i2 + i*13) && unica == 1; i3++)
				{
					if (baraja[i3] == carta)
					{
						unica = 0;
					}
				}
			}while (unica != 1);
			baraja[i4] = carta;
			i4++;
		}
	}

	for (i = 0; i < 52; i++)
	{
		printf("Index %d : %d\n",s, baraja[i]);
		s++;
	}
	printf("\n");
	return 0;
}

int cartas()
{
	for(i=0;i<20;i++)
	{
		array[i]=baraja[i];	
	}
	return 0;
}

int jugador1()
{
	for(i=0;i<5;i++)
	{
		j1[i]=array[i];
	}
	/*for (int gx = 0; gx <= 4; gx++)
	{
		if (gx == 0){
			j1[gx] = _a;
		}
		else if (gx == 1){
			j1[gx] = _e;
		}
		else if (gx == 2){
			j1[gx] = _i;
		}
		else if (gx == 3){
			j1[gx] = _m;
		}
		else
		{
			j1[gx] = _q;
		}
	}
	return 0;*/
	return 0;
}

int jugador2()
{
	for(i=0;i<5;i++)
	{
		j2[i]=array[i+5];
	}
	/*for (int gx = 0; gx <= 4; gx++)
	{
		if (gx == 0){
			j2[gx] = _b;
		}
		else if (gx == 1){
			j2[gx] = _f;
		}
		else if (gx == 2){
			j2[gx] = _j;
		}
		else if (gx == 3){
			j2[gx] = _n;
		}
		else
		{
			j2[gx] = _r;
		}
	}*/
	return 0;
}

int jugador3()
{
	for(i=0; i<5; i++)
	{
		j3[i] = array[i+10];
	}

	/*for (int gx = 0; gx <= 4; gx++)
	{
		if (gx == 0){
			j3[gx] = _c;
		}
		else if (gx == 1){
			j3[gx] = _g;
		}
		else if (gx == 2){
			j3[gx] = _k;
		}
		else if (gx == 3){
			j3[gx] = _o;
		}
		else
		{
			j3[gx] = _s;
		}
	}*/
	return 0;
}

int jugador4()
{
	for(i=0; i<5; i++)
	{
		j4[i]=array[i+15];
	}

	/*for (int gx = 0; gx <= 4; gx++)
	{
		if (gx == 0){
			j4[gx] = _d;
		}
		else if (gx == 1){
			j4[gx] = _h;
		}
		else if (gx == 2){
			j4[gx] = _l;
		}
		else if (gx == 3){
			j4[gx] = _p;
		}
		else
		{
			j4[gx] = _t;
		}
	}*/
	return 0;
}

int printcartas()
{
	printf("Jugador 1\n");
	for (i = 0; i < 5; i++) printf("%d\n", j1[i]);
	
	printf("\n Jugador 2\n");
	for (i = 0; i < 5; i++) printf("%d\n", j2[i]);
	
	printf("\n Jugador 3\n");
	for (i = 0; i < 5; i++) printf("%d\n", j3[i]);

	printf("\n Jugador 4\n");
	for (i = 0; i < 5; i++)	printf("%d\n", j4[i]);
	printf("****************************");
	
	return 0;
}


int main()
{
	char respuesta = 'no'; 
	do 
	{
		barajeo();
		cartas();
		jugador1();
		jugador2();
		jugador3();
		jugador4();
		printcartas();
		scanf("\nQuieres jugar denuevo? \n \t si | no %c\n", respuesta);
	} while (respuesta != 'no');
		
	return 0;
}