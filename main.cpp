#include <cstdio>
#include <ctime>
#include "Heap.h"

int main()
{
    srand(time(NULL));

    Min_heap heap;

    for (int i=0; i<10; i++)
        heap.insert(rand() % 25);

    while (!heap.is_empty())
    {
        int value = heap.get_minimal();
        printf("%d ", value);
        heap.delete_minimal();
    }

    printf("\n");

    return 0;
}