#include "Multiset_median_calculator.h"

void Multiset_median_calculator::add_value(int val)
{
    if (elements.empty())
    {
        current_median = elements.insert(val);
        return;
    }

    if (val < *current_median)
    {
        elements.insert(val);
        if (!(elements.size() & 1))
            --current_median;
    }
    else if (val > *current_median)
    {
        elements.insert(val);
        if (elements.size() & 1)
            ++current_median;
    }
    else
    {
        elements.insert(current_median, val);
        if (!(elements.size() & 1))
            --current_median;
    }
}

float Multiset_median_calculator::get_median() const
{
    if (elements.empty())
        throw Multiset_median_empty_exception();

    if (elements.size() & 1)
    {
        return (float)*current_median;
    }
    else
    {
        std::multiset<int>::iterator next = current_median;
        ++next;
        return (*current_median + *next) / 2.0f;
    }
}