#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <iostream>
#include <iterator>
#include <typeinfo>
using namespace std;

#define mid(l,r) (l+(r-l)/2)

#include "operation.hpp"

template<typename T,typename pred_t>
class segment_tree
{
	private:
	struct tree_node{
		T value;
		int index;
	};
	//To store the values to be propagated 
	mutable vector<T> lazy;
	mutable vector<tree_node> tree;
	//To differentiate between the update  nad assign
	mutable vector<bool> update_assign;// True if update and false if assign 
	int n;
	int size_;

	//To get elements from the containers passed to build a segment tree
	template<typename iter>
	T get_ele(iter &begin_, iter &end_)
	{
		if(begin_!=end_)
			return *begin_++;

		cout<<"WARNING: Returning out of range!";
		return *end_;
	}

	//For building a segment tree
	template<typename iter>
	void build_tree(iter &begin_, iter &end_, int start,int end, int np)
	{
		//To update the root leaves of the tree.
		if(end == start)
		{
			tree[np].value = get_ele(begin_,end_);
			tree[np].index = start;
			return;
		}

		//Recursively build the children
		int mid=mid(start,end);
		build_tree(begin_, end_, start,mid,2*np+1);
		build_tree(begin_, end_, mid+1,end,2*np+2);
		
		//update the node using its children
		tree[np] = pred_t()(tree[2*np+1],tree[2*np+2]);
	}
	
	//Used to propagate lazy value of a node to its children   
	void propagate(int start, int end, int np) const
	{

		if (lazy[np] != 0)
    	{ 
    		//Update 
			if(update_assign[np] == true){

				tree[np].value += lazy[np];
				//If node is not a root node propagate the lazy value to its children
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[2*np+1] =  true;
					lazy[np*2+2] += lazy[np];
					update_assign[2*np+1] =  true;
				}
	
				lazy[np] = 0;
			}
			//Assign 
			else{
				tree[np].value = lazy[np];
				//If node is not a root node propagate the lazy value to its children 
				if (start != end)
				{
					lazy[np*2+1] = lazy[np];
					update_assign[2*np+1] =  false;
					lazy[np*2+2] = lazy[np];
					update_assign[2*np+1] =  false;
				}
				update_assign[np] =  true;
				lazy[np] = 0;
			}
  		}
	}
	
	//Used to support query function
	tree_node query_util(int start,int end,int query_start,int query_end,int np) 
	{
		propagate(start, end, np);
		//If node doesnt not cover anything in the given range
		if(start>query_end or end<query_start)
		{
			return {pred_t().neutral_element, -1}; 
		}
		//If range covered by the node is in the queried range
		if(query_start<=start and query_end>=end)
		{
			return tree[np];
		}
		//Recursively query the children
		int mid=mid(start,end);
		tree_node left=query_util(start,mid,query_start,query_end,2*np+1);
		tree_node right=query_util(mid+1,end,query_start,query_end,2*np+2);
		return pred_t()(left,right);
	}
	
	//Used to support the update function
	void update_util(int start,int end,int index,int value,int np)
	{
		if(index<start or index>end)
			return;
		
		if(start==end)
		{
			tree[np].value += value;
			return;
		}

		//Search which child covers given index and recursively traverse that child
		int mid=mid(start,end);
		if(index>mid)
		{
			update_util(mid+1,end,index,value,2*np+2);
		}
		else
		{
			update_util(start,mid,index,value,2*np+1);
		}

		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	}
	
	//Used to support range update
	void updateRange_util(int start,int end,int query_start,int query_end,int value,int np)
	{
		// If the node already contains the value for update/assign push it to its children
		propagate(start, end, np);
			
		if(start>query_end or end<query_start)
			return;

		//If the node is in the range assign the value to lazy propagate when queried and return
		if (start>=query_start && end<=query_end)
    	{
        	tree[np].value += value;
        	if (start != end)
        	{
            	lazy[np*2 + 1]  += value;
				update_assign[2*np+1] =  true;
            	lazy[np*2 + 2]  += value;
				update_assign[2*np+2] =  true;
        	}
        	return;
    	}
		int mid=mid(start,end);
		updateRange_util(start,mid,query_start,query_end,value,2*np+1);
		updateRange_util(mid+1,end,query_start,query_end,value,2*np+2);
   		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);	
	}

	//Used to support range assign 
	void assignRange_util(int start,int end,int query_start,int query_end,int value,int np)
	{
		// If the node already contains the value for update/assign push it to its children
		propagate(start, end, np);
		
		if(start>query_end or end<query_start)
			return;

		//If the node is in the range assign the value to lazy propagate when queried and return
		if (start>=query_start && end<=query_end)
    	{
        	tree[np].value = value;
        	if (start != end)
        	{
            	lazy[np*2 + 1]  = value;
				update_assign[2*np+1] =  false;
            	lazy[np*2 + 2]  = value;
				update_assign[2*np+2] =  false;
        	}
        	return;
    	}
		int mid=mid(start,end);
		assignRange_util(start,mid,query_start,query_end,value,2*np+1);
		assignRange_util(mid+1,end,query_start,query_end,value,2*np+2);
   		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);	
	}

	//Used to get the get element at a particular index
	T get_util(int start,int end,int index,int np) const
	{
		//propagate and update the part of the tree that contains the index
		propagate(start, end, np);
		
		if(index<start or index>end)
			return pred_t().neutral_element;
		
		if(start==end)
		{
			return tree[np].value;
		}
		int mid=mid(start,end);
		//Search which child covers given index and recursively traverse that child
		if(index>mid)
		{
			return get_util(mid+1,end,index,2*np+2);
		}
		
		return get_util(start,mid,index,2*np+1);
	}

	//To get the value at the given index
	T get(int index) const
	{
		return get_util(0,size_-1,index,0);
	}

	//A support of bidirectional iterator for iterating over the segment trees
	public:
	class iterator: public std::iterator<std::bidirectional_iterator_tag, T>
    {
        private:
        const segment_tree<T, pred_t> *tree_;
	    int index_;

        public:
        iterator(const segment_tree<T, pred_t> &tree, int index):tree_(&tree), index_(index)
        { }

		iterator(const iterator& rhs):tree_(rhs.tree_), index_(rhs.index_)
		{ }
		iterator& operator=(const iterator& rhs)
		{
			tree_ = rhs.tree_;
			index_ = rhs.index_;
			return *this;
		}
        iterator& operator++()
        {
            ++index_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }
		iterator& operator--()
        {
            --index_;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp(*this);
            --(*this);
            return temp;
        }
        T operator*()
        {
            return tree_->get(index_);
        }
        bool operator==(const iterator &rhs)
        {
            return index_ == rhs.index_;
        }
        bool operator!=(const iterator &rhs)
        {
            return !(*this == rhs);
        }
		int get_index()
		{
			return index_;
		}
        int operator-(const iterator &rhs)
        {
            return index_ - rhs.index_;
        }
        int operator+(const iterator &rhs)
        {
            return index_ + rhs.index_;
        }
    };

	// Default Constructor
	segment_tree() = delete;

	// Parameterized Constructor
	template<typename iter>
	segment_tree(iter begin, iter end)
	{
		size_ = (int)distance(begin, end);
		n = 1;
		//Find the size of the segment tree
		while(n < size_){
			n = n*2;
		}
		n = n*2;

		//Allocate memory, accourding to thte size of the segment tree which needs to be built
		tree.resize(n,{pred_t().neutral_element , -1});
		lazy.resize(n,0);
		update_assign.resize(n,true);
		build_tree(begin, end, 0, size_-1, 0);
	}
	
	// Copy Constructor
	segment_tree(const segment_tree<T, pred_t> &other): size_(other.size_), n(other.n)
	{
		tree = other.tree;
		lazy = other.lazy;
		update_assign = other.update_assign;
	}
	
	//To create a segment tree using the iterartors of other segment tree
	segment_tree(iterator begin, iterator end)
	{
		size_ = end - begin;
		n = 1;
		while(n < size_){
			n = n*2;
		}
		n = n*2;

		tree.resize(n,{pred_t().neutral_element , -1});
		lazy.resize(n,0);
		update_assign.resize(n,true);
		build_tree(begin, end, 0, size_-1, 0);
	}

	// Destructor
	~segment_tree()
	{
		// DO NOTHING
	}
	
	//To perform a range query
	iterator query(int query_start,int query_end) 
	{
		tree_node t = query_util(0,size_-1,query_start,query_end,0);
		return iterator(*this, t.index);
	}

	//To perform an update at a particular value
	void update(int index,int value)
	{
		return update_util(0,size_-1,index,value,0);
	}

	//To perform range update
	void updateRange(int query_start,int query_end,int value){

		if(query_start < 0 || query_end > size_ )
			return;
		return updateRange_util(0,size_-1,query_start,query_end,value,0);
	}

	//To perform range assign 
	void assignRange(int query_start,int query_end,int value){
		if(query_start < 0 || query_end > size_ )
			return;
		return assignRange_util(0,size_-1,query_start,query_end,value,0);
	}

	int size() const
	{
		return size_;
	}
	bool empty() const
	{
		return size_==0;
	}
	iterator begin() const
	{
		return iterator(*this, 0);
	}
	iterator end() const
	{
		return iterator(*this, size_);
	}

	//To display the segment tree
	void display() const
	{
		iterator first = begin();
		iterator last = end();
		while(first!=last)
		{
			cout<<*first<<" ";
			++first;
		}
		cout<<"\n";
	}

	//Used to support display_WU
	T get_util_WU(int start,int end,int index,int np) const
	{		
		if(index<start or index>end)
			return pred_t().neutral_element;
		
		if(start==end)
		{
			return tree[np].value;
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			return get_util_WU(mid+1,end,index,2*np+2);
		}
		
		return get_util_WU(start,mid,index,2*np+1);
	}

	//To display the a tree in its current state(Without propogating the lazy value associated with the nodes)
	void display_WU() const
	{
		int first = begin().get_index();
		int last = end().get_index();
		while(first!=last){
			cout << get_util_WU(0,size_-1,first,0) << " " ;
			first++;
		}
		cout << "\n";
	}

};

template<typename T>
class segment_tree<T, operation::sum<T> >
{
	private:
	mutable vector<T> tree;
	mutable vector<T> lazy;
	mutable vector<bool> update_assign;
	int n;
	int size_;

	template<typename iter>
	T get_ele(iter &begin_, iter &end_)
	{
		if(begin_!=end_)
			return *begin_++;

		cout<<"WARNING: Returning out of range!";
		return *end_;
	}

	template<typename iter>
	void build_tree(iter &begin_, iter &end_, int start,int end, int np)
	{
		if(end == start)
		{
			tree[np] = get_ele(begin_,end_);
			return;
		}
		int mid=mid(start,end);
		build_tree(begin_, end_, start,mid,2*np+1);
		build_tree(begin_, end_, mid+1,end,2*np+2);

		tree[np]=operation::sum<T>()(tree[2*np+1],tree[2*np+2]);
	}
	
	void propagate(int start, int end, int np) const
	{
		if (lazy[np] != 0)
    	{
			if(update_assign[np] == true)
			{
				tree[np] += (end-start+1)*lazy[np];
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[2*np+1] =  true;
					lazy[np*2+2] += lazy[np];
					update_assign[2*np+2] = true;
				}
				lazy[np] = 0;
			}
			else
			{
				tree[np] = (end-start+1)*lazy[np];
				if (start != end)
				{
					lazy[np*2+1] = lazy[np];
					update_assign[2*np+1] =  false;
					lazy[np*2+2] = lazy[np];
					update_assign[2*np+2] =  false;
				}
				update_assign[np] =  true;
				lazy[np] = 0;
			}
  		}
	}

	T query_util(int start,int end,int query_start,int query_end,int np) 
	{
		propagate(start, end, np);

		if(start>query_end or end<query_start)
		{
			return operation::sum<T>().neutral_element;
		}
		if(query_start<=start and query_end>=end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		int left=query_util(start,mid,query_start,query_end,2*np+1);
		int right=query_util(mid+1,end,query_start,query_end,2*np+2);
		return operation::sum<T>()(left,right);
	}
	
	void update_util(int start,int end,int index,int value,int np)
	{
		if(index<start or index>end)
			return;
		
		if(start==end)
		{
			tree[np]=value;
			return;
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			update_util(mid+1,end,index,value,2*np+2);
		}
		else
		{
			update_util(start,mid,index,value,2*np+1);
		}

		tree[np]=operation::sum<T>()(tree[2*np+1],tree[2*np+2]);
	}

	void updateRange_util(int start,int end,int query_start,int query_end,int value,int np)
	{
		propagate(start, end, np);

		if(start>query_end or end<query_start)
			return;
		if (start>=query_start && end<=query_end)
    	{
        	tree[np] += (end-start+1)*value;
        	if (start != end)
        	{
            	lazy[np*2 + 1]   += value;
				update_assign[2*np+1] =  true;
            	lazy[np*2 + 2]   += value;
				update_assign[2*np+2] =  true;
        	}
        	return;
    	}
		int mid=mid(start,end);
		updateRange_util(start,mid,query_start,query_end,value,2*np+1);
		updateRange_util(mid+1,end,query_start,query_end,value,2*np+2);
   		tree[np]=operation::sum<T>()(tree[2*np+1],tree[2*np+2]);
	}
	
	void assignRange_util(int start,int end,int query_start,int query_end,int value,int np)
	{
		propagate(start, end, np);
		
		if(start>query_end or end<query_start)
			return;
		if (start>=query_start && end<=query_end)
    	{
        	tree[np] =  (end-start+1)*value;
        	if (start != end)
        	{
            	lazy[np*2 + 1]  = value;
				update_assign[2*np+1] =  false;
            	lazy[np*2 + 2]  = value;
				update_assign[2*np+2] =  false;
        	}
        	return;
    	}
		int mid=mid(start,end);
		assignRange_util(start,mid,query_start,query_end,value,2*np+1);
		assignRange_util(mid+1,end,query_start,query_end,value,2*np+2);
   		tree[np]=operation::sum<T>()(tree[2*np+1],tree[2*np+2]);	
	}

	int get_neutral_ele() const
	{
		return operation::sum<T>().neutral_element;
	}

	T get_util(int start,int end,int index,int np) const
	{
		propagate(start, end, np);
		
		if(index<start or index>end)
			return operation::sum<T>().neutral_element;
		
		if(start==end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			return get_util(mid+1,end,index,2*np+2);
		}
		
		return get_util(start,mid,index,2*np+1);
	}

	T get(int index) const
	{
		return get_util(0,size_-1,index,0);
	}



	public:
	class iterator: public std::iterator<std::bidirectional_iterator_tag, T>
    {
        private:
        const segment_tree<T,operation::sum<T> > *tree_;
	    int index_;

        public:
        iterator(const segment_tree<T, operation::sum<T> > &tree, int index):tree_(&tree), index_(index)
        { }

		iterator(const iterator& rhs):tree_(rhs.tree_), index_(rhs.index_)
		{ }
		iterator& operator=(const iterator& rhs)
		{
			tree_ = rhs.tree_;
			index_ = rhs.index_;
			return *this;
		}
        iterator& operator++()
        {
            ++index_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }
		iterator& operator--()
        {
            --index_;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp(*this);
            --(*this);
            return temp;
        }
        T operator*()
        {
            return tree_->get(index_);
        }
        bool operator==(const iterator &rhs)
        {
            return index_ == rhs.index_;
        }
        bool operator!=(const iterator &rhs)
        {
            return !(*this == rhs);
        }
		int get_index()
		{
			return index_;
		}
        int operator-(const iterator &rhs)
        {
            return index_ - rhs.index_;
        }
        int operator+(const iterator &rhs)
        {
            return index_ + rhs.index_;
        }
        bool operator<(const iterator &rhs)
        {
        	return **this < **rhs;
        }
    };

	// Default Constructor
	segment_tree() = delete;

	// Parameterized Constructor
	template<typename iter>
	segment_tree(iter begin, iter end)
	{
		size_ = (int) distance(begin, end);
		n = 1;
		while(n < size_){
			n = n*2;
		}
		n = n*2;

		tree.resize(n,get_neutral_ele());
		lazy.resize(n,get_neutral_ele());
		update_assign.resize(n,true);
		build_tree(begin, end, 0, size_-1, 0);
	}

	// Copy Constructor
	segment_tree(const segment_tree<T,operation::sum<T> >& other): size_(other.size_), n(other.n)
	{
		tree = other.tree;
		lazy = other.lazy;
		update_assign = other.update_assign;
	}

	segment_tree(iterator begin, iterator end)
	{
		size_ = end - begin;
		n = 1;
		while(n < size_){
			n = n*2;
		}
		n = n*2;

		tree.resize(n,get_neutral_ele());
		lazy.resize(n,get_neutral_ele());
		update_assign.resize(n,true);
		build_tree(begin, end, 0, size_-1, 0);
	}
	
	// Destructor
	~segment_tree()
	{
		// DO NOTHING
	}
	
	
	T query(int query_start,int query_end) 
	{
		return query_util(0,size_-1,query_start,query_end,0);
	}
	void update(int index,int value)
	{
		return update_util(0,size_-1,index,value,0);
	}

	void updateRange(int query_start,int query_end,int value){
		if(query_start < 0 || query_end > size_ )
			return;
		return updateRange_util(0,size_-1,query_start,query_end,value,0);
	}

	void assignRange(int query_start,int query_end,int value){
		if(query_start < 0 || query_end > size_ )
			return;
		return assignRange_util(0,size_-1,query_start,query_end,value,0);
	}

	int size() const
	{
		return size_;
	}
	bool empty() const
	{
		return size_==0;
	}
	iterator begin() const
	{
		return iterator(*this, 0);
	}
	iterator end() const
	{
		return iterator(*this, size_);
	}
	void display() const
	{
		iterator first = begin();
		iterator last = end();
		while(first!=last)
		{
			cout<<*first<<" ";
			++first;
		}
		cout<<"\n";
	}

	T get_util_WU(int start,int end,int index,int np) const
	{
		
		if(index<start or index>end)
			return operation::sum<T>().neutral_element;
		
		if(start==end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			return get_util_WU(mid+1,end,index,2*np+2);
		}
		
		return get_util_WU(start,mid,index,2*np+1);
	}
	void display_WU() const
	{
		int first = begin().get_index();
		int last = end().get_index();
		while(first!=last){
			cout << get_util_WU(0,size_-1,first,0) << " " ;
			first++;
		}
		cout << "\n";
	}
};
template<typename T>
class segment_tree<T, operation::gcd<T> >
{
	private:
	mutable vector<T> tree;
	mutable vector<T> lazy;
	mutable vector<bool> update_assign;
	int n;
	int size_;

	template<typename iter>
	T get_ele(iter &begin_, iter &end_)
	{
		if(begin_!=end_)
			return *begin_++;

		cout<<"WARNING: Returning out of range!";
		return *end_;
	}

	template<typename iter>
	void build_tree(iter &begin_, iter &end_, int start,int end, int np)
	{
		if(end == start)
		{
			tree[np] = get_ele(begin_,end_);
			return;
		}
		int mid=mid(start,end);
		build_tree(begin_, end_, start,mid,2*np+1);
		build_tree(begin_, end_, mid+1,end,2*np+2);

		tree[np]=operation::gcd<T>()(tree[2*np+1],tree[2*np+2]);
	}
	
	void propagate(int start, int end, int np) const
	{
		if (lazy[np] != 0)
    	{
			if(update_assign[np] == true)
			{
				tree[np] += (end-start+1)*lazy[np];
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[2*np+1] =  true;
					lazy[np*2+2] += lazy[np];
					update_assign[2*np+2] = true;
				}
				lazy[np] = 0;
			}
			else
			{
				tree[np] = (end-start+1)*lazy[np];
				if (start != end)
				{
					lazy[np*2+1] = lazy[np];
					update_assign[2*np+1] =  false;
					lazy[np*2+2] = lazy[np];
					update_assign[2*np+2] =  false;
				}
				update_assign[np] =  true;
				lazy[np] = 0;
			}
  		}
	}

	T query_util(int start,int end,int query_start,int query_end,int np) 
	{
		propagate(start, end, np);

		if(start>query_end or end<query_start)
		{
			return operation::gcd<T>().neutral_element;
		}
		if(query_start<=start and query_end>=end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		int left=query_util(start,mid,query_start,query_end,2*np+1);
		int right=query_util(mid+1,end,query_start,query_end,2*np+2);
		return operation::gcd<T>()(left,right);
	}
	
	void update_util(int start,int end,int index,int value,int np)
	{
		if(index<start or index>end)
			return;
		
		if(start==end)
		{
			tree[np]=value;
			return;
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			update_util(mid+1,end,index,value,2*np+2);
		}
		else
		{
			update_util(start,mid,index,value,2*np+1);
		}

		tree[np]=operation::gcd<T>()(tree[2*np+1],tree[2*np+2]);
	}

	void updateRange_util(int start,int end,int query_start,int query_end,int value,int np)
	{
		propagate(start, end, np);

		if(start>query_end or end<query_start)
			return;
		if (start>=query_start && end<=query_end)
    	{
        	tree[np] += (end-start+1)*value;
        	if (start != end)
        	{
            	lazy[np*2 + 1]   += value;
				update_assign[2*np+1] =  true;
            	lazy[np*2 + 2]   += value;
				update_assign[2*np+2] =  true;
        	}
        	return;
    	}
		int mid=mid(start,end);
		updateRange_util(start,mid,query_start,query_end,value,2*np+1);
		updateRange_util(mid+1,end,query_start,query_end,value,2*np+2);
   		tree[np]=operation::gcd<T>()(tree[2*np+1],tree[2*np+2]);
	}
	
	void assignRange_util(int start,int end,int query_start,int query_end,int value,int np)
	{
		propagate(start, end, np);
		
		if(start>query_end or end<query_start)
			return;
		if (start>=query_start && end<=query_end)
    	{
        	tree[np] =  (end-start+1)*value;
        	if (start != end)
        	{
            	lazy[np*2 + 1]  = value;
				update_assign[2*np+1] =  false;
            	lazy[np*2 + 2]  = value;
				update_assign[2*np+2] =  false;
        	}
        	return;
    	}
		int mid=mid(start,end);
		assignRange_util(start,mid,query_start,query_end,value,2*np+1);
		assignRange_util(mid+1,end,query_start,query_end,value,2*np+2);
   		tree[np]=operation::gcd<T>()(tree[2*np+1],tree[2*np+2]);	
	}

	int get_neutral_ele() const
	{
		return operation::gcd<T>().neutral_element;
	}

	T get_util(int start,int end,int index,int np) const
	{
		propagate(start, end, np);
		
		if(index<start or index>end)
			return operation::gcd<T>().neutral_element;
		
		if(start==end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			return get_util(mid+1,end,index,2*np+2);
		}
		
		return get_util(start,mid,index,2*np+1);
	}

	T get(int index) const
	{
		return get_util(0,size_-1,index,0);
	}



	public:
	class iterator: public std::iterator<std::bidirectional_iterator_tag, T>
    {
        private:
        const segment_tree<T,operation::gcd<T> > *tree_;
	    int index_;

        public:
        iterator(const segment_tree<T, operation::gcd<T> > &tree, int index):tree_(&tree), index_(index)
        { }

		iterator(const iterator& rhs):tree_(rhs.tree_), index_(rhs.index_)
		{ }
		iterator& operator=(const iterator& rhs)
		{
			tree_ = rhs.tree_;
			index_ = rhs.index_;
			return *this;
		}
        iterator& operator++()
        {
            ++index_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++(*this);
            return temp;
        }
		iterator& operator--()
        {
            --index_;
            return *this;
        }
        iterator operator--(int)
        {
            iterator temp(*this);
            --(*this);
            return temp;
        }
        T operator*()
        {
            return tree_->get(index_);
        }
        bool operator==(const iterator &rhs)
        {
            return index_ == rhs.index_;
        }
        bool operator!=(const iterator &rhs)
        {
            return !(*this == rhs);
        }
		int get_index()
		{
			return index_;
		}
        int operator-(const iterator &rhs)
        {
            return index_ - rhs.index_;
        }
        int operator+(const iterator &rhs)
        {
            return index_ + rhs.index_;
        }
    };

	// Default Constructor
	segment_tree() = delete;

	// Parameterized Constructor
	template<typename iter>
	segment_tree(iter begin, iter end)
	{
		size_ = (int) distance(begin, end);
		n = 1;
		while(n < size_){
			n = n*2;
		}
		n = n*2;

		tree.resize(n,get_neutral_ele());
		lazy.resize(n,get_neutral_ele());
		update_assign.resize(n,true);
		build_tree(begin, end, 0, size_-1, 0);
	}

	// Copy Constructor
	segment_tree(const segment_tree<T,operation::gcd<T> >& other): size_(other.size_), n(other.n)
	{
		tree = other.tree;
		lazy = other.lazy;
		update_assign = other.update_assign;
	}

	segment_tree(iterator begin, iterator end)
	{
		size_ = end - begin;
		n = 1;
		while(n < size_){
			n = n*2;
		}
		n = n*2;

		tree.resize(n,get_neutral_ele());
		lazy.resize(n,get_neutral_ele());
		update_assign.resize(n,true);
		build_tree(begin, end, 0, size_-1, 0);
	}
	
	// Destructor
	~segment_tree()
	{
		// DO NOTHING
	}
	
	
	T query(int query_start,int query_end) 
	{
		return query_util(0,size_-1,query_start,query_end,0);
	}
	void update(int index,int value)
	{
		return update_util(0,size_-1,index,value,0);
	}

	void updateRange(int query_start,int query_end,int value){
		if(query_start < 0 || query_end > size_ )
			return;
		return updateRange_util(0,size_-1,query_start,query_end,value,0);
	}

	void assignRange(int query_start,int query_end,int value){
		if(query_start < 0 || query_end > size_ )
			return;
		return assignRange_util(0,size_-1,query_start,query_end,value,0);
	}

	int size() const
	{
		return size_;
	}
	bool empty() const
	{
		return size_==0;
	}
	iterator begin() const
	{
		return iterator(*this, 0);
	}
	iterator end() const
	{
		return iterator(*this, size_);
	}
	void display() const
	{
		iterator first = begin();
		iterator last = end();
		while(first!=last)
		{
			cout<<*first<<" ";
			++first;
		}
		cout<<"\n";
	}
	T get_util_WU(int start,int end,int index,int np) const
	{
		
		if(index<start or index>end)
			return operation::gcd<T>().neutral_element;
		
		if(start==end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			return get_util_WU(mid+1,end,index,2*np+2);
		}
		
		return get_util_WU(start,mid,index,2*np+1);
	}
	void display_WU() const
	{
		int first = begin().get_index();
		int last = end().get_index();
		while(first!=last){
			cout << get_util_WU(0,size_-1,first,0) << " " ;
			first++;
		}
		cout << "\n";
	}
};
#endif