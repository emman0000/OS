#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10000000
#define NUM_THREADS 10

typedef struct{
     float *A, *B, *C;
     int start, end;
} ThreadArgs;

void *add_arrays(void *arg){
     ThreadArgs *args = (ThreadArgs*)arg;
     for(int i=args->start; i <args->end; i++){
           args->C[i] = args->A[i] + args->B[i];
     }
     pthread_exit(NULL);
}

int main(){
    float *A = malloc(SIZE * sizeof(float));
    float *B = malloc(SIZE * sizeof(float));
    float *C = malloc(SIZE * sizeof(float));

    srand(time(NULL));
    for( int i=0; i< SIZE; i++){
        A[i] = (float)rand()/ RAND_MAX;
        B[i] = (float)rand()/ RAND_MAX;
    }
    
    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];
    int chunk_size = SIZE / NUM_THREADS;
    
    clock_t start = clock();
    for(int i=0; i<NUM_THREADS; i++){
       args[i].A = A; 
       args[i].B = B;
       args[i].C = C;
       args[i].start = i*chunk_size;
       args[i].end = (i== NUM_THREADS - 1)? SIZE: (i+1)*chunk_size;
       pthread_create(&threads[i], NULL, add_arrays, &args[i]);
    } 
    for(int i=0; i<NUM_THREADS; i++){
       pthread_join(threads[i], NULL);
    } 
    clock_t end = clock();

    printf("Parallel execution time: %.2f ms\n", (double)(end - start)*1000/CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(C);
    return 0;
}
