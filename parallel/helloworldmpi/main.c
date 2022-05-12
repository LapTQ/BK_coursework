/*
mpicc main.c
mpirun -np 4 ./a.out
*/

#include <mpi.h>
#include <stdio.h>
void main(int argc, char *argv[]) {
    int ID_Process, Nr_Process;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &Nr_Process);
    MPI_Comm_rank(MPI_COMM_WORLD, &ID_Process);
    printf("Total process: %d, ", Nr_Process);
    printf("process: %d\n", ID_Process);
    MPI_Finalize();
}
