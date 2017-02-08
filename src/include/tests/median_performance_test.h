#ifndef __MEDIAN_PERFORMANCE_TEST_H__
#define __MEDIAN_PERFORMANCE_TEST_H__

#include "gtest/gtest.h"
#include "Heap_median_calculator.h"
#include "Multiset_median_calculator.h"
#include <vector>
#include <algorithm>

#define PERFORMANCE_TEST_SIZE 10000000

class Median_performance_test : public testing::Test
{
public:
    static std::vector<int> random_data;
    static std::vector<float> random_data_medians;
    static std::vector<int> ascending_data;
    static std::vector<float> ascending_data_medians;
    static std::vector<int> descending_data;
    static std::vector<float> descending_data_medians;


protected:
    static void SetUpTestCase()
    {
        random_data.reserve(PERFORMANCE_TEST_SIZE);
        for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
            random_data.push_back(rand() % 1000000);

        ascending_data = random_data;
        std::sort(ascending_data.begin(), ascending_data.end());

        descending_data = random_data;
        std::sort(descending_data.rbegin(), descending_data.rend());

        {
            random_data_medians.reserve(PERFORMANCE_TEST_SIZE);
            Heap_median_calculator calculator;
            for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
            {
                calculator.add_value(random_data[i]);
                random_data_medians.push_back(calculator.get_median());
            }
        }

        {
            ascending_data_medians.reserve(PERFORMANCE_TEST_SIZE);
            Heap_median_calculator calculator;
            for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
            {
                calculator.add_value(ascending_data[i]);
                ascending_data_medians.push_back(calculator.get_median());
            }
        }

        {
            descending_data_medians.reserve(PERFORMANCE_TEST_SIZE);
            Heap_median_calculator calculator;
            for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
            {
                calculator.add_value(descending_data[i]);
                descending_data_medians.push_back(calculator.get_median());
            }
        }
    }
};

std::vector<int> Median_performance_test::random_data;
std::vector<float> Median_performance_test::random_data_medians;
std::vector<int> Median_performance_test::ascending_data;
std::vector<float> Median_performance_test::ascending_data_medians;
std::vector<int> Median_performance_test::descending_data;
std::vector<float> Median_performance_test::descending_data_medians;


TEST_F(Median_performance_test, Heap_random)
{
    Heap_median_calculator calculator;

    for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
    {
        calculator.add_value(random_data[i]);
        ASSERT_EQ(calculator.get_median(), random_data_medians[i]);
    }
}


TEST_F(Median_performance_test, Multiset_random)
{
    Multiset_median_calculator calculator;

    for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
    {
        calculator.add_value(random_data[i]);
        ASSERT_EQ(calculator.get_median(), random_data_medians[i]);
    }
}

TEST_F(Median_performance_test, Heap_ascending)
{
    Heap_median_calculator calculator;

    for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
    {
        calculator.add_value(ascending_data[i]);
        ASSERT_EQ(calculator.get_median(), ascending_data_medians[i]);
    }
}

TEST_F(Median_performance_test, Multiset_ascending)
{
    Multiset_median_calculator calculator;

    for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
    {
        calculator.add_value(ascending_data[i]);
        ASSERT_EQ(calculator.get_median(), ascending_data_medians[i]);
    }
}

TEST_F(Median_performance_test, Heap_descending)
{
    Heap_median_calculator calculator;

    for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
    {
        calculator.add_value(descending_data[i]);
        ASSERT_EQ(calculator.get_median(), descending_data_medians[i]);
    }
}

TEST_F(Median_performance_test, Multiset_descending)
{
    Multiset_median_calculator calculator;

    for (int i=0; i<PERFORMANCE_TEST_SIZE; i++)
    {
        calculator.add_value(descending_data[i]);
        ASSERT_EQ(calculator.get_median(), descending_data_medians[i]);
    }
}

#endif