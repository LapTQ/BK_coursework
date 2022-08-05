// mpi: nhan doi array

/*
mpicc main.c
mpirun -np 4 ./a.out
*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<mpi.h>
#define N 10

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    
    int n_proc, proc_id;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
    MPI_Status thongbao;
    
    if (proc_id == 0)
    {
        int *A, i;
        A = (int*) malloc(N * sizeof(int));
        
        for (i = 0; i < N; i++)
        {
            *(A + i) = i;
            printf("%d\t", *(A + i));
        }
        printf("\n");
        
        MPI_Send(A, N, MPI_INT, 1, 2022, MPI_COMM_WORLD);
    }
    
    else
    {
        int *B, i;
        B = (int*) malloc(N * sizeof(int));
        
        MPI_Recv(B, N, MPI_INT, 0, 2022, MPI_COMM_WORLD, &thongbao);
        
        for (i = 0; i < N; i++)
        {
            *(B + i) = *(B + i) * 2;
            printf("%d\t", *(B + i));
        }
        printf("\n");
    }
    
    MPI_Finalize();
    
}
