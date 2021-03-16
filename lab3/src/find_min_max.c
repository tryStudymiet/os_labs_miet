#include "find_min_max.h"

#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {
    struct MinMax min_max;
    min_max.min = INT_MAX;
    min_max.max = INT_MIN;
    unsigned int i;
    for(i = begin; i < end; ++i){
        int item = array[i];
        if(item > min_max.max)
            min_max.max = item; 
        if(item < min_max.min)
            min_max.min = item;
    }
    return min_max;
}
