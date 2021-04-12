#include "sum.h"

long long Sum(const struct SumArgs *args)
{
    long long sum = 0;
    for (int i = args->begin; i < args->end; ++i)
    {
        sum += args->array[i];
    }

    return sum;
}

void *ThreadSum(void *args)
{
    struct SumArgs *sum_args = (struct SumArgs *)args;
    return (void *)Sum(sum_args);
}