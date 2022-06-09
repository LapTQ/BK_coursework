#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[]) {
    
    int id_process, nr_process;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nr_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_process);
    
    MPI_Status thongbao;
    if (id_process == 0) {
        int *A, i;
        A = (int *) malloc(10 * sizeof (int));
        for (i = 0; i < 10; i ++) *(A + i) = i;
        
        MPI_Send(A, 10, MPI_INT, 1, 2022, MPI_COMM_WORLD);
        printf("A at rank 0: ");
        for (i = 0; i < 10; i ++) printf("%d ", *(A + i)); printf("\n");
    }
    else {
        int *B, *C, i;
        B = (int *) malloc(10 * sizeof (int));
        C = (int *) malloc(10 * sizeof (int));
        
        MPI_Recv(B, 10, MPI_INT, 0, 2022, MPI_COMM_WORLD, &thongbao);

        for (i = 0; i < 10; i ++) *(C + i) = 2 * *(B + i);
        printf("C at rank 1: ");
        for (i = 0; i < 10; i ++) printf("%d ", *(C + i)); printf("\n");
    }
    
    MPI_Finalize();
    
    return 0;

}
