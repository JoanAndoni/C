#include <stdio.h>

/*
 * Funcion que hace el trabajo del factorial que se llama dentro del ciclo interno para hacer la funcion
 */
long factorial(int m)
{
	int n = 1; // Defino e Inicializo la variable
	long fact = 1; // definición e inicialización del resultado

	while (n <= m) // Cálculo de la sumatoria con ciclo - Condición de cuando se haran las operaciones mandadas a llamar
	{
		fact *= n; // fact = fact * n;
		n++; //n = n + 1;
	}
	return fact;
}

/*
 * Ciclo Interno INCREMENTAL - Esta funcion se manda a llamar en las funciones para hacer el ciclo de incremento
 */
void ciclointincremental(int n, int i)
{
	short j = 0; // Definicion e inicializacion de la variable j que comienza en 0 para que secumplan las diez veces que se mandaron a llamar
	for (j = 0; j <= i; j++) // Son las operaciones que se haran en todo el ciclo (La inicializacion de j, la condicion de la veces que se repetira y el aumento de 1 en j)
	{
		long calculo = factorial(i) / (factorial(j) * factorial(i - j)); //n! / (k!* (n - k)!); Cuando (n = i) y (k = j) La operacion para calcular el triangulo de pascal
		printf ("%ld\t", calculo); // Funcion que manda a imprimir el resultado del calculo con un tabulador para separar los numeros con un ld por que es una funcion long
	}
	printf("\n"); // Hace un enter en cada linea 
}

/*
 * Ciclo Interno DECREMENTAL - Esta funcion se manda a llamar en las funciones para hacer el ciclo de decremento
 */
void ciclointdecremental(int n, int i)
{
	short j = 0; // Definicion e inicializacion de la variable j
	for (j = n - i; j >= 0; j--) // Son las operaciones que se haran en todo el ciclo (La inicializacion de j, la condicion de la veces que se repetira y el decremento de 1 en j)
	{
		long calculo = factorial(n - i) / (factorial(j) * factorial((n-i) - j)); // n! / (k!* (n - k)!); Cuando (n = i) y (k = j) La operacion para calcular el triangulo de pascal
		printf("%ld\t", calculo); // Funcion que manda a imprimir el resultado del calculo con un tabulador para separar los numeros con un ld por que es de una funcion long
	} 
	printf("\n"); // Hace un enter en cada linea
}

/*
 * Función que imprime el un triangulo Incremental For
 */
void trianguloInFor(short n)
{
	short i = 0; // Inicializacion de i en la funcion
	for (i = 0; i <= n; i++) // Operaciones que se cumpliran en todo el ciclo (Incicalizacion de i, la condicion de la veces de repeticion y el incremento en i)
	{
		ciclointincremental(n, i); // Funcion que llama al ciclo interno de la funcion que hace el factorial 
	}
	printf("*******************************************************************************\n\n\n\n"); // Linea de asteriscos que hace que se separe una funcion de otra
}

/*
 * Función que imprime el un triangulo Decremental For
 */
void trianguloDeFor(short n)
{
	short i = 0; // Definicion de la variable i en la funcion
	for (i = n; i >= 0; i--)  // Operaciones que se cumpliran en todo el ciclo (Incicalizacion de i que sera igual a n para que vaya de arriba a abajo, la condicion de la veces de repeticion y el decremento en i)
	{
		ciclointdecremental(n, i); // Funcion que llama al ciclo interno de la funcion que hace el factorial 
	}
	printf("*******************************************************************************\n\n\n\n"); // Linea de asteriscos que hace que se separe una funcion de otra
}

/*
 * Función que imprime el un triangulo Incremental While
 */
void trianguloInWhile(short n)
{
	short i = 0; // Definicion de la variable i en la funcion
	while (i <= n) // Condicion de cuantas veces o cada cuanto se haran las operaciones correspondientes
	{
		ciclointincremental(n, i); // Funcion que llama al ciclo interno de la funcion que hace el factorial 
		i++; // Incremento de uno en i ( i = i + 1 )
	}
	printf("*******************************************************************************\n\n\n\n"); // Linea de asteriscos que hace que se separe una funcion de otra
}

/*
 * Función que imprime el un triangulo Decremental While
 */
void trianguloDeWhile(short n)
{
	short i = n; // Definicion de la variable i en la funcionque sera n para que vayan en decremento y se hagan las 11 lineas
	while (i >= 0) // Condicion de cuantas veces o cada cuanto se haran las operaciones correspondientes
	{
		ciclointdecremental(n, i); // Funcion que llama al ciclo interno de la funcion que hace el factorial 
		i--; // Decremento de uno en i ( i = i - 1 )
	}
	printf("*******************************************************************************\n\n\n\n"); // Linea de asteriscos que hace que se separe una funcion de otra
}

/*
 * Función que imprime el un triangulo Incremental Do-While
 */
void trianguloInDW(short n)
{
	short i = 0; // Defincion de la variable i que comienza en 0 para que con la condicion y se hagan las 11 lineas
	do 
	{
		ciclointincremental(n, i); // Funcion que llama al ciclo interno de la funcion que hace el factorial 
		i++; // Incremento de uno en i ( i = i + 1 )
	} 
	while (i <= n); // La condicion para que se hagan los pasos anteriores pero se incia ya con un valor hecho  
	printf("*******************************************************************************\n\n\n\n"); // Linea de asteriscos que hace que se separe una funcion de otra
}

/*
 * Función que imprime el un triangulo Decremental Do-While
 */
void trianguloDeDW(short n)
{
	short i = n; // Definicion de la variable i en l funcion que sera n para que de ahicomience el decremento
	do
	{
		ciclointdecremental(n, i); // Funcion que llama al ciclo interno de la funcion que hace el factorial 
		i--; // Decremnto de uno en i (i = i -1)
	} 
	while (i >= 0); // Condicion que indica cuantas veces y hasta dond llega la funcion, es >= 0  para que se hagan las 11 lineas
	printf("*******************************************************************************\n\n\n\n"); // Linea de asteriscos que hace que se separe una funcion de otra
}

/*
 * Main de donde se mandan a llamar todas las funciones con cierto valor 
 */
int main()
		//INICIALIZACION DE LAS FUNCIONES 
{
	trianguloInFor(10);
	trianguloDeFor(10);
	trianguloInWhile(10);
	trianguloDeWhile(10);
	trianguloInDW(10);
	trianguloDeDW(10);
return 1;
}
