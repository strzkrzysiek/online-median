#include "Heap_median_calculator.h"
#include <cassert>

void Heap_median_calculator::add_value(int val)
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
            int transfer_value = min_heap.get_minimal();
            min_heap.delete_minimal_and_insert(val);
            max_heap.insert_minimal(transfer_value);
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
            int transfer_value = max_heap.get_minimal();
            max_heap.delete_minimal_and_insert(val);
            min_heap.insert_minimal(transfer_value);
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

float Heap_median_calculator::get_median() const
{
    if (max_heap.is_empty())
    {
        throw Heap_median_empty_exception();
    }

    return median;
}