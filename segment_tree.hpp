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
	mutable vector<T> lazy;
	mutable vector<tree_node> tree;
	mutable vector<bool> update_assign;// True if update and false if assign 
	int n;
	int size_;

	// template<typename iter>
	// T find_ele(iter &begin_, iter &end_)
	// {
	// 	if(begin_!=end_)
	// 		return *begin_++;

	// 	cout<<"WARNING: Returning out of range!";
	// 	return *end_;
	// }
	template<typename iter>
	T find_ele(iter begin, int index, input_iterator_tag)
	{
		while(index > 0)
		{
			begin++;
			index--;
		}
		return *begin;
	}
	template<typename iter>
	T find_ele(iter begin, int index, bidirectional_iterator_tag )
	{
		return find_ele(begin, index, std::input_iterator_tag{});
	}
	template<typename iter>
	T find_ele(iter begin, int index, random_access_iterator_tag)
	{
		return *(begin + index);
	}

	template<typename iter>
	void build_tree(iter &begin_, iter &end_, int start,int end, int np)
	{
		

		if(end == start)
		{
			tree[np].value = find_ele(begin_, start, typename iterator_traits<iter>::iterator_category());
			tree[np].index = start;
			// tree[np] = find_ele(begin_,end_);
			return;
		}
		int mid=mid(start,end);
		build_tree(begin_, end_, start,mid,2*np+1);
		build_tree(begin_, end_, mid+1,end,2*np+2);
		tree[np] = pred_t()(tree[2*np+1],tree[2*np+2]);
	}
	
	tree_node query_util(int start,int end,int query_start,int query_end,int np) 
	{
		if (lazy[np] != 0)
    	{ 
			if(update_assign[np] == true){

				tree[np].value += lazy[np];
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[2*np+1] =  true;
					lazy[np*2+2] += lazy[np];
					update_assign[2*np+1] =  true;
				}
	
				lazy[np] = 0;
			}
			else{
				tree[np].value = lazy[np];
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
		if(start>query_end or end<query_start)
		{
			return {pred_t().n_element, -1}; 
		}
		if(query_start<=start and query_end>=end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		tree_node left=query_util(start,mid,query_start,query_end,2*np+1);
		tree_node right=query_util(mid+1,end,query_start,query_end,2*np+2);
		return pred_t()(left,right);
	}
	
	void update_util(int start,int end,int index,int value,int np)
	{
		if(index<start or index>end)
			return;
		
		if(start==end)
		{
			tree[np].value += value;
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

		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	}
	
	void updateRange_util(int start,int end,int query_start,int query_end,int value,int np){
		if (lazy[np] != 0)
		{
			if(update_assign[np] == true){
				tree[np].value += lazy[np];
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[2*np+1] =  true;
					lazy[np*2+2] += lazy[np];
					update_assign[2*np+1] =  true;
				}
	
				lazy[np] = 0;
			}
			else{
				tree[np].value = lazy[np];
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
		 //    tree[np].value += lazy[np];
			// if (start != end)
			// {
		 //    	lazy[np*2 + 1]  += lazy[np];
			// 	update_assign[2*np+1] =  true;
		 //    	lazy[np*2 + 2]  += +lazy[np];
			// 	update_assign[2*np+2] =  true;
			// }
			// update_assign[np] =  true;
			// lazy[np] = 0;
		}
		if(start>query_end or end<query_start)
			return;
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


	void assignRange_util(int start,int end,int query_start,int query_end,int value,int np){
		if (lazy[np] != 0)
		{
			if(update_assign[np] == true){
				tree[np].value += lazy[np];
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[2*np+1] =  true;
					lazy[np*2+2] += lazy[np];
					update_assign[2*np+1] =  true;
				}
	
				lazy[np] = 0;
			}
			else{
				tree[np].value = lazy[np];
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
		 //    tree[np].value = lazy[np];
			// if (start != end)
			// {
		 //    	lazy[np*2 + 1]  = lazy[np];
			// 	update_assign[2*np+1] =  false;
		 //    	lazy[np*2 + 2]  = lazy[np];
			// 	update_assign[2*np+2] =  false;
			// }
			// update_assign[np] =  true;
			// lazy[np] = 0;
		}
		if(start>query_end or end<query_start)
			return;
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

	T get_neutral_ele()
	{
		return pred_t().n_element;
	}

	T get_util(int start,int end,int index,int np) const
	{
		if (lazy[np] != 0)
    	{
			if(update_assign[np] == true){

				tree[np].value += lazy[np];
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[np*2+1] = true;
					lazy[np*2+2] += lazy[np];
					update_assign[np*2+2] = true;
				}
	
				lazy[np] = 0;
			}
			else{
				tree[np].value = lazy[np];
				if (start != end)
				{
					lazy[np*2+1] = lazy[np];
					update_assign[np*2+1] = false;
					lazy[np*2+2] = lazy[np];
					update_assign[np*2+2] = false;
				}
	
				lazy[np] = 0;
				update_assign[np] = true;
			}
  		}
		
		
		if(index<start or index>end)
			return pred_t().n_element;
		
		if(start==end)
		{
			return tree[np].value;
		}
		int mid=mid(start,end);
		if(index>mid)
		{
			return get_util(mid+1,end,index,2*np+2);
		}
		else 
		{
			return get_util(start,mid,index,2*np+1);
		}

		// Apply operations
		// tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	}

	T get(int index) const
	{
		return get_util(0,size_-1,index,0);
	}

	public:
	class iterator: public std::iterator<std::input_iterator_tag, T>
    {
        private:
        const segment_tree<T, pred_t> *tree_;
	    int index_;

        public:
        // Iterator(tree_node_t t):value(t.value), index(t.index) 
        iterator(const segment_tree<T, pred_t> &tree, int index):tree_(&tree), index_(index)
        { }

		iterator(const iterator& rhs):tree_(rhs.tree_), index_(rhs.index_)
		{
			// tree_ = rhs.tree_;
			// index_ = rhs.index_;
		}
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
        T operator*()
        {
            // return *ptr_;
			// int  x = index_;
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

        // int operator-(const Iterator &rhs)
        // {
        //     return ptr_ - rhs.ptr_;
        // }
        // int operator+(const Iterator &rhs)
        // {
        //     return ptr_ + rhs.ptr_;
        // }
    };

	// Default Constructor
	segment_tree() = delete;

	// Parameterized Constructor
	template<typename iter>
	segment_tree(iter begin, iter end)
	{
		size_ = (int)distance(begin, end);
		n = 1;
		while(n < size_){
			n = n*2;
		}
		n = n*2;

		tree.resize(n);
		lazy.resize(n,0);
		update_assign.resize(n,true);
		for(int i=0;i<n;++i)
		{
			tree[i] = {get_neutral_ele() , -1};
		}
		build_tree(begin, end, 0, size_-1, 0);
	}
	
	// Copy Constructor - TODO
	segment_tree(iterator begin, iterator end)
	{
		// DO SOMETHING THAT WORKS
	}
	
	// Destructor
	~segment_tree()
	{
		// DO NOTHING
	}
	
	
	iterator query(int query_start,int query_end) 
	{
		tree_node t = query_util(0,size_-1,query_start,query_end,0);
		return iterator(*this, t.index);
	}
	void update(int index,int value)
	{
		return update_util(0,size_-1,index,value,0);
	}

	void updateRange(int query_start,int query_end,int value){
		return updateRange_util(0,size_-1,query_start,query_end,value,0);
	}

	void assignRange(int query_start,int query_end,int value){
		return assignRange_util(0,size_-1,query_start,query_end,value,0);
	}

	int size() const
	{
		return size_;
	}
	bool empty() const
	{
		return size==0;
	}
	iterator begin()
	{
		return iterator(*this, 0);
	}
	iterator end()
	{
		return iterator(*this, size_);
	}
	void display()
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
};

template<typename T>
class segment_tree<T, operation::sum<T> >
{
	private:
	vector<T> tree;
	vector<T> lazy;
	vector<bool> update_assign;
	int n;
	int size_;

	// template<typename iter>
	// T find_ele(iter &begin_, iter &end_)
	// {
	// 	if(begin_!=end_)
	// 		return *begin_++;
	// 	cout<<"WARNING: Returning out of range!";
	// 	return *end_;
	// }
	template<typename iter>
	T find_ele(iter begin, int index, input_iterator_tag)
	{
		while(index > 0)
		{
			begin++;
			index--;
		}
		return *begin;
	}
	template<typename iter>
	T find_ele(iter begin, int index, bidirectional_iterator_tag )
	{
		return find_ele(begin, index, std::input_iterator_tag{});
	}
	template<typename iter>
	T find_ele(iter begin, int index, random_access_iterator_tag)
	{
		return *(begin + index);
	}

	template<typename iter>
	void build_tree(iter &begin_, iter &end_, int start,int end, int np)
	{
		if(end == start)
		{
			tree[np] = find_ele(begin_, start, typename iterator_traits<iter>::iterator_category());
			// tree[np] = find_ele(begin_,end_);
			return;
		}
		int mid=mid(start,end);
		build_tree(begin_, end_, start,mid,2*np+1);
		build_tree(begin_, end_, mid+1,end,2*np+2);

		tree[np]=operation::sum<T>()(tree[2*np+1],tree[2*np+2]);
	}
	
	T query_util(int start,int end,int query_start,int query_end,int np) 
	{

		if (lazy[np] != 0)
    	{
			if(update_assign[np] == true){

				tree[np] +=  (end-start+1)*lazy[np];
				if (start != end)
				{
					lazy[np*2+1] += lazy[np];
					update_assign[2*np+1] =  true;
					lazy[np*2+2] += lazy[np];
					update_assign[2*np+2] = true;
				}
				lazy[np] = 0;
			}
			else{
				tree[np] =  (end-start+1)*lazy[np];
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
		if(start>query_end or end<query_start)
		{
			return operation::sum<T>().n_element;
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

	void updateRange_util(int start,int end,int query_start,int query_end,int value,int np){
		if (lazy[np] != 0)
    	{
    		if(update_assign[np] == true){

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
			else{
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
	  //       tree[np] += (end-start+1)*lazy[np];
   //      	if (start != end)
   //  		{
   //          	lazy[np*2 + 1]   += lazy[np];
			// 	update_assign[2*np+1] =  true;
   //          	lazy[np*2 + 2]   += lazy[np];
			// 	update_assign[2*np+2] =  true;
  	//     	}
			// update_assign[np] =  true;
   //      	lazy[np] = 0;
    	}
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
	
	void assignRange_util(int start,int end,int query_start,int query_end,int value,int np){
		if (lazy[np] != 0)
		{
			if(update_assign[np] == true){
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
			else{
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
		 //    tree[np] =  (end-start+1)*lazy[np];
			// if (start != end)
			// {
		 //    	lazy[np*2 + 1]  = lazy[np];
			// 	update_assign[2*np+1] =  false;
		 //    	lazy[np*2 + 2]  = lazy[np];
			// 	update_assign[2*np+2] =  false;
			// }
			// update_assign[np] = true;
			// lazy[np] = 0;
		}
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

	int get_neutral_ele()
	{
		return operation::sum<T>().n_element;
	}

	public:
	// Default Constructor
	segment_tree() = delete;

	// Parameterized Constructor
	template<typename iter>
	segment_tree(iter begin, iter end)
	{
		cout<<"Specialized class\n";
		size_ =  (int)distance(begin, end);
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



	// Copy Constructor - TODO
	segment_tree(const segment_tree<T,operation::sum<T> >& other): size_(other.size_), n(other.n)
	{
		// DO SOMETHING THAT WORKS
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

	//range update
	void updateRange(int query_start,int query_end,int value){
		return updateRange_util(0,size_-1,query_start,query_end,value,0);
	}

	void assignRange(int query_start,int query_end,int value){
		return assignRange_util(0,size_-1,query_start,query_end,value,0);
	}

	T operator[](int index) const
	{
		return query(index,index);
	}
	void display()
	{
		for(int i=0;i<n;i++)
		{
			cout << tree[i] <<"  "; 
		}
		cout << "\n";
	}
	int size() const
	{
		return size_;
	}
	bool empty()
	{
		return size==0;
	}
};

#endif