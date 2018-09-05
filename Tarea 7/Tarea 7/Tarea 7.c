
#include <stdio.h>
#include <math.h>
#define PI (3.141592653589793)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

// Calculadora que en el main te pida dos numeros reales positivos de 1000.0 para abajo
// Despues de dar los numeros hacer un printf con las opciones de matematicas que se requieran hacer
// A cada operacion se le dara el valor de una letra para que sea llamda la funcion en el output
// Primeras operaciones: Suma, Resta, Multiplicacion, Division, Potencia y Modulo con los dos numeros ya pedidos
// Segundas operaciones: Raiz cuadrada, seni,coseno, tangente,exponencial y logaritmo (Para las funciones trigonometricas hay que convertir a radianes)
// Desplear en resultado de la operacion corepondiente a cada caso
// Pedir con dos letras el reinicio del programa y otra para salirte de el

//Funcion que pide los numeros te dalas opciones de operaciones y las ejecuta 
void numeros() 
{
	double x = 0, y = 0, resultado = 0; //Inicializacion de las tres variables x , y, elresultado para la acumulacion de puntos definidas por double para que tambien haya numeros reales
	char respuesta; //Definicion de la varable respuesta para recibir la operacion que se necesita
	printf("Introduce los dos numeros con los que quieres hacer operaciones\n"); //Funcion que despliega en la pantalla la indicacion de meter un valor
	scanf("%lf %lf", &x, &y);//Funcion que recibe el valor que se le dara a respuesta
	printf("Valor de x: %.1lf\n", x); // Imprime el valor de x
	printf("Valor de y: %.1lf\n", y);// Imprime el valor de y
	printf("\nQue operacion quieres hacer?\n  Suma-\ta\n  Resta-\tb\n  Multiplicacion-\tc\n  Division-\td\n  Potencia-\te\n  Modulo-\tf\n");//Funcion que imprime las opciones de operaciones
	printf("Raiz cuadrada-\tg\n  Exponencial-\th\n  Logaritmo base 10-\ti\n  Logaritmo base e-\tj\n  Seno-\tk\n  Coseno-\tl\n  Tangente-\tm\n");// Funcion que imprime las opciones de operaciones 
	double radianesx = (x * PI) / 180, radianesy = (y * PI) / 180;//Funcion que convierte el valor de X y Y en radianes
	
	scanf("%s", &respuesta);// Funcion que recibe el valor de respuesta para elegir las funciones

		if (respuesta == 'a')//Si la respuesta es a hace la operacion de suma
		{
			resultado = x + y; //Suma de los valores acumulandolos en la variable resultado
			printf("\nResultado = %.1lf\n", resultado);//Funcion que imprime el resultado de la suma
		}
		else if (respuesta == 'b')//Si la respuesta es b hace la operacion de la resta 
		{
			resultado = x - y;//Funcion que hace la resta y la acumula en la variable resultado
			printf("\nResultado = %.1lf\n", resultado);//Funcion que imprime el valor final de la resta
		}
		else if (respuesta == 'c')//Si la respuesta es c hace la operación de la multiplicación
		{
			resultado = x * y;//Funcion que hace la multiplicacion de x ,y acumulandolo en la variable resultado
			printf("\nResultado = %.1lf\n", resultado);// Funcion que imprime el valor de la multiplicacion
		}
		else if (respuesta == 'e')//Si la respuesta es e hace una potencia
		{
			printf("\nResultado = pow(%.1lf, %.1lf) = %.1lf\n", x, y, pow(x, y));// Funcion que hace e imprime la potencia de x , y
		}
		else if (respuesta == 'd')// Si la respuesta es d se hace una division
		{
			resultado = x / y;// Funcion que hace la division de x entre y, y lo acumula en la variable resultado
			printf("\nResultado = %.1lf\n", resultado);// Funcion que imprime el resultado de la division 
		}
		else if (respuesta == 'f')// Cuando la respuesta es f hace el modulo 
		{
			printf("\nResultado = fmod(%.1lf/%.1lf) = %.1lf", x, y, fmod(x, y));// Funcion que hace la operacio e imprime el modulo de los dos numeros
		}
		else if (respuesta == 'g')// Cuando la respuesta es g se hace la raiz cuadrada de los valores
		{
			printf("\nResultado x = sqrt(%.1lf) = %.1lf\n", x, sqrt(x));//Funcion que hace e imprime la funcion de la raiz cuadrada de x
			printf("\nResultado y = sqrt(%.1lf) = %.1lf\n", y, sqrt(y));//Funcion que hace e imprime la funcion de la raiz cuadrada de y
		}
		else if (respuesta == 'h')// Cuando la respuesta es h se hace la funcion exponencial
		{
			printf("\nResultado x = exp(%.1lf) = %.1lf\n", x, exp(x));// Funcion que hace la operacion exponencial y la imprime para x
			printf("\nResultado y = exp(%.1lf) = %.1lf\n", y, exp(y));// Funcion que hace la operacion exponencial y la imprime para y
		}
		else if (respuesta == 'i')//Cuando la respuesta es i se hara el logaritmo base 10 de x, y
		{
			printf("\nResultado x = log10(%.1lf) = %.1lf\n", x, log10(x));// Funcion que hace la operacion e imprime el valor final de x
			printf("\nResultado y = log10(%.1fl) = %.1lf\n", y, log10(y));// Funcion que hace la operacion e imprime el valor final de y
		}
		else if (respuesta == 'j')//Cuando la respuesta es j se hara el logaritmo base e de x, y
		{
			printf("\nResultado x = log(%.1lf) = %.1lf\n", x, log(x));// Funcion que hace la operacion e impresion de el logaritmo de x
			printf("\nResultado y = log(%.1lf) = %.1lf\n", y, log(y));// Funcion que hace la operacion e impresion de el logaritmo de y
		}
		else if (respuesta == 'k')// Cuando la respuesta es k se hara el seno de x, y
		{
			printf("\Resultado x = sin(%.1lf) = %.1lf\n", radianesx, sin(radianesx));//Funcion que hace el seno de x convertido en radianes
			printf("\Resultado y = sin(%.1lf) = %.1lf\n", radianesy, sin(radianesy));//Funcion que hace el seno de y convertido en radianes
		}
		else if (respuesta == 'l')//Cuando la respuesta es l se hara el coseno de x, y
		{
			printf("\Resultado x = cos(%.1lf) = %.1lf\n", radianesx, cos(radianesx));//Funcion que hace el coseno de x convertido en radianes
			printf("\Resultado y = cos(%.1lf) = %.1lf\n", radianesy, cos(radianesy));//Funcion que hace el coseno de y convertido en radianes
		}
		else if (respuesta == 'm')// Cuando la respuesta es m se hara la tangente de x, y
		{
			printf("\Resultado x = tan(%.1lf) = %.1lf\n", radianesx, tan(radianesx));//Funcion que hace el tangente de x convertido en radianes
			printf("\Resultado y = tan(%.1lf) = %.1lf\n", radianesy, tan(radianesy));//Funcion que hace el tangente de y convertido en radianes
		}
}

// Funcion que manda a llamar funciones y las ejecuta en el programa
int main()
{
	char response = 's'; // Definicion de la variable response que tiene valor 's'

	while (response != 'n') // Ciclo condicionado a que cuando la respuesta sea diferente de n corra el programa
	{
		numeros();//Funcion inicializada que hace todas las operaciones
		printf("\nQuieres hacer otra operacion?\n(Si = s , No = n)\n");//Funcion que imprime las indicaciones al terminar el programa para volver a comenzar
		scanf("%s", &response);// Funcion que recibe el valor de response que puede iniciar o terminar el programa
	} 
	return 0;
}