#include <stdio.h>
#include <pthread.h>



int isprime(int num)
{
    int i;
    for (i = 2; i <= num/2; i++) {
        if (num % i == 0) 
            return 0;
    }

    return 1;
}

void *checkprime(void *param)
{
    int i, num = param;

    for (i = 2; i <= num; i++) {
        if (isprime(i))
            printf("%d ", i);
    }

    pthread_exit(0);
}

int main(int argc, char **argv) 
{
    pthread_t tid;

    pthread_create(&tid, NULL, checkprime, 100000);
    pthread_join(tid, NULL);

    return 0;
}
