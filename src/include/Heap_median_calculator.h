#ifndef __HEAP_MEDIAN_CALCULATOR_H__
#define __HEAP_MEDIAN_CALCULATOR_H__

#include "Heap.h"

class Heap_median_empty_exception { };

class Heap_median_calculator
{
private:
    Min_heap min_heap;
    Max_heap max_heap;
    float median;

public:
    void add_value(int val);
    float get_median() const;
};

#endif