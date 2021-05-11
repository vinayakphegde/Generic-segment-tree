# Segment Tree

## Introduction
Segment tree is a data structure used to perform range queries on a contiguous sequence of elements. It also allows us to modify the sequence by performing an operation over a single element or a range of elements. The queries and updates are done efficiently in O(log n) time and the tree requires a linear amount of memory.

## Operations supported
1. Sum
2. Minimum
3. Maximum

## Functions supported

### Query on a segment
```cpp
iterator query(int query_left, int query_right);
``` 
Finds the minimum or maximum element within the given range. Returns an iterator to the element in the case of minimum or maximum operation. Returns the value in the case of sum operation.
```cpp
vector<int> a = {2, 3, 1, 6, 5};

segment_tree<int, operation::min<int> > tree1(a.begin(), a.end());
segment_tree<int, operation::min<int> >::iterator it = tree1.query(0,3);

segment_tree<int, operation::sum<int> > tree2(a.begin(), a.end());
int sum = tree2.query(0,3);
```
### Update
```cpp
void update(int index, int value);
```
Updates the value and the specified index and recomputes the value of the nodes along the path to the index.
```cpp
vector<int> a = {2, 3, 1, 6, 5};

segment_tree<int, operation::min<int> > tree(a.begin(), a.end());
tree.update(2,15);
```

### Update on a segment
```cpp
void update(int query_left, int query_right, int value);
```
Assigns the given value to the given range of indices. Implements lazy update, in which updates are postponed and done only when required.
```cpp
vector<int> a = {2, 3, 1, 6, 5};

segment_tree<int, operation::min<int> > tree(a.begin(), a.end());
tree.update(2,4,15);
```

### Addition on a segment 
```cpp
void add(int query_start,int query_end,int value);
``` 
Adds the given value to the given range of indices. Addition is done on the node which covers the entire segment. Atmost 2 nodes are modified.
```cpp
vector<int> a = {2, 3, 1, 6, 5};

segment_tree<int, operation::max<int> > tree(a.begin(), a.end());
tree.add(2,4,10);
```

## Iterators with C++ STL algorithms
Our implementation of segment tree works with standard C++ STL algorithms as well. Some examples include: 

#### lower bound
```cpp
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
segment_tree<int, operation::sum<int> >::iterator it = lower_bound(tree.begin(), tree.end(), 2);
```

#### find
```cpp
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
segment_tree<int, operation::sum<int> >::iterator it = find(tree.begin(), tree.end(), 2);
```

#### equal_range
```cpp
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
typedef segment_tree<int, operation::sum<int> >::iterator seg_tree_iter;
pair<seg_tree_iter, seg_tree_iter> p =  equal_range(tree.begin(), tree.end(), 2);
```

#### find_if
```cpp
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
segment_tree<int, operation::sum<int> >::iterator it = find_if(tree.begin(), tree.end(), [](int x){return x%2 == 0;});
```

## Performance
Comparison of time taken to find the sum on segments of different sizes.
```
| Range        | Linear Datastructure | Segment Tree   |
|--------------|----------------------|----------------|
| [6,28]       | 1 microseconds       | 2 microseconds |
| [414,959]    | 3 microseconds       | 2 microseconds |
| [1705,8412]  | 36 microseconds      | 2 microseconds |
| [1196,36532] | 198 microseconds     | 4 microseconds |
```

## References
* https://www.cplusplus.com/doc/oldtutorial/templates/
* https://cp-algorithms.com/data_structures/segment_tree.html
* https://codeforces.com/edu/course/2/lesson/4/1