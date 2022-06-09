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
    
    if (id_process == 0) {
        for (i = 0; i < Ns; i ++) *(As + i) = *(A + i);
        for (i = 0; i < Ns; i ++) *(Bs + i) = *(B + i);
        for (np = 1; np < nr_process; np ++) {
            MPI_Send(A + np*Ns, Ns, MPI_INT, np, 10000 + np, MPI_COMM_WORLD);
            MPI_Send(B + np*Ns, Ns, MPI_INT, np, 20000 + np, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(As, Ns, MPI_INT, 0, 10000 + id_process, MPI_COMM_WORLD, &thongbao);
        MPI_Recv(Bs, Ns, MPI_INT, 0, 20000 + id_process, MPI_COMM_WORLD, &thongbao);
    }
    
    for (i = 0; i < Ns; i ++) {
        *(Cs + i) = *(As + i) + *(Bs + i);
    }
    
    if (id_process != 0) {
        MPI_Send(Cs, Ns, MPI_INT, 0, 30000 + id_process, MPI_COMM_WORLD);
    }
    else {
        for (i = 0; i < Ns; i ++) *(C + i) = *(Cs + i);
        for (np = 1; np < nr_process; np ++) {
            MPI_Recv(C + np * Ns, Ns, MPI_INT, np, 30000 + np, MPI_COMM_WORLD, &thongbao);
        }
    }
    
    if (id_process == 0) {
        for (i = 0; i < 10; i ++) printf("%d ", *(A + i)); printf("\n");
        for (i = 0; i < 10; i ++) printf("%d ", *(B + i)); printf("\n");
        for (i = 0; i < 10; i ++) printf("%d ", *(C + i)); printf("\n");
    }
    
    MPI_Finalize();
    
    return 0;

}

