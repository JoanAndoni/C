//Daniel Charua - A01017419 - 08/10/18

#define MAX_NUMBERS 20

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include <errno.h>
//Global Variables
int interrupted = 0;

void countInputs();
void setupHandlers();
void catchInterrupt(int signal);

int main(){
  setupHandlers();
  countInputs();
  return 0;
}

void countInputs(){
  int total = 0;
  int number;

  //Variables to poll the standard input
  struct pollfd test_fd;
  int timeout = 1000;
  int poll_result;

  //Configure the polling
  test_fd.fd = 0;
  test_fd.events = POLLIN;

  for (int i = 0; i < MAX_NUMBERS && !interrupted; i++){
    printf("#%2d/%2d. Enter a number: ", i+1, MAX_NUMBERS);
    fflush(stdout);
    while(1){
      poll_result = poll(&test_fd, 1, timeout);
      // The timeput finished without event
      if (poll_result == 0){
        printf(".");
        fflush(stdout);
      }
      //if there is something to read ( user wrote on terminal read it)
      else if (poll_result > 0){
        if (test_fd.revents && POLLIN){
          scanf("%d", &number);
          total += number;
          break;
        }
      }
      //if poll was interrrupted by signal poll_result == -1
      else {
        //if error is interruption break
        if (errno == EINTR){
          break;
        }
      }
    }
  }
  printf("\nThe total is %d\n", total);
}

//Function to set the handler for CNTL C
void setupHandlers(){
  struct sigaction new_action;

  new_action.sa_handler = catchInterrupt;
  sigfillset(&new_action.sa_mask);

  //Define the signal to handle
  sigaction(SIGINT, &new_action, NULL);
}

//Function to act on CNTL C
void catchInterrupt(int signal){
  interrupted = 1;
}
