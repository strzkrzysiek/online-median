#ifndef __HEAP_H__
#define __HEAP_H__

#include <cstdlib>

class Empty_heap_exception { };

enum Heap_order
{
    MIN,
    MAX
};

template <Heap_order ORDER>
class Heap
{
private:
    size_t size;
    size_t remaining_size;

    int * data;

public:
    Heap();
    ~Heap();

    void    insert(int num);
    void    insert_minimal(int num);
    void    delete_minimal();
    void    delete_minimal_and_insert(int num);
    int     get_minimal() const;
    size_t  get_size() const;
    bool    is_empty() const;

private:
    void    extend();
    int     compare(int lhs, int rhs) const;
    void    push_upwards(unsigned idx);
    void    push_downwards(unsigned idx);
};

typedef Heap<MIN> Min_heap;
typedef Heap<MAX> Max_heap;

#endif