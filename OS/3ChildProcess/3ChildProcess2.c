#include <pthread.h>
#include <stdio.h>

int value = 0;
void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
    int pid;
    pthread_t tid, tid2;
    pthread_attr_t attr;
    pid = fork();

    if (pid == 0) { /* child process */
        int pid2 = fork();
        if (pid2 == 0) {
            pthread_create(&tid2, NULL, runner, 2);
            pthread_join(tid2, NULL);
            printf("PROCESS 2: value = %d\n",value); /* LINE C */
        } else if (pid2 > 0) {
            wait(NULL);
            printf("PARENT PROCESS 1: value = %d\n",value); /* LINE C */
        }

        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,runner,NULL);
        pthread_join(tid,NULL);
        printf("CHILD PROCESS 1: value = %d\n", 1); /* LINE C */
    }
    else if (pid > 0) { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d\n",value); /* LINE P */
    }
}

void *runner(void *param) {
    int p = (int) param;
    value = p;
    pthread_exit(0);
}
