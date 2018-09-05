#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// 2 personas, lanzan 3 dados, gana el que tenga mas puntos sumados
// Dado1: 6 Caras, 1 -> 6 
// Dado2: 12 Caras, 0 -> 11
// Dado3: 20 Caras, -1 -> 18
// Acumulador de puntos que comience en 0

// Desplegar los puntos de cada dado con la suma total de cada jugador
// Menos de 30 lineas de codigo
// Opcion de volver a lanzar los dados: "s"
// Utilizar valores aleatorios para el valor de los dados


//Funcion que despliega los valores obtenidos en los tres dados del jugador 1
int jugador1()
{
	int score = 0;// Variable que almacena los puntos del jugador 1.
	int puntos = 0;
	int x = 0, y = 0, z = 0; // Variables que almacenan los dados; x = dado1,  y = dado 2, z = dado 3.  

		x = 1 + rand() % 5;// Funcion que hace el valor random de un numero asigando a el dado 1. (1, 6)
		y = 0 + rand() % 12;// Funcion que hace el valor random de un numero asigando a el dado 2. (0, 11)
		z = -1 + rand() % 19;// Funcion que hace el valor random de un numero asigando a el dado 3. (-1,18)
		puntos = x + y + z;// Hace la operacion de la suma de los valores obtenidos en los dados.
		printf("Dado 1: %d\nDado 2: %d\nDado 3: %d\n", x, y, z);// Hace la impresion de los valores de los dados del jugador 1.
		printf("Score del jugador 1 = %d\n", puntos); //Hace la impresion de la suma de los dados.
 
	return puntos;
}

// Funcion que despliega los valores obtenidos en los tres dados del jugador 2
int jugador2()
{
	int score = 0;// Variable que almacena los puntos del jugador 2.
	int puntos = 0;
	int x = 0, y = 0, z = 0; // x = dado1,  y = dado 2, z = dado 3.  

		x = 1 + rand() % 5;// Funcion que hace el valor random de un numero asigando a el dado 1. (1, 6)
		y = 0 + rand() % 12;// Funcion que hace el valor random de un numero asigando a el dado 2. (0, 11)
		z = -1 + rand() % 19;// Funcion que hace el valor random de un numero asigando a el dado 3. (-1, 18)
		puntos = x + y + z;// Hace la operacion de la suma de los valores obtenidos en los dados.
		printf("\n\nDado 1: %d\nDado 2: %d\nDado 3: %d\n", x, y, z);// Hace la impresion de los valores de los dados del jugador 2.
		printf("Score del jugador 2 = %d\n", puntos);//Hace la impresion de la suma de los dados.

	return puntos;
}


//Funcion que inicializa las funciones 
int main()
{
	srand (time(NULL)); // Funcion que genera valores aleatorios que toma de la hora del sistema
	char respuesta = 's'; // Definicion e inicializacion de la variable "respuesta" dandole el valor de s

	while (respuesta != 'n') //Condicion de cuando se ejecutara el programa que se define asi (cuando respuesta sea diferente de n hcaer lo siguente)
	{
		int j1 = jugador1(); // Inicializacion de la funcion jugador 1 y asigancion de una variable para crear las condiciones en la parte de abajo
		int j2 = jugador2(); // Inicializacion de la funcion jugador 2 y asigancion de una variable para crear las condiciones en la parte de abajo
		printf("jugador1, jugador2 %d %d\n", j1, j2);
		if (j1 > j2) // Condicion de cuando el score del jugador 1 sea mas grande que el del jugador 2 hacer lo siguiente 
		{
			printf("\nEl jugador 1 ha ganado!!!\n\n");// Imprime que el jugador 1 ha ganado
		}
		else if (j1 < j2) // Condicion de cuando el score del jugador 1 sea mas grande que el del jugador 2 hacer lo siguiente
		{
			printf("\nEl jugador 2 ha ganado!!!\n\n");// Imprime que el jugador 2 ha ganado
		}
		else // Condicion de cuando el score del jugador 1 es cualquier cosa diferente de <, >, se hara lo siguiente
		{
			printf("\nHay un empate.\nY alguien tene que ganar\n\n");// Imprime que hubo un empate
		}

		printf("A todos les gusta ganar\nTe gustaria lanzar los dados denuevo\n\n");// Funcion que te dice que si quieres lanzar los dados denuevo
		printf("%s", "Escoge (Si=s \t No=n)\n");//Funcion que te da las opciones para escoger alguna respuesta
		scanf("%s", &respuesta);// Funcion que te deja escribir la respuesta y seguir haciendolo
	}
	return 0;
}