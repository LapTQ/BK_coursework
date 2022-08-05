// tinh tong mang n phan tu

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<malloc.h>
#define N 16
#define N_THREADS 4


int sum(int *A, int start, int stop)
{
    if (start + 1 == stop) {
       return *(A + start);
    }
    
    int mid = (start + stop) / 2;
    return sum(A, start, mid) + sum(A, mid, stop);
    
}


int main() 
{
    int *A, i;
    A = (int *) malloc(N * sizeof(int));
    
    for (i = 0; i < N; i ++) 
        *(A + i) = i;    
    
    omp_set_num_threads(N_THREADS);

    //* SOL 1
    int s = 0;
    #pragma omp parallel
    {
        int n_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int size = N / n_threads;
        
        int start = size * thread_id, stop = size * (thread_id + 1);
        int sub = 0;
        
        for (int j = start; j < stop; j ++)
            sub += *(A + j);

        #pragma omp critical    // must be executed by a single thread at a time
        s += sub;
   
    }
    //*/
    
    /* SOL 2
    int s = 0;
    #pragma omp parallel
    {
        int sub = 0;
        #pragma omp for nowait
        for (i = 0; i < N; i ++) 
            sub += *(A + i);
        
        #pragma omp critical
        s += sub;
    }
    */

    //s = sum(A, 0, N);
    printf("s = %d\n", s);
    
    
}
