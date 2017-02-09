#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <cstdlib>

#define AVL_BALANCED        0x00
#define AVL_RIGHT_HIGHER    0x01
#define AVL_LEFT_HIGHER     0x02

class AVL_tree
{
public:
    struct AVL_node
    {
        friend class AVL_tree;

    private:
        int element;

        AVL_node * left_child;
        AVL_node * right_child;
        AVL_node * next;
        AVL_node * prev;
        int balance;

        AVL_node(int val);

    public:
        int get_value() { return element; }
        AVL_node * get_next() { return next; }
        AVL_node * get_prev() { return prev; }
    };

private:
    size_t size;
    AVL_node * root;

public:
    AVL_tree();
    ~AVL_tree();

    void clear();

    AVL_node * insert(int val);

    size_t get_size() const;
    bool is_empty() const;

private:
    void clear_rec(AVL_node * node);
    bool insert_rec(AVL_node * new_node, AVL_node *& subtree);

    void LL_rotation(AVL_node *& node);
    void LR_rotation(AVL_node *& node);
    void RR_rotation(AVL_node *& node);
    void RL_rotation(AVL_node *& node);
};

#endif