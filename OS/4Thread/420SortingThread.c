#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10
#define HALF_SIZE SIZE/2

// threads are share resources each other
int left[HALF_SIZE] = {7, 12, 19, 3, 18};
int right[HALF_SIZE] = {4, 2, 6, 15, 8};


void *merge(void *param)
{
    int *array = param;

    int i = 0, j = 0, k = 0;
    while (i < HALF_SIZE && j < HALF_SIZE)
    {
        if (left[i] <= right[j])
        {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < HALF_SIZE)
    {
        array[k] = left[i];
        k++;
        i++;
    }

    while (j < HALF_SIZE)
    {
        array[k] = right[j];
        k++;
        j++;
    }

    pthread_exit(0);
}

void *sort_array(int *param)
{
    int *array = param;
    int tmp;

    for (int i = 0; i < HALF_SIZE-1; i++)
    {
        for (int j = 0; j < HALF_SIZE-1; j++)
        {
            if (array[j] > array[j+1])
            {
                tmp = array[j+1];
                array[j+1] = array[j];
                array[j] = tmp;
            }
        }
    }

    pthread_exit(0);
}

int main()
{
    pthread_t sid1, sid2, meid;

    pthread_create(&sid1, NULL, sort_array, left);
    pthread_create(&sid2, NULL, sort_array, right);

    pthread_join(sid1, NULL);
    pthread_join(sid2, NULL);

    int *array = (int*) malloc(sizeof(int)*SIZE);
    pthread_create(&meid, NULL, merge, array);
    pthread_join(meid, NULL);

    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);


    return 0;
}
