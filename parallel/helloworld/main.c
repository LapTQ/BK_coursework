/*
 * gcc main.c -fopenmp
 */

#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include "time.h"

int helloworldomp() {
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
    }
    return 0;
}

void element_wise_sum(int *A, int *B, int *C, int start, int stop) {
    for (int i = start; i < stop; i ++) {
        *(C + i) = *(A + i) + *(B + i);
    }
}

#define N 10
void ex3() {
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
        element_wise_sum(A, B, C, start, stop);
    }
    t = clock() - t;
    time = ((double) t) / CLOCKS_PER_SEC;
    printf("running time: %f\n", time);
}

#include<math.h>
int sum(int *A, int start, int stop) { // not including A[stop]
    printf("start: %d, end: %d\n", start, stop);
    if (start == stop) {
        return 0;
    }
    else if (start + 1 == stop) {
        return *(A + start);
    }
    else {
        int cum_sum = 0;
        #pragma omp parallel
        {
            int nthreads = omp_get_num_threads();
            int thread_id = omp_get_thread_num();

            int range = ceil((stop - start) / ((float) nthreads));
            for (int _ = 1; _ <= thread_id; _ ++) {
                start += range;
                range = ceil((stop - start - range) / ((float) (nthreads - _)));
            }
            cum_sum += sum(A, start, start + range);
        }
        return cum_sum;
    }
}


void ex4() {
    int *A, i, s;

    A = (int*) malloc(N * sizeof (int));

    for (i = 0; i < N; i ++) {
        *(A + i) = i;
        printf("%d ", *(A + i));
    }
    printf("\n");

    s = sum(A, 0, N);

    printf("%d\n", s);

}


int main(int argc, char *argv[]) {
    ex4();
    return 0;
}
