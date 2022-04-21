/*
 * gcc main.c -fopenmp
 */


#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
        {
            int threadnumber = omp_get_num_threads();
            int threadID = omp_get_thread_num();
            printf("%d\n%d", threadID, threadnumber);
        }
        return 0;
}
