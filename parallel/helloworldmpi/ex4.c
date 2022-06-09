#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include<mpi.h>
#include<omp.h>
#define m 2
#define n 3
#define p 3
//=========================
void DisplayMatrix(int *A, int row,  int col){
    int i,j;
    for(i=0;i<row;i++){
        for(j=0;j<col;j++) printf("  %d",*(A+i*col+j));
        printf("\n");
    }
}
//=========================
int main(int argc, char *argv[])
{

    int id_process, nr_process;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nr_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_process);
    MPI_Status thongbao;

    int i, j, k;
    int tmp, sum = 0.0;

    int *A, *B, *C;
    A = (int *) malloc ((m*n)*sizeof(int));
    B = (int *) malloc ((n*p)*sizeof(int));
    C = (int *) malloc ((m*p)*sizeof(int));

    for (  i = 0 ; i < m ; i++ )
        for ( j = 0 ; j < n ; j++ ){
            *(A+i*n+j) = i*n+j;
        }

  // Nhap Ma tran B
    for (  i = 0 ; i < n ; i++ )
        for ( j = 0 ; j < p ; j++ ){
            *(B+i*p+j) = i*p+j;
        }
    
    int *As, *Bs, *Cs;
    As = (int *) malloc(n * sizeof (int));
    Bs = (int *) malloc(n * p * sizeof (int));
    Cs = (int *) malloc(p * sizeof (int));
    
    MPI_Scatter(A, n, MPI_INT, As, n, MPI_INT, 0, MPI_COMM_WORLD);
    for ( k = 0 ; k < p ; k++ )
    {
        sum = 0;
            for ( j = 0 ; j < n ; j++ )
            {
                sum = sum + *(As + j) * *(B + j*p + k);
            }
            *(Cs + k) = sum;
    }
    
    MPI_Gather(Cs, p, MPI_INT, C, p, MPI_INT, 0, MPI_COMM_WORLD);

    if (id_process == 0) {
      printf("The Matrix A:\n");      
      DisplayMatrix(A, m, n);

      printf("The Matrix B:\n");
      DisplayMatrix(B, n, p);
      
      printf("The Matrix C:\n");
      DisplayMatrix(C, m, p);    
    }
    
    MPI_Finalize();

  //
    return 0;
}

