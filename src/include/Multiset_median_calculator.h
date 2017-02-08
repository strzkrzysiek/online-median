#ifndef __MULTISET_MEDIAN_CALCULATOR_H__
#define __MULTISET_MEDIAN_CALCULATOR_H__

#include <set>

class Multiset_median_empty_exception { };

class Multiset_median_calculator
{
private:
    std::multiset<int> elements;
    std::multiset<int>::iterator current_median;

public:
    void add_value(int val);
    float get_median() const;
};

#endif