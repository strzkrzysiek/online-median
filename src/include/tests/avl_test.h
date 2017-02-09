#ifndef __AVL_TEST_H__
#define __AVL_TEST_H__

#include "gtest/gtest.h"
#include "AVL_tree.h"
#include <climits>

#ifdef GLOBAL_TEST_SIZE
# define AVL_TEST_SIZE GLOBAL_TEST_SIZE
#else
# define AVL_TEST_SIZE 1000
#endif

TEST(AVL_test, Ascending_sort)
{
    AVL_tree tree;

    for (int i=0; i<AVL_TEST_SIZE; i++)
        tree.insert(rand() % (AVL_TEST_SIZE * 2));

    AVL_tree::AVL_node * current_node = tree.insert(INT_MIN);
    current_node = current_node->get_next();
    while (current_node)
    {
        ASSERT_TRUE(current_node->get_value() >= current_node->get_prev()->get_value());
        current_node = current_node->get_next();
    }
}

TEST(AVL_test, Descending_sort)
{
    AVL_tree tree;

    for (int i=0; i<AVL_TEST_SIZE; i++)
        tree.insert(rand() % (AVL_TEST_SIZE * 2));

    AVL_tree::AVL_node * current_node = tree.insert(INT_MAX);
    current_node = current_node->get_prev();
    while (current_node)
    {
        ASSERT_TRUE(current_node->get_value() <= current_node->get_next()->get_value());
        current_node = current_node->get_prev(); 
    }
}

#endif