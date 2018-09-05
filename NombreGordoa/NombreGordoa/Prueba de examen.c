//siempre comenzamos el programa con un include stdio
#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) //4996 
//el int main es lo que corre el programa y donde corre nuestro programa 

//	FUNCIONES

int gordoa() // es una funcion comun y corriente 
{
	double numero1, numero2;
	double resultadoPotencia;
	double resultadoRaiz;

	numero1 = 4;
	numero2 = 8;
	
	resultadoPotencia = pow( numero1, numero2 ); //  4^8 = Primer numero elevado a la potencia del numero 2

	printf("\n\nEl resultado de la potencia es: %.2f\n",resultadoPotencia);
	
	numero1 = 25;

	resultadoRaiz = sqrt( numero1 );

	printf("El resultado de la raiz es: %.2f\n",resultadoRaiz);

	return 0;
}

void erick()
{
	
}


int main(){

	//int es definir una variable, un numero entero
	//float es definir una variable con números decimales
	//char es definir una variable, una letra 
	int enteros = 5;
	float decimales = 5.574576;
	double doubl = 3.9;
	char letra = 'R';

	// %d es para imprimir cualquier int
	// %f es para imprimir cualquier float
	// %c es para imprimircualquier char

	printf("Entero = %d\n", enteros); //     \n : Es un enter
	printf("Decimal = %f\n", decimales);
	printf("Letra = %c\n", letra);

	// CONDICIONES

	int home, guest;
	home = 79;
	guest = 79;

	if (home > guest) // Condicional y tiene las propiedades :  
		//  < menor que  
		//  > mayor que
		//  == igual
		//  >= igual o mayor que
		//  <= igual o menor que
		//  != diferente de
	{
		printf("home wins\n");

	}
	else if (guest > home)
	{
		printf("guest wins\n");
	}
	else // se hace todo lo que nohace el if
	{
		printf("Hay empate \n");
	}

	// CICLOS, While y For

	int i = 0;

	while (i <= 10)
	{
		printf("El valor de i es: %d\n", i);

		if (i == 6)
		{
			printf("Se ulitiza break\n");
			break;
		}

		i = i + 1;    // i++    ->     i = i + 1       ->      i += 1   
	}

	int f;

	for (f = 10; f >= 0; f--) // f--      ->      f = f - 1       ->        f -= 1 
	{
		printf("\nEl valor de f es: %d", f);
	}


	gordoa();


	int option;
	printf("\n\n1.- Erick\n");
	printf("2.- Gordoa\n");
	printf("3.- Gero\n");
	printf("Introduce que opcion quieres\n");
	scanf("%d", &option); // Para pedir el valor de una variable y ahuevo tiene que tener -> &

	switch(option)
	{
		case 1:
			printf("Erick es putito #28\n");
			break;

		case 2:
			printf("Gordoa es una tetera #54\n");
			break;

		case 3:
			printf("Gero es pendejo #1\n");
			break;

		default:
			printf("Se chingo no existe\n");
	}



//el return siempre va al finalde nuestro programa y es obligatorio el return 
// si es que hay un int main.

	return 0;
}