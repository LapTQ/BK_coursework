/*
 * gcc main.c -fopenmp
 */

#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include "time.h"

int helloworld() {
    //omp_set_num_threads(10);
    #pragma omp parallel
    {
        int threadnumber = omp_get_num_threads();
        int threadID = omp_get_thread_num();
        printf("Hello from thread %d, nthreads %d\n", threadID, threadnumber);
    }
    return 0;
}

int ex1() {
    omp_set_num_threads(10);
    #pragma omp parallel
    {
        int nthreads = omp_get_num_threads();
        int id = omp_get_thread_num();
        printf("Hello %d of %d\n", id, nthreads);
    }
    return 0;
}

int ex2() {
    //shared memory with race condition
    int id, x;
    omp_set_num_threads(100);
    #pragma omp parallel //private(id, x)   // uncomment to correct
    {
        id = omp_get_thread_num();
        x = 10 * id;
        printf("\n");
        printf("hello from thread %d, x = %d", id, x);
        printf("\n");
    };
    return 0;
}

void element_wise_sum(int *A, int *B, int *C, int start, int stop) {

}

#define N 20
int ex3() {
    int *A, *B, *C, i;
    A = (int*) malloc(N * sizeof(int));
    B = (int*) malloc(N * sizeof(int));
    C = (int*) malloc(N * sizeof(int));

    for (i = 0; i < N; i ++) {
        *(A + i) = i;
        *(B + i) = i;
    }


    clock_t t = clock();
    for (i = 0; i < N; i ++) {
        *(C + i) = *(A + i) + *(B + i);
    }
    t = clock() - t;
    double time = ((double) t) / CLOCKS_PER_SEC;
    printf("running time: %f\n", time);

    t = clock();
    #pragma omp parallel
    {
        int nthread = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int start = thread_id * (N / nthread);
        int stop = (thread_id + 1) * (N / nthread);
        for (int i = start; i < stop; i ++) {
            *(C + i) = *(A + i) + *(B + i);
        }
//        for (int i = start; i < stop; i ++) {
//            printf("C[%d] = %d\n", i, *(C + i));
//        }
    };
    t = clock() - t;
    time = ((double) t) / CLOCKS_PER_SEC;
    printf("running time: %f\n", time);
}

int main() {
    ex3();
    return 0;
}