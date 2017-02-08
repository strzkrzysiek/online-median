#include "Online_median_calculator.h"
#include <cassert>

void Online_median_calculator::add_value(int val)
{
    if (max_heap.is_empty())
    {
        max_heap.insert(val);
        median = (float)val;
        return;
    }

    int diff = max_heap.get_size() - min_heap.get_size();
    switch (diff)
    {
    case -1:
        if (val <= median)
        {
            max_heap.insert(val);
            median = (median + max_heap.get_minimal()) / 2;
        }
        else
        {
            min_heap.insert(val);
            int transfer_value = min_heap.get_minimal();
            min_heap.delete_minimal();
            max_heap.insert(transfer_value);
            median = (min_heap.get_minimal() + max_heap.get_minimal()) / 2.0f;
        }
        break;

    case 1:
        if (val >= median)
        {
            min_heap.insert(val);
            median = (median + min_heap.get_minimal()) / 2;
        }
        else
        {
            max_heap.insert(val);
            int transfer_value = max_heap.get_minimal();
            max_heap.delete_minimal();
            min_heap.insert(transfer_value);
            median = (min_heap.get_minimal() + max_heap.get_minimal()) / 2.0f;
        }
        break;

    case 0:
        if (val <= median)
        {
            max_heap.insert(val);
            median = (float)max_heap.get_minimal();
        }
        else
        {
            min_heap.insert(val);
            median = (float)min_heap.get_minimal();
        }
        break;

    default:
        assert(0);
        break;
    }
}

float Online_median_calculator::get_median() const
{
    if (max_heap.is_empty())
    {
        throw Online_median_empty_exception();
    }

    return median;
}