#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<omp.h>

int main(int argc, char *argv[]) {
    
    int id_process, nr_process;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nr_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_process);
    MPI_Status thongbao;
        
    int *A, *B, *C, i;
    A = (int *) malloc(10 * sizeof (int));
    B = (int *) malloc(10 * sizeof (int));
    C = (int *) malloc(10 * sizeof (int));
    
    if (id_process == 0) {
        
        for (i = 0; i < 10; i ++) *(A + i) = i;
        for (i = 0; i < 10; i ++) *(B + i) = 2 * i;
    }
        
    int Ns = 10/nr_process;
    int *As, *Bs, *Cs, np;
    As = (int *) malloc(Ns * sizeof (int));
    Bs = (int *) malloc(Ns * sizeof (int));
    Cs = (int *) malloc(Ns * sizeof (int));
    
    MPI_Scatter(A, Ns, MPI_INT, As, Ns, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, Ns, MPI_INT, Bs, Ns, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (i = 0; i < Ns; i ++) {
        *(Cs + i) = *(As + i) + *(Bs + i);
    }
    
    MPI_Gather(Cs, Ns, MPI_INT, C, Ns, MPI_INT, 0, MPI_COMM_WORLD);
    if (id_process == 0) {
        for (i = 0; i < 10; i ++) printf("%d ", *(A + i)); printf("\n");
        for (i = 0; i < 10; i ++) printf("%d ", *(B + i)); printf("\n");
        for (i = 0; i < 10; i ++) printf("%d ", *(C + i)); printf("\n");
    }
    
    MPI_Finalize();
    
    return 0;

}

