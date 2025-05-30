#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *nums;
    int count;
} ThreadData;

void *calculate_avg(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int sum = 0;
    for (int i = 0; i < data->count; i++) {
        sum += data->nums[i];
    }
    float *result = malloc(sizeof(float));
    *result = (float)sum / data->count;
    pthread_exit(result);
}

void *calculate_min(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int min = data->nums[0];
    for (int i = 1; i < data->count; i++) {
        if (data->nums[i] < min) {
            min = data->nums[i];
        }
    }
    int *result = malloc(sizeof(int));
    *result = min;
    pthread_exit(result);
}

void *calculate_max(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int max = data->nums[0];
    for (int i = 1; i < data->count; i++) {
        if (data->nums[i] > max) {
            max = data->nums[i];
        }
    }
    int *result = malloc(sizeof(int));
    *result = max;
    pthread_exit(result);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    int count = argc - 1;
    int *nums = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        nums[i] = atoi(argv[i + 1]);
    }

    ThreadData data = {nums, count};
    pthread_t threads[3];
    void *results[3];

    pthread_create(&threads[0], NULL, calculate_avg, &data);
    pthread_create(&threads[1], NULL, calculate_min, &data);
    pthread_create(&threads[2], NULL, calculate_max, &data);

    pthread_join(threads[0], &results[0]);
    pthread_join(threads[1], &results[1]);
    pthread_join(threads[2], &results[2]);

    printf("Avg: %.2f\n", *((float *)results[0]));
    printf("Min: %d\n", *((int *)results[1]));
    printf("Max: %d\n", *((int *)results[2]));

    free(nums);
    free(results[0]);
    free(results[1]);
    free(results[2]);
    return 0;
}