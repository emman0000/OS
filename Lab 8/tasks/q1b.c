#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10000000

int main() {
    float *A = malloc(SIZE * sizeof(float));
    float *B = malloc(SIZE * sizeof(float));
    float *C = malloc(SIZE * sizeof(float));

    srand(time(NULL));  // Fixed: Changed scanf to srand for random seed initialization
    for(int i = 0; i < SIZE; i++) {
        A[i] = (float)rand() / RAND_MAX;
        B[i] = (float)rand() / RAND_MAX;
    }

    clock_t start = clock();
    for(int i = 0; i < SIZE; i++) {
        C[i] = A[i] * B[i];
    }
    clock_t end = clock();

    // Fixed the time calculation (removed extra 0 in 10000)
    printf("Serial execution time: %.2f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(C);
    return 0;
}
