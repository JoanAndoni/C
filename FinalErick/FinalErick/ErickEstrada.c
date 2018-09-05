// Erick Estrada 
// Proyecto final de programación
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

//función que lee el archivo de texto con el arreglo de tamaño 150 como parametro.
void lector(int datosRecibo[150])
{
	FILE *myData;
	int aux;
	if ((myData = fopen("datos.txt", "r")) == NULL)	printf("No se encuentra el documento que esta buscando.");
	else
	{
		for (int i = 0; i < 150; i++)
		{
			fscanf(myData, "%d\n", &aux);
			datosRecibo[i] = aux;
		}
		fclose(myData); 
	} 
}

double sacarMedia(int array[150])
{
	double suma = 0, media;

	for (int i = 0; i < 150; i++) suma = suma + array[i];
	media = (suma / 150);

	return media;
}

void asignarMedia(double array[4], double media)
{
	array[0] = media;
	printf("\nEsta es la media: %f\n\n", array[0]);
}

void ordenamientoDatos(int array[150])
{
	int a = 0, aux;

	while (a < 150)
	{
		int b = a + 1;
		while (b < 150)
		{
			if (array[a] > array[b])
			{
				aux = array[a];
				array[a] = array[b];
				array[b] = aux;
			}
			b++;
		}
		a++;
	}
}

double sacarMediana(int array[150])
{
	int numero1 = (150 / 2) - 1, numero2 = 150 / 2;
	double mediana = (array[numero1] + array[numero2]) / 2;
	return mediana;
}

void asignarMediana(double array[4],double mediana)
{
	array[1] = mediana;
	printf("\nEsta es la mediana: %f\n\n", array[1]);
}

double sacarVarianza(int array[150], double media)
{
	double varianza, sumatoria = 0;

	for (int i = 0; i < 150; i++) sumatoria = sumatoria + (pow((array[i] - media), 2));
	varianza = sumatoria/149;

	return varianza;
}

void asignarVarianza(double array[4], double varianza)
{
	array[2] = varianza;
	printf("\nEsta es la varianza: %f\n\n", array[2]);
}

double sacarDesviacion(int array[150], double varianza)
{
	double desviacion = sqrt(varianza);
	return desviacion;
}

void asignarDesviacion(double array[4], double desviacion)
{
	array[3] = desviacion;
	printf("\nEsta es la desviacion estandar: %f\n\n", array[3]);
}

void escribirResultados(double array[4])
{
	FILE* filePtr;
	if ((filePtr = fopen("resultados.txt", "w")) == NULL) printf("No se pudo crear el archivo.\n");
	else
	{
		for (int i = 0; i < 4; i++) fprintf(filePtr, " %f\n", array[i]);
		fclose(filePtr);
	}
}

void leerResultados()
{
	float array[4], aux;
	FILE* filePtr;
	if ((filePtr = fopen("resultados.txt", "r")) == NULL) printf("No se encuentra el documento que esta buscando.\n");
	else
	{
		for (int i = 0; i < 4; i++)
		{
			fscanf(filePtr, " %f\n", &aux);
			array[i] = aux;
		}
		printf("\nMedia es un double : %f\n", array[0]);
		printf("Mediana es un double : %f\n", array[1]);
		printf("Varianza es un double : %f\n", array[2]);
		printf("Desviacion estandar es un double : %f\n", array[3]);
		printf("Los 150 datos recopilados eran Integers\n\n");
		fclose(filePtr);
	}
}

int main()
{
	int datos[150];
	double resultados[4], mediana, media, varianza, desvEsta;

	//Funcion para leer todos los datos
	lector(datos);

	//Funciones de media
	media = sacarMedia(datos);
	asignarMedia(resultados, media);

	//Ordenamiento de datos
	printf("El arreglo de datos desordenado:\n\n");
	for (int i = 0; i < 150; i++) printf("%d\n", datos[i]);
	ordenamientoDatos(datos);
	printf("\nEl arreglo de datos ordenado:\n\n");
	for (int i = 0; i < 150; i++) printf("%d\n", datos[i]);

	//Funciones de mediana
	mediana = sacarMediana(datos);
	asignarMediana(resultados, mediana);

	//Funciones de varianza
	varianza = sacarVarianza(datos, resultados[0]);
	asignarVarianza(resultados, varianza);

	//Funciones de desviacion estandar
	desvEsta = sacarDesviacion(datos, resultados[2]);
	asignarDesviacion(resultados, desvEsta);

	//Funcion para crear un documento y escribir los resultados
	escribirResultados(resultados);

	//Funcion que lee los resultados y los desplega diciendo que tipo de archivos son los 150 datos
	leerResultados();

	return 0;
}