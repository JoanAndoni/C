/*
    Joan Andoni González Rioz A00569929
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

// Include libraries for sockets
#include <netdb.h>
#include <arpa/inet.h>

// My sockets library
#include "sockets.h"

#define SERVICE_PORT 8642
#define MAX_QUEUE 5
#define BUFFER_SIZE 1023

void usage(char * program);
void waitForConnections(int server_fd);
void communicationLoop(int connection_fd);

int main(int argc, char * argv[])
{
    int server_fd;

    printf("\n=== DEALER PROGRAM ===\n");

    if (argc != 2)
        usage(argv[0]);

    server_fd = startServer(argv[1]);

    printf("Server ready and waiting!\n");
    // Stand by to receive connections from the clients
    waitForConnections(server_fd);

    printf("Closing the server socket\n");
    // Close the socket
    close(server_fd);

    return 0;
}

// Show the user how to run this program
void usage(char * program)
{
    printf("Usage:\n%s {port_number}\n", program);
    exit(EXIT_FAILURE);
}



// Stand by for connections by the clients
void waitForConnections(int server_fd)
{
    struct sockaddr_in client_address;
    socklen_t client_address_size;
    char client_presentation[INET_ADDRSTRLEN];
    int connection_fd;
    pid_t pid;

    // Loop to wait for client connections
    while (1)
    {
        ///// ACCEPT
        // Receive incomming connections
        // Get the size of the structure where the address of the client will be stored
        client_address_size = sizeof client_address;
        connection_fd = accept(server_fd, (struct sockaddr *) &client_address, &client_address_size);
        if (connection_fd == -1)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Identify the client
        // Get the ip address from the structure filled by accept
        inet_ntop(client_address.sin_family, &client_address.sin_addr, client_presentation, sizeof client_presentation);
        printf("Received connection from '%s' on port '%d'\n", client_presentation, client_address.sin_port);

        pid = fork();
        // Parent process
        if (pid > 0)
        {
            close(connection_fd);
        }
        // Child process
        else if (pid == 0)
        {
            close(server_fd);
            // Establish the communication
            communicationLoop(connection_fd);
            exit(EXIT_SUCCESS);
        }
        // Fork error
        else
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

    }
}

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

// Do the actual receiving and sending of data
void communicationLoop(int connection_fd)
{
    char buffer[BUFFER_SIZE];
    //int message_counter = 0;

    srand(time(NULL));   // initial the random once

    char *cards[13] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    char *dealer[2];

    int r, bet, secondBet, option = 1, userSum, decition, dealerSum;

    // Handshake
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sprintf(buffer, "RANGE");
    sendMessage(connection_fd, buffer, strlen(buffer));

    // Receive the first bet of the user
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sscanf(buffer, "%d", &bet);
    printf("The fist bet of the user is: %d\n", bet);

    // Start the game by generating two random cards for the user
    r = rand() % 13;
    printf("First user card generated is: %s\n", cards[r]);
    sprintf(buffer, "%s", cards[r]);
    sendMessage(connection_fd, buffer, strlen(buffer));
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);

    r = rand() % 13;
    printf("Second user card generated is: %s\n", cards[r]);
    sprintf(buffer, "%s", cards[r]);
    sendMessage(connection_fd, buffer, strlen(buffer));
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);

    // Generate and send the card of the dealer
    r = rand() % 13;
    printf("Dealers first card generated is: %s\n", cards[r]);
    dealer[0] = cards[r];
    sprintf(buffer, "%s", cards[r]);
    sendMessage(connection_fd, buffer, strlen(buffer));

    // Recive the sum of the user cards
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sscanf(buffer, "%d", &userSum);

    // Condition if the user made a BlackJack and he gets paid 1.5 his first bet
    if( userSum == 21) {
      printf("The player made a BlackJack\n");
      bet = bet + bet * 1.5;
      printf("He gets paid the amount of: %d\n", bet);
      sprintf(buffer, "%d", bet);
      sendMessage(connection_fd, buffer, strlen(buffer));
      exit(0);
    }

    // Create the second card of the dealers
    r = rand() % 13;
    printf("Dealers second card generated is: %s\n", cards[r]);
    dealer[1] = cards[r];

    dealerSum = sumCards(dealer);

    // Send a message to ask what he does the user wants to do
    sprintf(buffer, "DECITION");
    sendMessage(connection_fd, buffer, strlen(buffer));

    //Receiving the decition to check if he wants to raise the bet 1
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sscanf(buffer, "%d", &decition);
    if ( decition == 1 ) {
      printf("The player wants raise the bet\n");
      sprintf(buffer, "AMOUNT");
      //1.1
      sendMessage(connection_fd, buffer, strlen(buffer));
      //1.2
      receiveMessage(connection_fd, buffer, BUFFER_SIZE);
      sscanf(buffer, "%d", &secondBet);
      bet = bet + secondBet;
    } else {
      printf("The player wants to stay with the opening bet\n");
    }

    // Send a message to ask what does the user wants to do 2
    sprintf(buffer, "OPTION");
    sendMessage(connection_fd, buffer, strlen(buffer));

    while (option != 0)
    {
        receiveMessage(connection_fd, buffer, BUFFER_SIZE); // 3
        sscanf(buffer, "%d", &option);

        if ( option == 1 ) {
          printf("The player wants to get another card\n");

          // Create another card for the user
          r = rand() % 13;
          printf("The other user card generated is: %s\n", cards[r]);
          sprintf(buffer, "%s", cards[r]);
          sendMessage(connection_fd, buffer, strlen(buffer));

          // Recive the sum of the user cards
          receiveMessage(connection_fd, buffer, BUFFER_SIZE);
          sscanf(buffer, "%d", &userSum);

          if (userSum > 21){
            printf("The user sum passes the 21 so he losses the amount of his first bet: %d\n", bet);
            sprintf(buffer, "%d", bet);
            sendMessage(connection_fd, buffer, strlen(buffer));
            option = 0;
          } else {
            sprintf(buffer, "CONTINUE");
            sendMessage(connection_fd, buffer, strlen(buffer));
          }
        } else if (option == 2){
          printf("The player wants to stay\n");
          sprintf(buffer, "%d", dealerSum);
          sendMessage(connection_fd, buffer, strlen(buffer));
          receiveMessage(connection_fd, buffer, BUFFER_SIZE);
          if (userSum == dealerSum) {
            printf("The user has the same sum of cards as the dealer, he gets back his bet: %d$\n", bet);
            sprintf(buffer, "%d", bet);
            sendMessage(connection_fd, buffer, strlen(buffer));
          } else if ((21 - dealerSum) < (21 - userSum)) {
            printf("The user sum of cards is farther than dealers sum of cards so he losses the amount of his bet: %d$\n", bet);
            sprintf(buffer, "%d", bet);
            sendMessage(connection_fd, buffer, strlen(buffer));
          } else if ((21 - dealerSum) > (21 - userSum)) {
            bet = bet + bet;
            printf("The user sum of cards is closer than dealers sum of cards so he gets paid the amount of: %d$\n", bet);
            sprintf(buffer, "%d", bet);
            sendMessage(connection_fd, buffer, strlen(buffer));
          }
          option = 0;
        }
    }

    // Goodbye
    receiveMessage(connection_fd, buffer, BUFFER_SIZE);
    sprintf(buffer, "BYE");
    sendMessage(connection_fd, buffer, strlen(buffer));
}
