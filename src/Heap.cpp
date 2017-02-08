#include "Heap.h"
#include <cstdlib>
#include <cstring>
#include <cassert>

#define HEAP_INITIAL_SIZE   32
#define HEAP_PARENT(idx)    ((idx-1) >> 1)
#define HEAP_LCHILD(idx)    ((idx << 1) + 1)
#define HEAP_RCHILD(idx)    ((idx << 1) + 2)
#define HEAP_SWAP(x, y)     x ^= y, y ^= x, x ^= y

template <Heap_order ORDER>
Heap<ORDER>::Heap()
:size(0)
,remaining_size(HEAP_INITIAL_SIZE)
{
    data = (int *)malloc(sizeof(int) * HEAP_INITIAL_SIZE);
};

template <Heap_order ORDER>
Heap<ORDER>::~Heap()
{
    free(data);
    data = NULL;
    size = 0;
    remaining_size = 0;
}

template <Heap_order ORDER>
void Heap<ORDER>::insert(int num)
{
    if (remaining_size == 0)
        extend();

    data[size] = num;
    size++;
    remaining_size--;  

    if (size < 2)
        return;

    push_upwards(size - 1);  
}

template <Heap_order ORDER>
void Heap<ORDER>::insert_minimal(int num)
{
    assert(size == 0 || compare(data[0], num) >= 0);

    if (remaining_size == 0)
        extend();

    int idx = size;
    while (idx)
    {
        int parent = HEAP_PARENT(idx);
        data[idx] = data[parent];
        idx = parent;
    }
    data[0] = num;

    size++;
    remaining_size--;
}

template <Heap_order ORDER>
void Heap<ORDER>::delete_minimal()
{
    if (size == 0)
        throw Empty_heap_exception();

    size--;
    remaining_size++;

    HEAP_SWAP(data[size], data[0]);

    if (size < 2)
        return;

    push_downwards(0);
}

template <Heap_order ORDER>
void Heap<ORDER>::delete_minimal_and_insert(int num)
{
    if (size == 0)
        throw Empty_heap_exception();

    data[0] = num;
    push_downwards(0);
}

template <Heap_order ORDER>
int Heap<ORDER>::get_minimal() const
{
    if (size == 0)
        throw Empty_heap_exception();

    return data[0];
}

template <Heap_order ORDER>
size_t Heap<ORDER>::get_size() const
{
    return size;
}

template <Heap_order ORDER>
bool Heap<ORDER>::is_empty() const
{
    return (size == 0);
}

template <Heap_order ORDER>
inline void Heap<ORDER>::extend()
{
    assert(remaining_size == 0);

    int * new_data = (int *)malloc(sizeof(int) * 2 * size);
    memcpy(new_data, data, sizeof(int) * size);
    free(data);
    data = new_data;
    remaining_size = size;
}

template <>
inline int Heap<MIN>::compare(int lhs, int rhs) const
{
    return lhs - rhs;
}

template <>
inline int Heap<MAX>::compare(int lhs, int rhs) const
{
    return rhs - lhs;
}

template <Heap_order ORDER>
inline void Heap<ORDER>::push_upwards(unsigned idx)
{
    while (idx > 0)
    {
        unsigned parent = HEAP_PARENT(idx);
        if (compare(data[parent], data[idx]) < 0)
            break;

        HEAP_SWAP(data[parent], data[idx]);
        idx = parent;
    }
}

template <Heap_order ORDER>
inline void Heap<ORDER>::push_downwards(unsigned idx)
{
    while (true)
    {
        unsigned swap_candidate = idx;

        unsigned left_child = HEAP_LCHILD(idx);
        if (left_child < size && compare(data[left_child], data[swap_candidate]) < 0)
            swap_candidate = left_child;

        unsigned right_child = left_child + 1;
        if (right_child < size && compare(data[right_child], data[swap_candidate]) < 0)
            swap_candidate = right_child;

        if (swap_candidate == idx)
            return;

        HEAP_SWAP(data[idx], data[swap_candidate]);
        idx = swap_candidate;
    }
}

template class Heap<MIN>;
template class Heap<MAX>;
