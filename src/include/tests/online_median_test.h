#ifndef __ONLINE_MEDIAN_TEST_H__
#define __ONLINE_MEDIAN_TEST_H__

#include <vector>
#include <algorithm>
#include "Online_median_calculator.h"

#define ONLINE_MEDIAN_TEST_SIZE 1000

TEST(Online_median_test, Random)
{
    std::vector<int> sample_data;
    sample_data.reserve(ONLINE_MEDIAN_TEST_SIZE);
    for (int i=0; i<ONLINE_MEDIAN_TEST_SIZE; i++)
        sample_data.push_back(rand() % (ONLINE_MEDIAN_TEST_SIZE * 10));

    std::vector<float> medians;
    std::vector<int> sorted_data(sample_data);
    medians.reserve(ONLINE_MEDIAN_TEST_SIZE);

    for (int i=1; i<=ONLINE_MEDIAN_TEST_SIZE; i++)
    {
        std::sort(sorted_data.begin(), sorted_data.begin() + i);
        if (i % 2 == 0)
        {
            float median = (sorted_data[i/2] + sorted_data[i/2 - 1]) / 2.0f;
            medians.push_back(median);
        }
        else
        {
            medians.push_back((float)sorted_data[i/2]);
        }
    }

    Online_median_calculator calculator;

    for (int i=0; i<ONLINE_MEDIAN_TEST_SIZE; i++)
    {
        calculator.add_value(sample_data[i]);
        ASSERT_EQ(calculator.get_median(), medians[i]);
    }
}

TEST(Online_median_test, Ascending)
{
    std::vector<int> sorted_data;
    sorted_data.reserve(ONLINE_MEDIAN_TEST_SIZE);
    for (int i=0; i<ONLINE_MEDIAN_TEST_SIZE; i++)
        sorted_data.push_back(rand() % (ONLINE_MEDIAN_TEST_SIZE * 10));

    std::sort(sorted_data.begin(), sorted_data.end());

    std::vector<float> medians;
    medians.reserve(ONLINE_MEDIAN_TEST_SIZE);

    for (int i=1; i<=ONLINE_MEDIAN_TEST_SIZE; i++)
    {
        if (i % 2 == 0)
        {
            float median = (sorted_data[i/2] + sorted_data[i/2 - 1]) / 2.0f;
            medians.push_back(median);
        }
        else
        {
            medians.push_back((float)sorted_data[i/2]);
        }
    }

    Online_median_calculator calculator;

    for (int i=0; i<ONLINE_MEDIAN_TEST_SIZE; i++)
    {
        calculator.add_value(sorted_data[i]);
        ASSERT_EQ(calculator.get_median(), medians[i]);
    }
}

TEST(Online_median_test, Descending)
{
    std::vector<int> sorted_data;
    sorted_data.reserve(ONLINE_MEDIAN_TEST_SIZE);
    for (int i=0; i<ONLINE_MEDIAN_TEST_SIZE; i++)
        sorted_data.push_back(rand() % (ONLINE_MEDIAN_TEST_SIZE * 10));

    std::sort(sorted_data.rbegin(), sorted_data.rend());

    std::vector<float> medians;
    medians.reserve(ONLINE_MEDIAN_TEST_SIZE);

    for (int i=1; i<=ONLINE_MEDIAN_TEST_SIZE; i++)
    {
        if (i % 2 == 0)
        {
            float median = (sorted_data[i/2] + sorted_data[i/2 - 1]) / 2.0f;
            medians.push_back(median);
        }
        else
        {
            medians.push_back((float)sorted_data[i/2]);
        }
    }

    Online_median_calculator calculator;

    for (int i=0; i<ONLINE_MEDIAN_TEST_SIZE; i++)
    {
        calculator.add_value(sorted_data[i]);
        ASSERT_EQ(calculator.get_median(), medians[i]);
    }
}

#endif