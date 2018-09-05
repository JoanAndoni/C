// Joan Andoni González Rioz 
// A00569929

#include <stdio.h>
#include <string.h>
//Libraries for using the getopt
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#define LENG 50

int power(int base, unsigned int exp){
    int i, result = 1;
    for (i = 0; i < exp; i++)
        result *= base;
    return result;
}

int makeCharNumber(char letter) {
    if (letter >= '0' && letter <= '9')
        return (int)letter - '0';
    else
        return (int)letter - 'A' + 10;
}

char makeNumberChar(int number) {
    if (number >= 0 && number <= 9)
        return (char)(number + '0');
    else
        return (char)(number - 10 + 'A');
}

int operation2dec(int arrayNumbers[LENG], int base, int numbers) {
    int sum = 0;
    for(int i = 0; i < numbers; i++)
        sum += arrayNumbers[i]*(power(base, i));
    return sum;
}

void dec2other(char alreadyConverted[LENG], int baseToConvert, int numDec) {
    int i = 0;
    while(numDec != 0){
        alreadyConverted[i] = makeNumberChar(numDec%baseToConvert);
        numDec = numDec/baseToConvert;
        i++;
    }
}

void makeAll(char NumberToConvert[LENG], int actualBase, int baseToConvert) {
    char alreadyConverted[LENG];
    int arrayNumbers[LENG];
    
    // IN THIS LOOP WE ARE CHECKING THE STRING TO MAKE IT A NUMBER FOR WORK //
    for(int counter = 0; counter < strlen(NumberToConvert); counter++)
        arrayNumbers[(strlen(NumberToConvert))-(counter+1)] = makeCharNumber(NumberToConvert[counter]);

    dec2other(alreadyConverted, baseToConvert, operation2dec(arrayNumbers, actualBase, strlen(NumberToConvert)));

    // PRINT THE CONVERTION //
    printf("Converting %s from base %d to base %d\n", NumberToConvert, actualBase, baseToConvert);
    printf("Converted to base %d: ", baseToConvert);
    for(int index = strlen(alreadyConverted); index >=0 ; index--)
        printf("%c", alreadyConverted[index]);
    printf("\n");
}

void print_usage() {
    printf("Usage: -i [Initial Base] -o [Base to convert] [NUM] [NUM] [NUM] ...\n");
}

int main(int argc, char **argv) {
    int option_index = 0, actualBase = -1, baseToConvert = -1;
    while ((option_index = getopt(argc, argv, "i:o: ")) != -1){
        switch (option_index) {
            case 'i':
                actualBase = atoi(optarg);
                break;
            case 'o':
                baseToConvert = atoi(optarg);
                break;
            default:
                print_usage();
                return 1;
        }
    }
    for(int i = 5 ; i < argc; i++){
        makeAll(argv[i], actualBase, baseToConvert);
        printf("\n");
    }
    return 0;
}