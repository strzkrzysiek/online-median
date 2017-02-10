#include "AVL_median_calculator.h"

void AVL_median_calculator::add_value(int val)
{
    if (tree.is_empty())
    {
        current_median = tree.insert(val);
        return;
    }

    if (val < current_median->get_value())
    {
        tree.insert(val);
        if (!(tree.get_size() & 1))
            current_median = current_median->get_prev();
    }
    else
    {
        tree.insert(val);
        if (tree.get_size() & 1)
            current_median = current_median->get_next();
    }
}

float AVL_median_calculator::get_median() const
{
    if (tree.is_empty())
        throw AVL_median_empty_exception();

    if (tree.get_size() & 1)
    {
        return (float)current_median->get_value();
    }
    else
    {
        AVL_tree::AVL_node * next = current_median->get_next();
        return (current_median->get_value() + next->get_value()) / 2.0f;
    }
}