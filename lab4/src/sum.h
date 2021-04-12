#ifndef THREAD_SUM_H
#define THREAD_SUM_H

struct SumArgs
{
    int *array;
    int begin;
    int end;
};

long long Sum(const struct SumArgs *args);
void *ThreadSum(void *args);

#endif