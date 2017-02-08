# Online median

A bundle of two algorithms that calculate median of a set provided that its elements are received on-line and the program is asked for the result after each insertion.

### Disclaimer

This project was written for purposes of a recruitment process and was not intended to be used in professional sofware. It is provided "as is" and the author disclaims all warranties with regard to this software

## Cloning, building and running

To clone this repository be sure that you get its submodule. In order to do this type:
```
git clone --recursive https://github.com/strzkrzysiek/online-median.git
```
If you have already cloned without the `--recursive` option type:
```git submodule update --init --recursive```
to have the submodule been cloned.

In the main directory type `make` or `make debug` to build the project int the release or debug version, respectively.

Running the program `./onlinemedian` triggers the tests. In addition to the attributes provided by `googletest` you can specify seed attribute. Otherwise it is chosen at random.
```
./onlinemedian --seed=42
```

## Algorithm using heaps `Heap_median_calculator`

### Description

We keep two heaps for storing values smaller and bigger than the current median. One that stores the smaller values has maximum in its root, while the other one - minimum. The heaps are balanced, i.e. the difference in their size is at most 1.

If the sizes are equal while inserting a new element, it is places into the adequate one after comparison with the current median.

If the sizes are unequal two options are possible. Either we choose to place it into the one with smaller number of elements or we put it into the another one and there is a need to rebalance the heaps. It is done by deleting the minimum and transfering it into the smaller heap.

Since operations that are done on the heaps are very special, additional specialized methods (`insert_minimal(int)` and `delete_minimal_and_insert(int)`) were implemented to speed up the process.

### Complexity

During each insertion depending on the need to rebalance two cases are possible:
* no rebalance is needed - only one insertion is performed which has amortized complexity of O(n),
* otherwise - delete_minimal_and_insert(int) and insert_minimal(int) methods are invoked; the first one has complexity of O(nlogn) as it requires the new element to traverse the heap starting from the root; same with inserting_minimal as it traverses the heap from the bottom to the very top.

Having a uniformly random input the first case happens in 75% of operations while the second on in 25%. However, in the worst case only the second option is used (for sorted input) which also results in O(nlogn) operations. In the best case (having an input that keeps the heaps balanced all the time) the complexity is O(n).

## Algorithm using STL multisets

### Description

While inserting elements into the multiset we can keep track of current median. It is done by storing an iterator to this element which is guaranteed to be safe by C++ standard. By examining if the newly inserted element is inserted before or after the current median we can decide to move it backwards or forwards.

### Complexity

Multisets in the STL implementation require to have logarithmic insertion time and amortized constant time of incrementing/decrementing an iterator. As the insertion is performed every time a value is added into the set, the total complexity turnes out to be O(nlogn).
