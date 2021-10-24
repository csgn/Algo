#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M   4
#define N   4
#define K   3
#define NUM_THREADS M*N

struct POINT { int x, y; };

static int A[M][K] = 
{
    {  2,   8,  -3   },
    { -9,  -3,  190  },
    { 50,  -2,  -190 },
    { 25, -25,  650  }
};

static int B[K][N] = 
{ 
    { 8,  7,  6, -3 },
    { 0, -1, 19, 27 },
    { 5,  4,  3, -1 }
};

static int C[M][N];

static void *multiplication(void *param)
{
    int sum = 0;
    struct POINT *point = param;

    for (int i = 0; i < K; i++)
        sum += A[point->x][i] * B[i][point->y];

    C[point->x][point->y] = sum;

    free(point);
    pthread_exit(0);
}

int main()
{
    int worker_index = 0;
    pthread_t workers[NUM_THREADS];

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            struct POINT *point = (struct POINT*) malloc(sizeof(struct POINT));
            point->x = i;
            point->y = j;

            pthread_create(&workers[worker_index++], NULL, multiplication, point);
        }
    }

    // wait all workers
    for (int ti = 0; ti < NUM_THREADS; ti++)
        pthread_join(workers[ti], NULL);

    // print result
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d\t", C[i][j]);
        printf("\n");
    }

    return 0;
}
