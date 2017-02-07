#ifndef __ONLINE_MEDIAN_CALCULATOR_H__
#define __ONLINE_MEDIAN_CALCULATOR_H__

#include "Heap.h"

class Empty_set_exception { };

class Online_median_calculator
{
private:
    Min_heap min_heap;
    Max_heap max_heap;
    float median;

public:
    Online_median_calculator();

    void add_value(int val);
    float get_median() const;
};

#endif