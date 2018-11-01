/*
  Modify by: Joan Andoni González Rioz A00569929

    Program for a simple bank server
    It uses sockets and threads
    The server will process simple transactions on a limited number of accounts

    Gilberto Echeverria
    gilecheverria@yahoo.com
    29/03/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// Signals library
#include <errno.h>
#include <signal.h>
// Sockets libraries
#include <netdb.h>
#include <sys/poll.h>
// Posix threads library
#include <pthread.h>

// Custom libraries
#include "bank_codes.h"
#include "sockets.h"
#include "fatal_error.h"

#define NUM_ACCOUNTS 4
#define BUFFER_SIZE 1024
#define MAX_QUEUE 5

//  GLOBAL VARIABLES
int interrupted = 0;

///// Structure definitions

// Data for a single bank account
typedef struct account_struct {
    int id;
    float balance;
} account_t;

// Data for the bank operations
typedef struct bank_struct {
    // Store the total number of operations performed
    int total_transactions;
    // An array of the accounts
    account_t * account_array;
} bank_t;

// Structure for the mutexes to keep the data consistent
typedef struct locks_struct {
    // Mutex for the number of transactions variable
    pthread_mutex_t transactions_mutex;
    // Mutex array for the operations on the accounts
    pthread_mutex_t * account_mutex;
} locks_t;

// Data that will be sent to each structure
typedef struct data_struct {
    // The file descriptor for the socket
    int connection_fd;
    // A pointer to a bank data structure
    bank_t * bank_data;
    // A pointer to a locks structure
    locks_t * data_locks;
} thread_data_t;



///// FUNCTION DECLARATIONS
void usage(char * program);
void setupHandlers();
void initBank(bank_t * bank_data, locks_t * data_locks);
void waitForConnections(int server_fd, bank_t * bank_data, locks_t * data_locks);
void * attentionThread(void * arg);
int checkValidAccount(int account);
void closeBank(bank_t * bank_data, locks_t * data_locks);
/*
    EXAM: Add your function declarations here
*/
void catchInterrupt(int signal);

///// MAIN FUNCTION
int main(int argc, char * argv[])
{
  int server_fd;
  bank_t bank_data;
  locks_t data_locks;

  printf("\n=== SIMPLE BANK SERVER ===\n");

  // Check the correct arguments
  if (argc != 2) {
    usage(argv[0]);
  }

  // Configure the handler to catch SIGINT
  setupHandlers();

  // Initialize the data structures
  initBank(&bank_data, &data_locks);

  // Show the IPs assigned to this computer
  printLocalIPs();

  // Start the server
  server_fd = initServer(argv[1], MAX_QUEUE);

  // Listen for connections from the clients
  waitForConnections(server_fd, &bank_data, &data_locks);

  // Close the socket
  close(server_fd);

  // Clean the memory used
  closeBank(&bank_data, &data_locks);

  // Finish the main thread
  pthread_exit(NULL);

  return 0;
}

///// FUNCTION DEFINITIONS

/*
    Explanation to the user of the parameters required to run the program
*/
void usage(char * program) {
  printf("Usage:\n");
  printf("\t%s {port_number}\n", program);
  exit(EXIT_FAILURE);
}

/*
    Modify the signal handlers for specific events
*/
void setupHandlers() {
  struct sigaction new_action;

  new_action.sa_handler = catchInterrupt;
  sigfillset(&new_action.sa_mask);

  sigaction(SIGINT, &new_action, NULL);
}

/*
    Function to initialize all the information necessary
    This will allocate memory for the accounts, and for the mutexes
*/
void initBank(bank_t * bank_data, locks_t * data_locks) {
  // Set the number of transactions
  bank_data->total_transactions = 0;

  // Allocate the arrays in the structures
  bank_data->account_array = malloc(NUM_ACCOUNTS * sizeof (account_t));
  // Allocate the arrays for the mutexes
  data_locks->account_mutex = malloc(NUM_ACCOUNTS * sizeof (pthread_mutex_t));

  // Initialize the mutexes, using a different method for dynamically created ones
  //data_locks->transactions_mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_init(&data_locks->transactions_mutex, NULL);
  for (int i=0; i<NUM_ACCOUNTS; i++) {
    //data_locks->account_mutex[i] = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&data_locks->account_mutex[i], NULL);
  }
}

/*
    Main loop to wait for incomming connections
*/
void waitForConnections(int server_fd, bank_t * bank_data, locks_t * data_locks) {
  struct sockaddr_in client_address;
  socklen_t client_address_size;
  char client_presentation[INET_ADDRSTRLEN];
  int client_fd;
  pthread_t new_tid;
  thread_data_t * connection_data = NULL;
  int poll_response;
	int timeout = 500;		// Time in milliseconds (0.5 seconds)

  // Get the size of the structure to store client information
  client_address_size = sizeof client_address;

  while (!interrupted) {
	//// POLL

    // Create a structure array to hold the file descriptors to poll
    struct pollfd test_fds[1];

    // Fill in the structure
    test_fds[0].fd = server_fd;
    test_fds[0].events = POLLIN;  // Check for incomming data

    // Check if there is any incomming communication
    poll_response = poll(test_fds, 1, timeout);

		// Error when polling
    if (poll_response == -1)  {
      // Test if the error was caused by an interruption
      if (errno == EINTR) {
        printf("Poll did not finish. The program was interrupted");
      } else  {
        fatalError("ERROR: poll");
      }
    }
    // Timeout finished without reading anything
    else if (poll_response == 0)
    {
      //printf("No response after %d seconds\n", timeout);
    }
		// There is something ready at the socket
    else {
      // Check the type of event detected
      if (test_fds[0].revents & POLLIN) {
        // ACCEPT

        // Wait for a client connection
				client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_address_size);
				if (client_fd == -1) {
					fatalError("ERROR: accept");
				}

				// Get the data from the client
				inet_ntop(client_address.sin_family, &client_address.sin_addr, client_presentation, sizeof client_presentation);
				printf("Received incomming connection from %s on port %d\n", client_presentation, client_address.sin_port);

				// Prepare the structure to send to the thread
        connection_data = malloc(sizeof(thread_data_t)); // Sizeof the structure thread_data_t
        connection_data->connection_fd = client_fd;
        connection_data->bank_data = bank_data;
        connection_data->data_locks = data_locks;

				// CREATE A THREAD
        /*
        The first argument is a pointer to thread_id which is set by this function.
        The second argument specifies attributes. If the value is NULL, then default attributes shall be used.
        The third argument is name of function to be executed for the thread to be created.
        The fourth argument is used to pass arguments to the function, attentionThread.
        */
        pthread_create(&new_tid, NULL, attentionThread, (void*)connection_data);
      }
    }
  }

  // Print the total number of transactions performed
  printf("The server already stopped and it made this number of transactions: %d\n", bank_data->total_transactions);

  //Free the allocated memory for the connection_data
  free(connection_data);
}

/*
    Hear the request from the client and send an answer
*/
void * attentionThread(void * arg) {
    // Receive the data for the bank, mutexes and socket file descriptor
    thread_data_t * connection_data = (thread_data_t*)arg;
    //operation_t operation = CHECK; Doesnt let it be the enum cause it reads an int
    int operation;
    response_t response = OK;
    int account = 0;
    float ammount = 0;

    char buffer[BUFFER_SIZE];

    // Loop to listen for messages from the client
    while (!interrupted && operation != EXIT) {
      // Receive the request
      if (!recvString(connection_data->connection_fd, buffer, BUFFER_SIZE)){
        perror("Message recive");
        exit(EXIT_FAILURE);
      }

      // Process the request being careful of data consistency
      sscanf(buffer, "%d %d %f", &operation, &account, &ammount);
      printf("Operation: %d | Account: %d | Ammount: %f\n", operation, account, ammount);

      // Check if you recive the EXIT option
      if (operation == EXIT){
        // Set the response
        response = BYE;
        // Set the string to finish the processes of the client
        sprintf(buffer, "%d %f", response, 0.0);
        // Send the response
        sendString(connection_data->connection_fd, buffer);
        // Break the cicle
        break;
      }

      // Check if the account is valid
      if(!checkValidAccount(account)){
        // Set the response
        response = NO_ACCOUNT;
        // Set the string to finish the processes of the client
        sprintf(buffer, "%d %f", response, 0.0);
        // Send the response
        sendString(connection_data->connection_fd, buffer);
        // Break the cicle
        break;
      }

      // Block the account operations for the different threads cause we will move
      // a global variable that is the global transactions of the bank.
      pthread_mutex_lock(&connection_data->data_locks->account_mutex[account]);

      // Check if is an operation and make it
      switch (operation) {
        case CHECK:
        // Set the response
        response = OK;
        // Set the string with the balance of the account that is in the array
        // of the accounts that is saved in the bank_data
        sprintf(buffer, "%d %f", response, connection_data->bank_data->account_array[account].balance);
        break;

        case DEPOSIT:
        // Add the money to deposit in the account stored in the array of the bank_data
        connection_data->bank_data->account_array[account].balance += ammount;
        // Set the response
        response = OK;
        // Set the string with the final balance of the account after the DEPOSIT
        // that is in the array of the accounts that is saved in the bank_data
        sprintf(buffer, "%d %f", response, connection_data->bank_data->account_array[account].balance);
        break;

        case WITHDRAW:
        // Check if the ammount to withdraw is smaller than the balance of the account
        if(connection_data->bank_data->account_array[account].balance > ammount){
          // Take the ammount of money from the balance of the account
          connection_data->bank_data->account_array[account].balance -= ammount;
          // Set the response
          response = OK;
          // Set the string with the final balance of the account after the WITHDRAW
          // that is in the array of the accounts that is saved in the bank_data
          sprintf(buffer, "%d %f", response, connection_data->bank_data->account_array[account].balance);
        // If the ammount to withdraw is bigger than the balance of the account
        } else {
          // Set the response INSUFFICIENT cause the ammount to WITHDRAW is smaller
          response = INSUFFICIENT;
          // Set the string with the balance of the account that is in the array
          // of the accounts that is saved in the bank_data
          sprintf(buffer, "%d %f", response, connection_data->bank_data->account_array[account].balance);
        }
        break;

        default:
        // Set the response ERROR cause there are no option defined
        response = ERROR;
        // Set the string to finish the processes of the client
        sprintf(buffer, "%d %f", response, 0.0);
        break;
      }

      // Update the number of transactions
      if (response == OK) {
        // Add a transaction in case there was a movement succesfull
        connection_data->bank_data->total_transactions += 1;
      }

      // Send a reply
      sendString(connection_data->connection_fd, buffer);

      // Unlock the mutex of the account in use
      pthread_mutex_unlock(&connection_data->data_locks->account_mutex[account]);
    }

    pthread_exit(NULL);
}

/*
    Free all the memory used for the bank data
*/
void closeBank(bank_t * bank_data, locks_t * data_locks) {
  printf("DEBUG: Clearing the memory for the thread\n");
  free(bank_data->account_array);
  free(data_locks->account_mutex);
}

/*
    Return true if the account provided is within the valid range,
    return false otherwise
*/
int checkValidAccount(int account) {
  return (account >= 0 && account < NUM_ACCOUNTS);
}

// Function on [ Ctrl + C ]
void catchInterrupt(int signal){
  // Change the global variable that will made the interruption
  interrupted = 1;
}
