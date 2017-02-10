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

Additionally, every heap contains a small fixed-sized buffer to store several smallest/biggest values. Let's call them subminimal buffers. This makes `insert_minimal(int)` and `delete_minimal_and_insert(int)` operations to run in constant time if the buffer is not full or not empty, respectively, and thus, most of the rebalance operations constant time.

### Complexity

During each insertion depending on the need to rebalance two cases are possible:
* no rebalance is needed - only one insertion is performed which has amortized complexity of O(1),
* otherwise - `delete_minimal_and_insert(int)` and `insert_minimal(int)` methods are invoked; the first one has complexity of O(logn) if the subminimal buffer is empty as it requires the new element to traverse the heap starting from the root and complexity of O(1) if the buffer is non-empty; same with `insert_minimal(int)` - O(logn) if the buffer is full as it traverses the heap from the bottom to the very top and O(1) if the buffer is not full.

Having a uniformly random input and not having the subminimal buffers, the first case happens in 75% of operations while the second on in 25%. As already said, the latter one can be done either in O(1) or O(logn) depending on the state of the buffers. The exact calculations depend on the distribution of the input, but assuming the uniform one we can say that every state of the buffer is equally possible and the possibility of an operation taking O(logn) time is 25% times one over the size of the buffer.

In worst case only second option is used and the buffer quickly overfills (for sorted input) and it results in total of O(nlogn) operations. In an average case the calculation is much faster but still in O(nlogn) time. In the best case (having an input that keeps the heaps moreless balanced) the complexity is O(n).

## Algorithm using AVL tree `AVL_median_calculator`

### Description

We start with the first element being inserted and we remember its node as current median. Then after each insertion we can either adjust the node holding the median or leave it as it is.

If the element inserted is lower than the current median, its predecessor can be set as a new one depending on number of elements in the tree.

Symmetrically, if the element is bigger or equal (this tree inserts elements to the right of the equal ones), its successor can be set as a new median.

### Complexity

Insertion time into the AVL tree is logarithmic. Finding successor and predecessor is done in constant time (because of keeping pointers to them). As the insertion is performed every time a value is added into the set, the total complexity turnes out to be O(nlogn).