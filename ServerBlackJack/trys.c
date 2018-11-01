/*
    Joan Andoni González Rioz A00569929
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int sumCards(char *cards[2]){
  int sum = 0;
  for (int i = 0; i < 2; i++) {
    if (strcmp( cards[i], "A") == 0) {
      sum += 11;
    } else if (strcmp( cards[i], "2") == 0) {
      sum += 2;
    } else if (strcmp( cards[i], "3") == 0) {
      sum += 3;
    } else if (strcmp( cards[i], "4") == 0) {
      sum += 4;
    } else if (strcmp( cards[i], "5") == 0) {
      sum += 5;
    } else if (strcmp( cards[i], "6") == 0) {
      sum += 6;
    } else if (strcmp( cards[i], "7") == 0) {
      sum += 7;
    } else if (strcmp( cards[i], "8") == 0) {
      sum += 8;
    } else if (strcmp( cards[i], "9") == 0) {
      sum += 9;
    } else if (strcmp( cards[i], "10") == 0) {
      sum += 10;
    } else if (strcmp( cards[i], "J") == 0) {
      sum += 10;
    } else if (strcmp( cards[i], "Q") == 0) {
      sum += 10;
    } else if (strcmp( cards[i], "K") == 0) {
      sum += 10;
    }
  }
  return sum;
}

int main(int argc, char const *argv[]) {
  char *cards[13] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K"};

  srand(time(NULL));   // initial the random once
  int r = rand() % 13; // random int between 0 and 13

  char *dealerCards[2];
  for (int i = 0; i < 2; i++) {
    dealerCards[i] = cards[rand() % 13];
  }

  int sum = sumCards(dealerCards);
  printf("%d\n", sum);

  return 0;
}
