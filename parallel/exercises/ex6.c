// mpi: nhan 2 ma tran

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<malloc.h>
#define M 2
#define N 3
#define P 2

void display(int *A, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j ++)
            printf("\t%d", *(A + i*n + j));
        printf("\n");
    }
}

void init(int *A, int m, int n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j ++)
            *(A + i*n + j) = i*n + j;
}

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    
    int n_proc, proc_id;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    int *A, *B, *C;
    
    A = (int*) malloc(M * N * sizeof(int));
    B = (int*) malloc(N * P * sizeof(int));
    C = (int*) malloc(M * P * sizeof(int));
    
    if (proc_id == 0)
    {
        init(A, M, N);
        init(B, N, P);
    }
    
    int m = M/n_proc;
    int *a, *c;
    
    a = (int*) malloc(m * N * sizeof(int));
    c = (int*) malloc(m * P * sizeof(int));
    
    MPI_Scatter(A, m * N, MPI_INT, a, m * N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(B, N * P, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (int i = 0; i < m; i ++)
        for (int k = 0; k < P; k ++)
        {
            int s = 0;
            for (int j = 0; j < N; j ++)
                s += *(a + i * N + j) * *(B + j * P + k);
            *(c + i * P + k) = s;
        }
        
    MPI_Gather(c, m * P, MPI_INT, C, m * P, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (proc_id == 0)
    {
        printf("A =\n");
        display(A, M, N);
        printf("B =\n");
        display(B, N, P);
        printf("C =\n");
        display(C, M, P);
    }
    
    MPI_Finalize();
}
