// openmp: tinh so pi

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<malloc.h>
#define N_STEPS 1000000
#define N_THREADS 4

int main()
{
    double dx = 1.0 / (double) N_STEPS;
    
    omp_set_num_threads(N_THREADS);
    
    /* SOL 1
    double s = 0;
    
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int n_steps_per_block = N_STEPS / N_THREADS;
        int start_step = n_steps_per_block * id, stop_step = n_steps_per_block * (id + 1);
        double sub = 0;
        
        for (int j = start_step; j < stop_step; j ++)
        {
            sub += 1 / (1 + (j * dx) * (j * dx));
        }
        
        #pragma omp critical
        s += 4 * dx * sub;
    }
    */
    
    
    //* SOL 2
    double s = 0;
    
    #pragma omp parallel
    {
        double sub = 0;
        
        #pragma omp for nowait
        for (int i = 0; i < N_STEPS; i ++)
        {
            sub += 1 / (1 + (i * dx) * (i * dx));
        }
        
        #pragma omp critical
        s += 4 * dx * sub;
    }
    
    //*/   
    
    
    printf("%lf\n", s);
}
