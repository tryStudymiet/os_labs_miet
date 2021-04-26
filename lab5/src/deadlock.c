#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER,
                mtx2 = PTHREAD_MUTEX_INITIALIZER;

int global_var = 1;

void work1(void *arg)
{
    pthread_mutex_lock(&mtx1);
    sleep(1);
    pthread_mutex_lock(&mtx2);
    for (int i = 0; i < 100; ++i)
    {
        global_var *= 2;
        printf("%d_", global_var);
    }
    sleep(3);
    pthread_mutex_unlock(&mtx2);
    pthread_mutex_unlock(&mtx1);
}

void work2(void *arg)
{
    pthread_mutex_lock(&mtx2);
    sleep(1);
    pthread_mutex_lock(&mtx1);
    for (int i = 0; i < 100; ++i)
    {
        global_var *= 3;
        printf("%d_", global_var);
    }
    sleep(3);
    pthread_mutex_unlock(&mtx1);
    pthread_mutex_unlock(&mtx2);
}

int main()
{
    pthread_t thr1, thr2;
    void *some;

    if (pthread_create(&thr1, NULL, (void *)work1, some))
    {
        perror("pthread create");
        exit(1);
    }

    if (pthread_create(&thr2, NULL, (void *)work2, some))
    {
        perror("pthread create");
        exit(1);
    }

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    printf("\n");
    return 0;
}