#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) //4996 


int funcion1()
{
	/*Calcular  la  suma  de  los  primeros  n  números  naturales (1 + ... + n).Utilizar 
	una variable para n y otra para el resultado.Desplegar en pantalla sólo el 
	resultado para n = 1000 y luego dejar una línea vacía.*/
	int result = 0, n = 0;

	while (result <= 1000)
	{
		n = n + result;
		result++;
	}

	printf("Resultado de la suma de numeros: %d\n", n);

	return 0;
}

int funcion2()
{
	/*Programar  la  fórmula  correspondiente  utilizando  variables  para 
	obtener  las  2  posibles  soluciones  para  x  de  la  siguiente  ecuación 
	desplegando cada solución en una línea diferente: 6x² ­ 5x +1 = 0*/
	float result1, result2;

	result1 = (((-5) + sqrt(25 - 24)) / 12);
	result2 = (((-5) - sqrt(25 - 24)) / 12);

	printf("El resultado de x1 = %.2f  y   x2 = %.2f\n", result1, result2);
	return 0;
}

int funcion3()
{
	/*Calcular  la  suma  de  las  primeros  n  números  naturales  elevados  a  la  4a 
	potencia  (1 +2 +3 +4 +...+(n­1) +n ).  Hacer  el  cálculo  para  la  variable 
	n=200 directo en el printf sin utilizar otra variable. Desplegar en pantalla la 
	palabra “SUMA Potencias” seguido de 2 tabuladores y el resultado. Dejar 
	2 líneas vacías después de la línea con el resultado.*/
	int result = 0, n = 0;

	for (int i = 1; i <= 200; i++)
	{
		n = n + result;
		result = result + pow(i, 4);
	}

	printf("SUMA Potencias\t\t%d\d\d", result);

	return 0;
}

int funcion4()
{
	/*Investigar  cuál  es  la  fórmula  que  sirve  para  calcular  la  siguiente  serie  o 
	progresión  con  20  números,  programarla  con  variables  y  desplegar  el 
	resultado final utilizando 10 decimales después del mensaje “resultado:”:
	11+5.5+2.75+1.375+...+0.000020981+0.00001049 */
	float result = 0;
	int n = 11;

	for (int i = 0; i < 20; i++)
	{
		n = (n / 2);
	}

	printf("Resultado: %.10f", result);

	return 0;
}

int main()
{
	int option;
	printf("Ricardo Gordoa A01020400 \n\n");
	printf("Selecciona la funcion que quieres correr : \n\n");
	printf("1.- Suma de numeros hasta 1000\n");
	printf("2.- Despeje de x en (6x² ­- 5x + 1 = 0)\n");
	printf("3.- Funcion de numeros elevados a la cuarta potencia\n");
	printf("4.- Funcion para dividir un numero a la mitad 20 veces\n");
	printf("Opcion: ");
	scanf("%d", &option);
	
	switch(option)
	{
	case 1 :
		funcion1();
		break;

	case 2 :
		funcion2();
		break;
		
	case 3 :
		funcion3();
		break;

	case 4 :
		funcion4();
		break;

	default:
		printf("Ha ingresado un numero no valido\n");
		break;
	}
	return 0;
}