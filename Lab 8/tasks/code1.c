#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 0;

void *runner(void *parameters){
       int i, upper = *((int *)parameters);
       if (upper > 0){
            for (i = 1; i<= upper; i++)
                   sum = sum + i;
       }
       pthread_exit(0);
}

int main(int argc, char *argv[]){
       pthread_t threadID;
       pthread_attr_t attributes;
       int num = 10;

       if (argc > 1){
            num = atoi(argv[1]);
        }
       
       pthread_attr_init(&attributes);
       pthread_create(&threadID, &attributes, runner, &num);
       pthread_join(threadID, NULL);
       printf("sum=%d\n" , sum);
       exit(0);
}

