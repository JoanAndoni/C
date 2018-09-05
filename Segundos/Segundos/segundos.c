#include <stdio.h>
#define _CRT_SECURE_NO_DEPRECATE

int segundos(int x)
{
	int s;
	x = s;
	printf("\n %d Segundos", s);
	return 0;
}

int minutos(int x)
{
	int s, mi;
	(x/60) = mi;
	(x%60) = s;
	printf("\n %d Minutos", mi);
	printf("\n %d Segundos", s);
	return 0;
}

int horas(int x)
{
	int s, mi, h, i;
	(x/3600) = h;
	(x%3600) = i;
	(i/60) = mi;
	(i%60) = s;
	printf("\n %d Horas", h);
	printf("\n %d Minutos", mi);
	printf("\n %d Segundos", s);
	return 0;
}

int dias(int x)
{
	int s, mi, h, d, i, i2;
	(x/86400) = d;
	(x%86400) = i2;
	(i2/3600) = h;
	(i2%3600) = i;
	(i/60) = mi;
	(i%60) = s;
	printf("\n %d Dias", d);
	printf("\n %d Horas", h);
	printf("\n %d Minutos", mi);
	printf("\n %d Segundos", s);
	return 0;
}

int semanas(int x)
{
	int s, mi, h, d, sem, i, i2, i3;
	(x/604800) = sem; 
	(x%604800) = i3;
	(i3/86400) = d;
	(i3%86400) = i2;
	(i2/3600) = h;
	(i2%3600) = i;
	(i/60) = mi;
	(i%60) = s;
	printf("\n %d Semanas", sem);
	printf("\n %d Dias", d);
	printf("\n %d Horas", h);
	printf("\n %d Minutos", mi);
	printf("\n %d Segundos", s);
	return 0;
}

int operaciones()
{
	int x, n;
	printf("Dame el numero de segundos que quieras");
	scanf("%d \n", &x);
	x = n;
	printf("%d segundos es igual a: \n", x);
	
	if ( 604800 > x ) semanas(n);

	if ( (604800 > x) && (x > 86400) ) dias(n);

	if ( (86400 > x) && (x > 3600) ) horas(n);

	if ( (3600 > x) && (x > 60) ) minutos(n);

	if ( 60 > x ) segundos(x);

	return 0;
}

int main()
{
	operaciones();

	return 0;
}