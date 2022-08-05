// mpi: tong 2 array A, B. Luu ket qua vao C

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<mpi.h>
#define N 8

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    
    int n_proc, proc_id;
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
    MPI_Status thongbao;
    
    int *A, *B, *C, i;
    A = (int*) malloc(N * sizeof(int));
    B = (int*) malloc(N * sizeof(int));
    C = (int*) malloc(N * sizeof(int));
    
    if (proc_id == 0)
    {
        for (i = 0; i < N; i ++)
        {
            *(A + i) = i;
            *(B + i) = i * 2;
            
            printf("%d + %d\t", *(A + i), *(B + i));
         }
         printf("\n");
    }
    
    int n = N/n_proc;
    int *a, *b, *c;
    a = (int*) malloc(n * sizeof(int));
    b = (int*) malloc(n * sizeof(int));
    c = (int*) malloc(n * sizeof(int));
    
    //* SOL 1
    if (proc_id == 0)
        for (int r = 0; r < n_proc; r ++)
        {
            MPI_Send(A + r * n, n, MPI_INT, r, 20220, MPI_COMM_WORLD);
            MPI_Send(B + r * n, n, MPI_INT, r, 20221, MPI_COMM_WORLD);
        }
    
    MPI_Recv(a, n, MPI_INT, 0, 20220, MPI_COMM_WORLD, &thongbao);
    MPI_Recv(b, n, MPI_INT, 0, 20221, MPI_COMM_WORLD, &thongbao);
    
    for (i = 0; i < n; i ++)
        *(c + i) = *(a + i) + *(b + i);
    
    MPI_Send(c, n, MPI_INT, 0, 20222 + proc_id, MPI_COMM_WORLD);
    
    if (proc_id == 0)
        for (int r = 0; r < n_proc; r ++)
            MPI_Recv(C + r * n, n, MPI_INT, r, 20222 + r, MPI_COMM_WORLD, &thongbao);
    //*/
    
    /* SOL 2
    MPI_Scatter(A, n, MPI_INT, a, n, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, n, MPI_INT, b, n, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (i = 0; i < n; i ++)
        *(c + i) = *(a + i) + *(b + i);
    
    MPI_Gather(c, n, MPI_INT, C, n, MPI_INT, 0, MPI_COMM_WORLD);
    
    */
    
    if (proc_id == 0)
        for (i = 0; i < N; i ++)
            printf("%d\t", *(C + i));
        
    MPI_Finalize();
}

