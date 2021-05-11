# Segment Tree

## Introduction
Segment tree is a data structure used to perform range queries on a contiguous sequence of elements. 
In addition, it allows us to modify the sequence by performing an operation over a single element or a range of elements.
The queries and updates are done efficiently in O(log n) time and the tree requires a linear amount of memory.

## Usage

### Range Query
```diff -
T query_util(int start,int end,int query_start, int query_end,int np);
```
Retrieves the value from the node which completely covers the input range. 

### Range Update
```
void update_util(int start,int end,int index,int value, int np);
```
Updates the value and the specified index and recomputes the value of the nodes along the path to the index.

### Lazy update
```
void updateRange_util(int start,int end,int query_start,int query_end,int value,int np);
```
Since a single value update in an array may cause multiple updates in Segment Tree as there may be many segment tree nodes 
that have a single array element in their ranges.To overcome the same we can make use of lazy updates,
In which updates are postponed (avoid recursive calls in update) and do those updates only when required.

### Lazy assignment
```
void assignRange_util(int start,int end,int query_start,int query_end,int value,int np);
```
Lazy assignment works with the same logic as lazy update. Except, instead of incrementing value as done 
in lazy update the value will be assigned (Replaced by the value). 


## Iterator
Segment tree is a data structure which is used to do some of the range query/update operations on some set of elements.
So it has to be a data structure and it has to work with other generic algorithms also.
Therefore we have implemented the iterator to give the abstraction from the container. 
 Iterator class is inheriting from the bidirectional iterator.

It contains 2 fields: 
#### pointer to the segment tree
Pointer to the tree is used to access the elements.
#### index 
Index is used to get the updated value of the element at the given index. 

## Segment tree works with generic algorithms

#### lower bound
```
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int>> tree(b.begin(),b.end());
segment_tree<int, operation::sum<int> >::iterator it=lower_bound(tree.begin(),tree.end(),2);
```

#### find
```
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int>> tree(b.begin(),b.end());
segment_tree<int, operation::sum<int> >::iterator it=find(tree2.begin(), tree2.end(),2) - tree2.begin());
```

#### equal_range
```
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int>> tree(b.begin(),b.end());
typedef segment_tree<int, operation::sum<int> >::iterator stType;
pair<stType,stType> p =  equal_range(tree2.begin(), tree2.end(),2);
cout << p.first - tree2.begin() <<" " << p.second -  tree2.begin()<<"\n";
```

#### find_if
```
vector<int> b = {1,2,2,3,6};
segment_tree<int, operation::sum<int>> tree(b.begin(),b.end());
cout << "Find if, even number found at: ";
cout << find_if(tree2.begin(), tree2.end(),[](int x){return x%2 == 0;}) - tree2.begin()<< "\n";
```
