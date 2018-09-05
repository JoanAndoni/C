/*
Nombre:Joan Andoni González Rioz
Matricula: A00569929

Second Partial Exam
Program to register the cars that enter and exit a parking lot
Use an array for parking places and store the license plates of the cars parked in each place.
Empty parking places will be indicated by a 0 in the array.
License plates are positive integers of up to 3 digits. The number can NOT be 0.

Questions:
1. Complete the function "register_car".
	It receives as a parameter the array of the parking
	It will return nothing.
	It will ask for the license plates of the car to register (you can use the "input_license" function)
	It will look for the next available space (one containing 0) and change the value for the license plate of the car
	If the car is already in the parking (you can use the "search_car" function), or if there are no more places,
	print a warning message
2. ------------------------------------Complete the "search_car" function. 
	It receives three parameters: the array, an int with the license number to search for and a pointer to int
	It will return 1 if the car was found, 0 if it was NOT found.
	The current location of the car (the index of the array) is returned via reference, using the third parameter to the function
	This function should not print anything. Other functions may print messages depending on the results from this one
3. Create the function "remove_car".
	It will return nothing.
	It receives the array of the parking places
	It will ask for the license plates of the car to remove (you can use the "input_license" function)
	Once the license plate is found, it will be replaced by 0 and print a message indicating which place has been freed.
	If the car is not found, print a warning message.
*/

#define _CRT_SECURE_NO_DEPRECATE	// Stop the complaining from MS VS
// http://www.cplusplus.com/forum/beginner/2300/

#include <stdio.h>

#define PARKING_PLACES 10


void parking_loop(void);
void register_car(int* parking_array);
void remove_car(int* parking_array);
void query_car(int* parking_array);
int search_car(int* parking_array, int license, int* location);
int input_license(void);
void print_parking_array(int* parking_array);

int main()
{
	printf("PARKING REGISTRY PROGRAM\n");
	printf("========================\n");
	parking_loop();

	return 0;
}

/*
	Main loop for the program. It shows the user menu.
*/
void parking_loop(void)
{
	int option = 1;
	int parking_places[PARKING_PLACES] = { 0 };

	while (option != 0)
	{
		printf("\nUser menu:\n");
		printf("\t1. Enter a new car in the parking lot\n");
		printf("\t2. Remove a car from the parking lot\n");
		printf("\t3. Search the parking lot for a car and print the place it uses\n");
		printf("\t4. Print all cars in the parking lot\n");
		printf("\t0. Exit the program\n");
		printf("Choose an option according to the action to take: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			register_car(parking_places);
			break;
		case 2:
			remove_car(parking_places);
			break;
		case 3:
			query_car(parking_places);
			break;
		case 4:
			print_parking_array(parking_places);
			break;
		case 0:
			printf("Thanks for using the system\n");
			break;
		default:
			printf("Invalid option. Try again\n");
			break;
		}
	}
}

void register_car(int* parking_array)
{
	int i, existente, spots = 0, location;

	for (i = 0; i < 10; i++)
	{
		if (parking_array[i] == 0) spots = 1; 
	}
	if (spots == 0) printf("There are no spots\n");

	for (i = 0; i < 10; i++)
	{
		if (parking_array[i] == 0)
		{
			int license = input_license();
			existente = search_car(parking_array, license, &location);
			if (existente == 1) printf("The car is already in the parking in the spot %d", location);
			if (existente == 0)
			{
				parking_array[i] = license;
				printf("The car is in the spot: %d", i);
			}
			i = 10;
		}
	}
	
}

void remove_car(int* parking_array)
{
	int location, license;

	printf("Search of a registered car ->\n");
	license = input_license();
	search_car(parking_array, license, &location);
	parking_array[location] = 0;
	printf("The place %d has been freed\n", location);
}


void query_car(int* parking_array)
{
	int location;
	int license;

	printf("Search of a registered car ->\n");
	license = input_license();
	if (license)
	{
		if (search_car(parking_array, license, &location))
		{
			printf("The car is parked in box number [%3d]\n", location);
		}
		else
		{
			printf("That car is not registered in this parking lot. Sorry!\n");
		}
	}
}

int search_car(int* parking_array, int license, int* location)
{
	int option = 0, i;

	for (i = 0; i < 10; i++)
	{
		if (parking_array[i] == license)
		{
			option = 1;
			*location = i;
		}
	}

	if(option == 1) return 1;
	if(option == 0) return 0;
}

int input_license()
{
	int license;

	printf("Enter the license plate number of the car (3 digits, different from 0): ");
	scanf("%d", &license);

	if (license > 0 && license < 1000)
	{
		return license;
	}
	else
	{
		printf("That is not a valid license number! Try again.\n");
		return 0;
	}
}

void print_parking_array(int* parking_array)
{
	int i;

	for (i = 0; i < PARKING_PLACES; i++)
	{
		printf("Place: [%3d] -> Car license: '%3d'\n", i, parking_array[i]);
	}
}