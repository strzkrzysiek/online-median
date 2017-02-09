#include "AVL_tree.h"
#include <cassert>

AVL_tree::AVL_node::AVL_node(int val)
:element(val)
,left_child(NULL)
,right_child(NULL)
,next(NULL)
,prev(NULL)
,balance(AVL_BALANCED)
{
}


AVL_tree::AVL_tree()
:size(0)
,root(NULL)
{
}

AVL_tree::~AVL_tree()
{
    clear();
}

void AVL_tree::clear()
{
    if (root)
        clear_rec(root);
    root = NULL;
    size = 0;
}

AVL_tree::AVL_node * AVL_tree::insert(int val)
{
    AVL_node * new_node = new AVL_node(val);
    if (!root)
        root = new_node;
    else
        insert_rec(new_node, root);

    size++;

    return new_node;
}

size_t AVL_tree::get_size() const
{
    return size;
}

bool AVL_tree::is_empty() const
{
    return (size == 0);
}

void AVL_tree::clear_rec(AVL_node * node)
{
    assert(node);

    if (node->left_child)
        clear_rec(node->left_child);
    
    if (node->right_child)
        clear_rec(node->right_child);

    delete node;
}

bool AVL_tree::insert_rec(AVL_node * new_node, AVL_node *& subtree)
{
    assert(new_node);
    assert(subtree);

    if (new_node->element < subtree->element)
    {
        bool grown_up;
        if (subtree->left_child)
        {
            grown_up = insert_rec(new_node, subtree->left_child);
        }
        else
        {
            subtree->left_child = new_node;
            new_node->prev = subtree->prev;
            if (new_node->prev)
                new_node->prev->next = new_node;
            new_node->next = subtree;
            subtree->prev = new_node;
            grown_up = true;
        }

        if (!grown_up)
            return false;

        switch (subtree->balance)
        {
        case AVL_RIGHT_HIGHER:
            subtree->balance = AVL_BALANCED;
            return false;

        case AVL_BALANCED:
            subtree->balance = AVL_LEFT_HIGHER;
            return true;

        case AVL_LEFT_HIGHER:
            if (subtree->left_child->balance == AVL_LEFT_HIGHER)
                LL_rotation(subtree);
            else
                LR_rotation(subtree);
            subtree->balance = AVL_BALANCED;
            return false;
        }
    }
    else
    {
        bool grown_up;
        if (subtree->right_child)
        {
            grown_up = insert_rec(new_node, subtree->right_child);
        }
        else
        {
            subtree->right_child = new_node;
            new_node->next = subtree->next;
            if (new_node->next)
                new_node->next->prev = new_node;
            new_node->prev = subtree;
            subtree->next = new_node;
            grown_up = true;
        }

        if (!grown_up)
            return false;

        switch (subtree->balance)
        {
        case AVL_LEFT_HIGHER:
            subtree->balance = AVL_BALANCED;
            return false;

        case AVL_BALANCED:
            subtree->balance = AVL_RIGHT_HIGHER;
            return true;

        case AVL_RIGHT_HIGHER:
            if (subtree->right_child->balance == AVL_RIGHT_HIGHER)
                RR_rotation(subtree);
            else
                RL_rotation(subtree);
            subtree->balance = AVL_BALANCED;
            return false;
        }
    }

    assert(0);
    return false;
}

inline void AVL_tree::LL_rotation(AVL_node *& node)
{
    AVL_node * node1 = node->left_child;
    assert(node1);

    node->left_child = node1->right_child;
    node1->right_child = node;
    node->balance = AVL_BALANCED;
    node = node1;
}

inline void AVL_tree::LR_rotation(AVL_node *& node)
{
    AVL_node * node1 = node->left_child;
    assert(node1);

    AVL_node * node2 = node1->right_child;
    assert(node2);

    node1->right_child = node2->left_child;
    node2->left_child = node1;
    node->left_child = node2->right_child;
    node2->right_child = node;
    node->balance = (node2->balance == AVL_LEFT_HIGHER) ? AVL_RIGHT_HIGHER : AVL_BALANCED;
    node1->balance = (node2->balance == AVL_RIGHT_HIGHER) ? AVL_LEFT_HIGHER : AVL_BALANCED;
    node = node2;
}

inline void AVL_tree::RR_rotation(AVL_node *& node)
{
    AVL_node * node1 = node->right_child;
    assert(node1);

    node->right_child = node1->left_child;
    node1->left_child = node;
    node->balance = AVL_BALANCED;
    node = node1;
}

inline void AVL_tree::RL_rotation(AVL_node *& node)
{
    AVL_node * node1 = node->right_child;
    assert(node1);

    AVL_node * node2 = node1->left_child;
    assert(node2);

    node1->left_child = node2->right_child;
    node2->right_child = node1;
    node->right_child = node2->left_child;
    node2->left_child = node;
    node->balance = (node2->balance == AVL_RIGHT_HIGHER) ? AVL_LEFT_HIGHER : AVL_BALANCED;
    node1->balance = (node2->balance == AVL_LEFT_HIGHER) ? AVL_RIGHT_HIGHER : AVL_BALANCED;
    node = node2;
}