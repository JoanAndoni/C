#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996) //4996
#define PI 3.1416

double Degre2Rad(double degrees)
{
	double radians;
	radians = ((degrees*PI)/180);
	
	return radians;
}

double Rad2Degre(double radians)
{
	double degrees;
	degrees = ((radians*180)/PI);

	return degrees;
}

double Polar2Carte(double angle, double h)
{
	double x, y;
	x = h * cos(angle);
	y = h * sin(angle);

	printf("\nCartesian coordinate : (%.2lf, %.2lf) \n\n", x, y);
	
	return 0;
}

double Carte2Polar(double x, double y)
{
	double angle, angleRad, finalAngle, h;

	h = sqrt((pow(x, 2))+(pow(y, 2)));
	angle = (y / x);
	angleRad = atan(angle);
	finalAngle = Rad2Degre(angleRad);
	printf("\nPolar coordinate : h = %.2lf | angle = %.2lf\n\n", h, finalAngle);

	return 0;
}

int FunPolar()
{
	double h, angle, angleRad;
	printf("\nGive me the magnitud of the vector and his angle\n\n");
	printf("\th = ");
	scanf("%lf", &h);
	printf("\tangle = ");
	scanf("%lf", &angle);

	printf("\nPolar coordinate : angle = %.2lf | h = %.2lf", angle, h);

	angleRad = Degre2Rad(angle);
	Polar2Carte(angleRad, h);

	return 0;
}

int FunCart()
{
	double x, y;
	printf("\nGive me the points of the cartesian coordinate\n\n");
	printf("\tx = ");
	scanf("%lf", &x);
	printf("\ty = ");
	scanf("%lf", &y);

	printf("\n\nCartesian coordinate = (%.2lf , %.2lf)", x, y);

	Carte2Polar(x, y);

	return 0;
}

int condition()
{
	char r;
	printf("What conversion do you want?\n\n\tCartesian to polar : 'c'\n\tPolar to cartesian : 'p'\n");
	printf("r = ");
	scanf("%c", &r);

	if (r == 'c')
	{
		FunCart();
	}

	if (r == 'p')
	{
		FunPolar();
	}
	
	return 0;
}

int main()
{
		condition();
		
		return 0;
}