/*
Nombre:Joan Andoni González Rioz
Matricula: A00569929

Examen Final
Fundamentos de Programación

Game catalogue
Reads a file with the collection of games. Allows for viewing of the game details,
computing the total cost of all games and adding new games.

HINT: Read the provided code to understand what you have to do and how to make it
work with the existing program.

QUESTIONS:
1. Complete the data structure that will hold the data read from the provided text file.
	Consider a string size of at least 20 characters. Use int for boolean values.
2. Create the function "read_file" that will read all the data from the text file and
	store it in an array of the game_data structure.
	Parameters received: the name of the file, the array of structures
	Return value: number of data entries read (full games) or -1 if the file could not be opened
3. Create the function "print_game_data" that will show the contents of one structur on the screen
	Parameters received: a single structure
	Return value: nothing
4. Create the function "total_catalogue_cost" that will compute the combined price of
	all the games in the list
	Parameters received: the array of structures, the number of games stored
	Return value: the total cost as a floating point number
5. Create the function "add_game" that will insert a new game to the array of structures
	and also add it to the text file. The function will ask the user for the necessary data
	Parameters received: the name of the file, the array of structures, the number of games stored
	Return value: 0 if the insertion was successful, -1 if the file could not be opened
*/
#define _CRT_SECURE_NO_DEPRECATE	// Stop the complaining from MS VS

#include <stdio.h>

#include <stdlib.h>

#define ARRAY_SIZE 10

#define STRING 20

// Structures
typedef struct game_data
{
	char game[STRING];
	char developer[STRING];
	char platform[STRING];
	int releaseYear;
	int numPlayers;
	int online;
	float price;
} game_data;

// Function prototypes
void menu_loop(void);
int read_file(char* filename, game_data all_games[ARRAY_SIZE]);
void print_game_data(game_data all_games);
float total_catalogue_cost(game_data all_games[], int numGames);
int add_game(char* filename, game_data all_games[], int numGames);

// EXAM: Add your function prototypes here:
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv


int main(int argc, const char * argv[])
{
	menu_loop();

	return 0;
}

/*
Function that displays the menu and manages the flow of the program.
*/
void menu_loop()
{
	char* filename = "game_catalogue.txt";
	game_data all_games[ARRAY_SIZE];
	int num_games = 0;
	int option = 1;
	int i;
	float games_cost;

	// Init the data from the file
	num_games = read_file(filename, &all_games);
	if (num_games == -1)
	{
		printf("Fatal Error! Better luck next time.\n");
		exit(0);
	}
	printf("Just read %d games from file '%s'\n", num_games, filename);

	// Start the user menu
	while (option != 0)
	{
		printf("\nUser menu:\n");
		printf("\t1. Print my game catalogue\n");
		printf("\t2. Print the total cost of my catalogue\n");
		printf("\t3. Add a game to my catalogue\n");
		printf("\t0. Exit the program\n");
		printf("Choose an option according to the action to take: ");
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			// Show all games
			for (i = 0; i < num_games; i++)
			{
				print_game_data(all_games[i]);
			}
			break;
		case 2:
			// Print cost of catalogue
			games_cost = total_catalogue_cost(all_games, num_games);
			printf("\nTotal cost of your library: %.2f\n", games_cost);
			break;
		case 3:
			if (add_game(filename, all_games, num_games) == -1)
			{
				printf("Fatal Error! Better luck next time.\n");
				exit(0);
			}
			else
			{
				num_games += 1;
				printf("You now have %d games\n", num_games );
			}
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

// EXAM: Place your functions here:
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

int read_file(char* filename, game_data all_games[ARRAY_SIZE])
{
    FILE* filePtr;
    int i = 0;
    
    filePtr = fopen(filename, "r");
    if (filePtr == NULL)
    {
        printf("Could not open file '%s' for reading.\n", filename);
        return -1;
    }

    for (i = 0 ; i < ARRAY_SIZE; i++)
    {
	    fscanf(filePtr, " %s", all_games[i].game);
   		fscanf(filePtr, " %s", all_games[i].developer);
    	fscanf(filePtr, " %s", all_games[i].platform);
    	fscanf(filePtr, " %d", &all_games[i].releaseYear);
    	fscanf(filePtr, " %d", &all_games[i].numPlayers);
    	fscanf(filePtr, " %d", &all_games[i].online);
    	fscanf(filePtr, " %f", &all_games[i].price);
    	if (feof(filePtr) || i > ARRAY_SIZE) 
			break;
    }  

    fclose(filePtr);
    return i;
}

void print_game_data(game_data games)
{
	printf("\nGame : %s\n", games.game);
	printf("\tDeveloper : %s\n", games.developer);
	printf("\tPlatform : %s\n", games.platform);
	printf("\tRelease Year : %d\n", games.releaseYear);
	printf("\tNumber of Players : %d\n", games.numPlayers);
	if (games.online == 1) printf("\tOnline : Yes\n");
	if (games.online == 0) printf("\tOnline : No\n");
	printf("\tPrice : %.2f\n", games.price);
}

float total_catalogue_cost(game_data all_games[], int numGames)
{
	float cost = 0;
	int i;

	for(i = 0; i < numGames; i++)
	{
		cost += all_games[i].price;
	}

	return cost;
}

int add_game(char* filename, game_data all_games[], int numGames)
{
    FILE* filePtr;
    
	if (numGames >= ARRAY_SIZE)
	{
		printf("\nYou don´t have more space to add a game\n");
		return 1;
	}

	if (numGames < ARRAY_SIZE)
	{
		filePtr = fopen(filename, "a");
		if (filePtr == NULL)
		{
			printf("Could not open file '%s' for writing.\n", filename);
			return -1;
		}

		printf("\nGive me the data of the new game...\n");
		printf("Name : ");
		scanf("%s", all_games[numGames].game);
		fprintf(filePtr, "\n\n%s\n", all_games[numGames].game);
		printf("Developer : ");
		scanf("%s", all_games[numGames].developer);
		fprintf(filePtr, "%s\n", all_games[numGames].developer);
		printf("Platform : ");
		scanf("%s", all_games[numGames].platform);
		fprintf(filePtr, "%s\n", all_games[numGames].platform);
		printf("Release Year : ");
		scanf("%d", &all_games[numGames].releaseYear);
		fprintf(filePtr, "%d\n", all_games[numGames].releaseYear);
		printf("Number of Players : ");
		scanf("%d", &all_games[numGames].numPlayers);
		fprintf(filePtr, "%d\n", all_games[numGames].numPlayers);
		printf("Online( Yes: 1 | No: 0 ): ");
		scanf("%d", &all_games[numGames].online);
		fprintf(filePtr, "%d\n", all_games[numGames].online);
		printf("Price : ");
		scanf("%f", &all_games[numGames].price);
		fprintf(filePtr, "%.2f\n", all_games[numGames].price);

		fclose(filePtr);
		return 0;
	}
}