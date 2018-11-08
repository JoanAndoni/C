#include <stdio.h>
#include <omp.h>

int main()
{
    int tid;
    int num_threads;

    #pragma omp parallel
    {
        tid = omp_get_thread_num();
        printf("Thread %d\n", tid);

        #pragma omp master
        {
            num_threads = omp_get_num_threads();
            printf("There are %d threads\n", num_threads);
        }
    }

    return 0;
}
