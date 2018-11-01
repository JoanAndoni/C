/*
    Joan Andoni González Rioz A00569929
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>

#include "sockets.h"

#define SERVICE_PORT 8642
#define BUFFER_SIZE 1024

void usage(char * program);
void connectToServer(char * address, char * port);
void communicationLoop(int connection_fd);

int main(int argc, char * argv[])
{
    printf("\n=== PLAYER PROGRAM ===\n");

    if (argc != 3)
        usage(argv[0]);

    connectToServer(argv[1], argv[2]);

    return 0;
}

// Show the user how to run this program
void usage(char * program)
{
    printf("Usage:\n%s {server_address} {port_number}\n", program);
    exit(EXIT_FAILURE);
}

// Establish a connection with the server indicated by the parameters
void connectToServer(char * address, char * port)
{
    struct addrinfo hints;
    struct addrinfo * server_info;
    int connection_fd;

    // Prepare the information to determine the local address
    bzero(&hints, sizeof hints);
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    ///// GETADDRINFO
    // Get the actual address of this computer
    if (getaddrinfo(address, port, &hints, &server_info) == -1)
    {
        perror("getaddrinfo");
        exit(EXIT_FAILURE);
    }

    ///// SOCKET
    // Use the information obtained by getaddrinfo
    connection_fd = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
    if (connection_fd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    ///// CONNECT
    // Connect with the desired port
    if (connect(connection_fd, server_info->ai_addr, server_info->ai_addrlen) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Release the memory of the list of addrinfo
    freeaddrinfo(server_info);

    // Establish the communication
    communicationLoop(connection_fd);

    // Close the socket
    close(connection_fd);
}

int sumCards(char *cards[20], int count){
  int sum = 0;
  for (int i = 0; i < count; i++) {
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

void printCards(char *cards[20], char *dealerCard, int count, int sum) {
  printf("\nYour cards:\n");
  for (int i = 0; i < count; i++) {
    printf("\t%d.- %s\n", i+1, cards[i]);
  }
  printf("Sum of your cards: %d\n", sum);
  printf("Dealer card: %s\n", dealerCard);
}

// Do the actual receiving and sending of data
void communicationLoop(int connection_fd)
{
    char buffer[BUFFER_SIZE];

    char *userCards[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for (int i = 0; i < 20; i++) userCards[i] = (char *) malloc(3);
    char *dealerCard[1];
    dealerCard[0] = (char *) malloc(3);
    int bet, count = 0, sum, secondBet, option = 1, decition = 0, dealerSum;

    // Handshake
    sprintf(buffer, "HELLO");
    sendMessage(connection_fd, buffer, strlen(buffer));
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);

    // Send the first bet
    printf("Enter your first bet: ");
    scanf("%d", &bet);
    sprintf(buffer, "%d", bet);
    sendMessage(connection_fd, buffer, strlen(buffer));

    // Recieving cards
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sscanf(buffer, "%s", userCards[count]);
    printf("This is your first card: %s\n", userCards[count]);
    count++;
    sprintf(buffer, "OK");
    sendMessage(connection_fd, buffer, strlen(buffer));

    // Recieve your second card
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sscanf(buffer, "%s", userCards[count]);
    printf("This is your second card: %s\n", userCards[count]);
    count++;
    sprintf(buffer, "OK");
    sendMessage(connection_fd, buffer, strlen(buffer));

    //Recieve the card of the dealer
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sscanf(buffer, "%s", dealerCard[0]);
    printf("This is the first card of the dealer: %s\n", dealerCard[0]);

    //Send the sum of my cards
    sum = sumCards(userCards, count);
    sprintf(buffer, "%d", sum);
    sendMessage(connection_fd, buffer, strlen(buffer));

    if (sum == 21) {
      receiveMessage(connection_fd, buffer, BUFFER_SIZE);
      sscanf(buffer, "%d", &bet);
      printf("\nYou made a BlackJack congratulations you already won: %d\n", bet);
      exit(0);
    }

    printCards(userCards, dealerCard[0], count, sum);

    //Recieve the decition
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    printf("\nWhat you want to do?\n\t1. Raise bet\n\t2. Stand\n Decition: ");
    scanf("%d", &decition);

    // Send the decition 1
    sprintf(buffer, "%d", decition);
    sendMessage(connection_fd, buffer, strlen(buffer));
    switch (decition) {
      case 1:
      //1.1
      receiveMessage(connection_fd, buffer, BUFFER_SIZE);
      printf("\nHow much you want to raise the bet: ");
      scanf("%d", &secondBet);
      sprintf(buffer, "%d", secondBet);
      //1.2
      sendMessage(connection_fd, buffer, strlen(buffer));
      bet = bet + secondBet;
      break;

      case 2:
      printf("\nYoure going to stay with your first bet\n");
      break;
    }

    printf("This is your bet: %d\n", bet);

    // Getting the option for starting the loop 2
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);

    while ( option != 0 )
    {
      printf("\nWhat you want to do?\n\t1. Get another card\n\t2. Stay with my cards\nOption: ");
      scanf("%d", &option );
      sprintf(buffer, "%d", option);
      sendMessage(connection_fd, buffer, strlen(buffer)); //3
      switch (option) {
        case 1:
        // Recieve another card
        receiveMessage(connection_fd, buffer, BUFFER_SIZE);
        sscanf(buffer, "%s", userCards[count]);
        printf("\nTheres another card: %s\n", userCards[count]);
        count++;
        // Sending the sum of the cards
        sum = sumCards(userCards, count);
        sprintf(buffer, "%d", sum);
        sendMessage(connection_fd, buffer, strlen(buffer));
        // Check if you already passed the 21
        if (sum > 21) {
          printf("You have passed 21 with the sum of your cards: %d\n", sum);
          receiveMessage(connection_fd, buffer, BUFFER_SIZE);
          sscanf(buffer, "%d", &bet);
          printf("You have lost this amount: %d\n", bet);
          option = 0;
        } else {
          receiveMessage(connection_fd, buffer, BUFFER_SIZE);
          printCards(userCards, dealerCard[0], count, sum);
        }
        break;

        case 2:
        printf("\nLet's reveal the cards...\n");
        receiveMessage(connection_fd, buffer, BUFFER_SIZE);
        sscanf(buffer, "%d", &dealerSum);
        sprintf(buffer, "OK");
        sendMessage(connection_fd, buffer, strlen(buffer));
        printf("Dealer sum of cards: %d\n", dealerSum);
        if (sum == dealerSum) {
          receiveMessage(connection_fd, buffer, BUFFER_SIZE);
          sscanf(buffer, "%d", &bet);
          printf("You have the same sum of cards as the dealer: %d, you get back your bet: %d$\n", sum, bet);
        } else if ((21 - dealerSum) < (21 - sum)) {
          receiveMessage(connection_fd, buffer, BUFFER_SIZE);
          sscanf(buffer, "%d", &bet);
          printf("Your sum of cards: %d is farther than dealers cards: %d, so you loss the amount of the bet: %d$\n", sum, dealerSum, bet);
        } else if ((21 - dealerSum) > (21 - sum)) {
          receiveMessage(connection_fd, buffer, BUFFER_SIZE);
          sscanf(buffer, "%d", &bet);
          printf("Your sum of cards: %d is closer than dealers cards: %d so you get paid the amount of: %d$\n", sum, dealerSum, bet);
        }
        option = 0;
        break;
      }
    }

    // Goodbye
    sprintf(buffer, "BYE");
    sendMessage(connection_fd, buffer, strlen(buffer));
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);

    for (int i = 0; i < 20; i++) free(userCards[i]);
}
