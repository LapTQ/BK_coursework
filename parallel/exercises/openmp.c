//====================================================
#pragma omp parallel
{
    int id = omp_get_thread_num();
    A[id] = calc(id);
    
    #pragma omp barrier // all threads arrive here before any threads go on.
    B[id] = calc(id, A)
}


//====================================================
total_sum = 0;
#pragma omp parallel
{
    int id = omp_get_thread_num();
    int start = calc_start(id), stop = calc_stop(id);
    int partial_sum = calc_sum(A, start, stop);
    
    #pragma omp critical // must be executed by a single thread at a time
    total_sum += partial_sum;
}

//====================================================
// atomic is like critical, but for x++, x--, ++x, --x only


//====================================================
#pragma omp parallel
#pragma omp for
for (i = 0; i < N; i ++) A[i] = A[i] * 2;


//====================================================
int sum = 0;    // public sum
#pragma omp parallel
{
    #pragma omp for reduction (+:sum)   // public sum = sum<thread 1> + sum<thread 2> + sum<thread 3>
    for (i = 0; i < N; i ++)
        sum = calc_sum(i);  // private sum

}


//====================================================
#pragma omp parallel
{
    int id = omp_get_thread_num();
    A[id] = calc1(id);

    #pragma omp barrier // explicit barrier
    #pragma omp for
    for (i = 0; i < N; i ++)
        C[i] = calc2(i, A);
    // there is an implicit barrier here by default
    
    #pragma omp for nowait  // remove implicit barrier at the end of this loop to reduce overhead
    for (i = 0; i < N; i ++)
        B[i] = calc3(i, C);
    
    A[id] = calc4(id);
}


//====================================================
#pragma omp parallel
{
    do_many_things();
    
    #pragma omp master  // master thread does this before everyone goes on. But NO synchronization implied
    exchange_boundaries();
    
    #pragma omp barrier // need an explicit barrier to ask everyone to wait
    do_other_things();
}


//====================================================
#pragma omp parallel
{
    do_many_things();
    
    #pragma omp single  // any thread, not just master, that gets to it first will do the work. But DO implies synchronization
    exchange_boundaries();
    
    // so no need an explicit barrier here, and can use single nowait
    do_other_things();
}


//====================================================
#pragma omp parallel
{
    #pragma omp sections
    {
        #pragma omp section
        x_calc();
        #pragma omp section
        y_calc();
        #pragma omp section
        z_calc();
    }
}


//====================================================
#pragma omp parallel for
for (j = 0; j < n_bins; j ++) 
{
    omp_init_lock(&locks[j]);
    hist[j] = 0;
}

#pragma omp parallel for
for (i = 0; i < N; i ++) 
{
    j = (int) calc_j(A[i]);
    omp_set_lock(&locks[j]);
    hist[j] ++;
    omp_unset_lock(&locks[j])
}

#pragma omp parallel for
for (j = 0; j < n_bins; j ++) 
    omp_destroy_lock(&locks[j]);
    
    
//====================================================
omp_in_parallel()
omp_set_dynamic()
omp_get_dynamic()
omp_num_procs()


