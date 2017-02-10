#ifndef __AVL_MEDIAN_CALCULATOR_H__
#define __AVL_MEDIAN_CALCULATOR_H__

#include "AVL_tree.h"

class AVL_median_empty_exception { };

class AVL_median_calculator
{
private:
    AVL_tree tree;
    AVL_tree::AVL_node * current_median;

public:
    void add_value(int val);
    float get_median() const;
};

#endif