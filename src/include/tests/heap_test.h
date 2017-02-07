#ifndef __TESTS_H__
#define __TESTS_H__

#include "gtest/gtest.h"
#include "Heap.h"
#include <climits>

#define HEAP_TEST_SIZE 1000

TEST(Heap_test, Ascending_sort)
{
    Min_heap heap;

    for (int i=0; i<HEAP_TEST_SIZE; i++)
        heap.insert(rand() % (HEAP_TEST_SIZE * 2));

    int current_min = INT_MIN;

    while (!heap.is_empty())
    {
        int elem = heap.get_minimal();
        ASSERT_TRUE(current_min <= elem);
        heap.delete_minimal();
        current_min = elem;
    }
}

TEST(Heap_test, Descending_sort)
{
    Max_heap heap;

    for (int i=0; i<HEAP_TEST_SIZE; i++)
        heap.insert(rand() % (HEAP_TEST_SIZE * 2));

    int current_max = INT_MAX;

    while (!heap.is_empty())
    {
        int elem = heap.get_minimal();
        ASSERT_TRUE(current_max >= elem);
        heap.delete_minimal();
        current_max = elem;
    }
}

#endif