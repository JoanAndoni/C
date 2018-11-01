#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Let us create a global variable to change it in threads
int g = 0;

// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
	// Store the value argument passed to this thread
	int *myid = (int *)vargp;

	// Let us create a static variable to observe its changes
	static int s = 0;

	// Change static and global variables
	++s; ++g;

	// Print the argument, static and global variables
	printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}

int main()
{
	int i;
	pthread_t tid;

	// Let us create three threads
	for (i = 0; i < 3; i++)
    /*
    The first argument is a pointer to thread_id which is set by this function.
    The second argument specifies attributes. If the value is NULL, then default attributes shall be used.
    The third argument is name of function to be executed for the thread to be created.
    The fourth argument is used to pass arguments to the function, myThreadFun.
    */
    pthread_create(&tid, NULL, myThreadFun, (void *)&tid);

	pthread_exit(NULL);
	return 0;
}
