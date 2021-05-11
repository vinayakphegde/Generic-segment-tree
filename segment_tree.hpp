#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <iostream>
using namespace std;

#include "operation.hpp"
#include "iterator.hpp"
#include "utils.hpp"

#define mid(l,r) (l+(r-l)/2)

template<typename T,typename pred_t>
class segment_tree
{
	private:
	/**
	 * Stores the values to be propagated 
	*/
	mutable vector<T> lazy_;
	
	/** 
	 * Stores the tree nodes
	*/
	mutable vector<tree_node<T> > tree_;
	
	/** 
	 * Boolean value used to check if the operation to be performed at a given node 
	 * is addition or assignment.
	 * Set to true if the operation to be performed is addition and false otherwise
	*/
	mutable vector<bool> is_addition_;
	
	int n_;
	int size_;

	/**
	 * @brief Returns the elements one by one from the container passed to build a segment tree.
	*/
	template<typename iter>
	T get_ele(iter &begin, iter &end)
	{
		if(begin!=end)
			return *begin++;

		cout<<"WARNING: Returning out of range!";
		return *end;
	}

	/** 
	 * @brief Builds a segment tree recursively
	*/
	template<typename iter>
	void build_tree(iter &begin, iter &end, int left, int right, int np)
	{
		if(right == left)
		{
			tree_[np].value = get_ele(begin,end);
			tree_[np].index = left;
			return;
		}

		int mid=mid(left,right);
		build_tree(begin, end, left, mid, 2*np+1);
		build_tree(begin, end, mid+1, right, 2*np+2);
		
		tree_[np] = pred_t()(tree_[2*np+1],tree_[2*np+2]);
	}
	
	/** 
	 * @brief Propagates lazy value of the current node to its children 
	 * if the current node is not a leaf node
	*/  
	void propagate(int left, int right, int np) const
	{
		if (lazy_[np] != 0)
    	{ 
    		// Perform addition operation
			if(is_addition_[np] == true)
			{
				tree_[np].value += lazy_[np];
				if (left != right)
				{
					lazy_[np*2+1] += lazy_[np];
					is_addition_[2*np+1] =  true;
					lazy_[np*2+2] += lazy_[np];
					is_addition_[2*np+1] =  true;
				}
	
				lazy_[np] = 0;
			}
			// Perform Assignment operation 
			else
			{
				tree_[np].value = lazy_[np];
				if (left != right)
				{
					lazy_[np*2+1] = lazy_[np];
					is_addition_[2*np+1] =  false;
					lazy_[np*2+2] = lazy_[np];
					is_addition_[2*np+1] =  false;
				}

				is_addition_[np] =  true;
				lazy_[np] = 0;
			}
  		}
	}
	
	/** 
	 * @brief 	Util function to find the minimum or maximum element within the given range
	 * @param 	left 		Leftmost index of the range covered by the current node 
	 * @param 	right		Rightmost index of the range covered by the current node
	 * @param	query_left	Leftmost index of the query range 
	 * @param	query_right	Rightmost index of the query range
	 * @param 	np			Index of the current node
	*/
	tree_node<T> query_util(int left,int right,int query_left,int query_right,int np)
	{
		propagate(left, right, np);

		// If the node does not cover anything in the given range
		if(left>query_right or right<query_left)
		{
			return {pred_t().NEUTRAL_ELEMENT, -1}; 
		}

		// If the node covers the given range
		if(query_left<=left and query_right>=right)
		{
			return tree_[np];
		}

		int mid=mid(left,right);
		tree_node<T> left_ans=query_util(left,mid,query_left,query_right,2*np+1);
		tree_node<T> right_ans=query_util(mid+1,right,query_left,query_right,2*np+2);
		return pred_t()(left_ans,right_ans);
	}
	
	/** 
	 * @brief 	Util function to assign the value at a given index
	 * @param 	left 		Leftmost index of the range covered by the current node 
	 * @param 	right		Rightmost index of the range covered by the current node 
	 * @param	index		Index of the element to be updated
	 * @param 	value		New value to be assigned to the element at a given index
	 * @param 	np			Index of the current node
	*/
	void update_util(int left,int right,int index,int value,int np)
	{
		if(index<left or index>right)
			return;
		
		if(left==right)
		{
			tree_[np].value += value;
			return;
		}

		int mid=mid(left,right);
		if(index>mid)
		{
			update_util(mid+1,right,index,value,2*np+2);
		}
		else
		{
			update_util(left,mid,index,value,2*np+1);
		}

		tree_[np]=pred_t()(tree_[2*np+1],tree_[2*np+2]);
	}
	
	/**
	 * @brief 	Util function to assign the given value to the given range of indices
	 * @param 	left 		Leftmost index of the range covered by the current node 
	 * @param 	right		Rightmost index of the range covered by the current node
	 * @param	query_left	Leftmost index of the query range 
	 * @param	query_right	Rightmost index of the query range
	 * @param 	value		New value to be added to the given range of indices
	 * @param 	np			Index of the current node
	*/
	void update_util(int left,int right,int query_left,int query_right,int value,int np)
	{
		propagate(left, right, np);
		
		if(left>query_right or right<query_left)
			return;

		if (left>=query_left && right<=query_right)
    	{
        	tree_[np].value = value;
        	if (left != right)
        	{
            	lazy_[np*2 + 1]  = value;
				is_addition_[2*np+1] =  false;
            	lazy_[np*2 + 2]  = value;
				is_addition_[2*np+2] =  false;
        	}
        	return;
    	}

		int mid=mid(left,right);
		update_util(left,mid,query_left,query_right,value,2*np+1);
		update_util(mid+1,right,query_left,query_right,value,2*np+2);
   		tree_[np]=pred_t()(tree_[2*np+1],tree_[2*np+2]);	
	}

	/** 
	 * @brief 	Util function to add the given value to the given range of indices
	 * @param 	left 		Leftmost index of the range covered by the current node 
	 * @param 	right		Rightmost index of the range covered by the current node
	 * @param	query_left	Leftmost index of the query range 
	 * @param	query_right	Rightmost index of the query range
	 * @param 	value		New value to be added to the given range of indices
	 * @param 	np			Index of the current node
	*/
	void add_util(int left,int right,int query_left,int query_right,int value,int np)
	{
		propagate(left, right, np);
			
		if(left>query_right or right<query_left)
			return;

		if (left>=query_left && right<=query_right)
    	{
        	tree_[np].value += value;
        	if (left != right)
        	{
            	lazy_[np*2 + 1]  += value;
				is_addition_[2*np+1] =  true;
            	lazy_[np*2 + 2]  += value;
				is_addition_[2*np+2] =  true;
        	}
        	return;
    	}

		int mid=mid(left,right);
		add_util(left,mid,query_left,query_right,value,2*np+1);
		add_util(mid+1,right,query_left,query_right,value,2*np+2);
   		tree_[np]=pred_t()(tree_[2*np+1],tree_[2*np+2]);	
	}

	/**
	 * @brief 	Util function to get the value of the element at the given index
	 * @param 	left 		Leftmost index of the range covered by the current node 
	 * @param 	right		Rightmost index of the range covered by the current node
	 * @param	index		Index of the element to be returned 
	 * @param 	np			Index of the current node
	*/
	T get_util(int left,int right,int index,int np) const
	{
		propagate(left, right, np);
		
		if(index<left or index>right)
		{
			return pred_t().NEUTRAL_ELEMENT;
		}

		if(left==right)
		{
			return tree_[np].value;
		}

		int mid=mid(left,right);
		if(index>mid)
		{
			return get_util(mid+1,right,index,2*np+2);
		}
		
		return get_util(left,mid,index,2*np+1);
	}

	/** 
	 * @brief 	Returns the value of the element at the given index
	 * @param	index		Index of the element to be returned 
	*/
	T get(int index) const
	{
		return get_util(0,size_-1,index,0);
	}


	public:
	template<typename T1, typename pred_t1>
	friend class seg_tree::iterator;

	typedef seg_tree::iterator<T, pred_t> iterator;

	// Default Constructor
	segment_tree() = delete;

	/** 
	 * @brief 	Constructs a segment tree using a pair of iterators of a container
	*/
	template<typename iter>
	segment_tree(iter begin, iter end)
	{
		size_ = (int)distance(begin, end);
		n_ = calculate_n(size_);

		tree_.resize(n_,{pred_t().NEUTRAL_ELEMENT , -1});
		lazy_.resize(n_,0);
		is_addition_.resize(n_,true);

		if(n_>0)
			build_tree(begin, end, 0, size_-1, 0);
	}
	
	/** 
	 * @brief 	Constructs a segment tree using another segment tree
	*/
	segment_tree(const segment_tree<T, pred_t> &other): size_(other.size_), n_(other.n_)
	{
		tree_ = other.tree_;
		lazy_ = other.lazy_;
		is_addition_ = other.is_addition_;
	}
	
	/** 
	 * @brief 	Constructs a segment tree using a pair of iterators of another segment tree
	*/
	segment_tree(iterator begin, iterator end)
	{
		size_ = end - begin;
		n_ = calculate_n(size_);

		tree_.resize(n_,{pred_t().NEUTRAL_ELEMENT , -1});
		lazy_.resize(n_,0);
		is_addition_.resize(n_,true);
		
		if(n_>0)
			build_tree(begin, end, 0, size_-1, 0);
	}

	// Destructor
	~segment_tree()
	{
		// DO NOTHING
	}
	
	/** 
	 * @brief	Finds the minimum or maximum element within the given range
	 * @param	query_left	Leftmost index of the query range 
	 * @param	query_right	Rightmost index of the query range
	*/
	iterator query(int query_left,int query_right) 
	{
		if(!isValid(query_left,query_right, size_))
			return end();

		tree_node<T> t = query_util(0,size_-1,query_left,query_right,0);
		return iterator(*this, t.index);
	}

	/** 
	 * @brief	Assigns the given value to the given index
	 * @param	index		Index of the element to be updated
	 * @param 	value		New value to be assigned to the element at a given index
	*/
	void update(int index,int value)
	{
		if(!isValid(index, size_))
			return;

		return update_util(0,size_-1,index,value,0);
	}

	/** 
	 * @brief 	Assigns the given value to the given range of indices
	 * @param	query_left	Leftmost index of the query range 
	 * @param	query_right	Rightmost index of the query range
	 * @param 	value		New value to be assigned to the given range of indices
	*/
	void update(int query_left,int query_right,int value){
		if(!isValid(query_left, query_right, size_))
			return;

		return update_util(0,size_-1,query_left,query_right,value,0);
	}

	/** 
	 * @brief 	Adds the given value to the given range of indices 
	 * @param	query_left	Leftmost index of the query range 
	 * @param	query_right	Rightmost index of the query range
	 * @param 	value		New value to be added to the given range of indices
	*/
	void add(int query_left,int query_right,int value){

		if(!isValid(query_left,query_right, size_))
			return;
		
		return add_util(0,size_-1,query_left,query_right,value,0);
	}

	/** 
	 * @brief Displays the elements of the segment tree
	*/
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

	/** 
	 * @brief Returns the number of elements present in the segment tree
	*/
	int size() const
	{
		return size_;
	}
	
	/** 
	 * @brief Returns true if the segment tree is empty
	*/
	bool empty() const
	{
		return size_==0;
	}
	
	/** 
	 * @brief Returns an iterator that refers to the first element of the segment tree
	*/
	iterator begin() const
	{
		return iterator(*this, 0);
	}
	
	/** 
	 * @brief Returns an iterator that refers to one past the last element of the segment tree
	*/
	iterator end() const
	{
		return iterator(*this, size_);
	}

};


template<typename T>
class segment_tree<T, operation::sum<T> >
{
	private:
	mutable vector<T> tree_;
	mutable vector<T> lazy_;
	mutable vector<bool> is_addition_;
	int n_;
	int size_;

	template<typename iter>
	T get_ele(iter &begin, iter &end)
	{
		if(begin!=end)
			return *begin++;

		cout<<"WARNING: Returning out of range!";
		return *end;
	}

	template<typename iter>
	void build_tree(iter &begin, iter &end, int left,int right, int np)
	{
		if(right == left)
		{
			tree_[np] = get_ele(begin,end);
			return;
		}
		int mid=mid(left,right);
		build_tree(begin, end, left, mid, 2*np+1);
		build_tree(begin, end, mid+1, right, 2*np+2);

		tree_[np]=operation::sum<T>()(tree_[2*np+1],tree_[2*np+2]);
	}
	
	void propagate(int left, int right, int np) const
	{
		if (lazy_[np] != 0)
    	{
			if(is_addition_[np] == true)
			{
				tree_[np] += (right-left+1)*lazy_[np];
				if (left != right)
				{
					lazy_[np*2+1] += lazy_[np];
					is_addition_[2*np+1] =  true;
					lazy_[np*2+2] += lazy_[np];
					is_addition_[2*np+2] = true;
				}
				lazy_[np] = 0;
			}
			else
			{
				tree_[np] = (right-left+1)*lazy_[np];
				if (left != right)
				{
					lazy_[np*2+1] = lazy_[np];
					is_addition_[2*np+1] =  false;
					lazy_[np*2+2] = lazy_[np];
					is_addition_[2*np+2] =  false;
				}
				is_addition_[np] =  true;
				lazy_[np] = 0;
			}
  		}
	}

	T query_util(int left,int right,int query_left,int query_right,int np) 
	{
		propagate(left, right, np);

		if(left>query_right or right<query_left)
		{
			return operation::sum<T>().NEUTRAL_ELEMENT;
		}
		if(query_left<=left and query_right>=right)
		{
			return tree_[np];
		}
		int mid=mid(left,right);
		int left_ans=query_util(left,mid,query_left,query_right,2*np+1);
		int right_ans=query_util(mid+1,right,query_left,query_right,2*np+2);
		return operation::sum<T>()(left_ans,right_ans);
	}
	
	void update_util(int left,int right,int index,int value,int np)
	{
		if(index<left or index>right)
			return;
		
		if(left==right)
		{
			tree_[np]=value;
			return;
		}
		int mid=mid(left,right);
		if(index>mid)
		{
			update_util(mid+1,right,index,value,2*np+2);
		}
		else
		{
			update_util(left,mid,index,value,2*np+1);
		}

		tree_[np]=operation::sum<T>()(tree_[2*np+1],tree_[2*np+2]);
	}

	void update_util(int left,int right,int query_left,int query_right,int value,int np)
	{
		propagate(left, right, np);
		
		if(left>query_right or right<query_left)
			return;
		if (left>=query_left && right<=query_right)
    	{
        	tree_[np] = (right-left+1)*value;
        	if (left != right)
        	{
            	lazy_[np*2 + 1]  = value;
				is_addition_[2*np+1] =  false;
            	lazy_[np*2 + 2]  = value;
				is_addition_[2*np+2] =  false;
        	}
        	return;
    	}
		int mid=mid(left,right);
		update_util(left,mid,query_left,query_right,value,2*np+1);
		update_util(mid+1,right,query_left,query_right,value,2*np+2);
   		tree_[np]=operation::sum<T>()(tree_[2*np+1],tree_[2*np+2]);	
	}

	void add_util(int left,int right,int query_left,int query_right,int value,int np)
	{
		propagate(left, right, np);

		if(left>query_right or right<query_left)
			return;
		if (left>=query_left && right<=query_right)
    	{
        	tree_[np] += (right-left+1)*value;
        	if (left != right)
        	{
            	lazy_[np*2 + 1]   += value;
				is_addition_[2*np+1] =  true;
            	lazy_[np*2 + 2]   += value;
				is_addition_[2*np+2] =  true;
        	}
        	return;
    	}
		int mid=mid(left,right);
		add_util(left,mid,query_left,query_right,value,2*np+1);
		add_util(mid+1,right,query_left,query_right,value,2*np+2);
   		tree_[np]=operation::sum<T>()(tree_[2*np+1],tree_[2*np+2]);
	}
	
	int get_neutral_ele() const
	{
		return operation::sum<T>().NEUTRAL_ELEMENT;
	}

	T get_util(int left,int right,int index,int np) const
	{
		propagate(left, right, np);
		
		if(index<left or index>right)
			return operation::sum<T>().NEUTRAL_ELEMENT;
		
		if(left==right)
		{
			return tree_[np];
		}
		int mid=mid(left,right);
		if(index>mid)
		{
			return get_util(mid+1,right,index,2*np+2);
		}
		
		return get_util(left,mid,index,2*np+1);
	}

	T get(int index) const
	{
		return get_util(0,size_-1,index,0);
	}


	public:
	template<typename T1>
	friend class seg_tree::iterator;

	typedef seg_tree::iterator<T, operation::sum<T> > iterator;

	// Default Constructor
	segment_tree() = delete;

	// Parameterized Constructor
	template<typename iter>
	segment_tree(iter begin, iter end)
	{
		size_ = (int) distance(begin, end);
		n_ = calculate_n(size_);

		tree_.resize(n_,get_neutral_ele());
		lazy_.resize(n_,get_neutral_ele());
		is_addition_.resize(n_,true);
		build_tree(begin, end, 0, size_-1, 0);
	}

	// Copy Constructor
	segment_tree(const segment_tree<T,operation::sum<T> >& other): size_(other.size_), n_(other.n_)
	{
		tree_ = other.tree_;
		lazy_ = other.lazy_;
		is_addition_ = other.is_addition_;
	}

	segment_tree(iterator begin, iterator end)
	{
		size_ = end - begin;
		n_ = calculate_n(size_);

		tree_.resize(n_,get_neutral_ele());
		lazy_.resize(n_,get_neutral_ele());
		is_addition_.resize(n_,true);
		build_tree(begin, end, 0, size_-1, 0);
	}
	
	// Destructor
	~segment_tree()
	{
		// DO NOTHING
	}
	
	
	T query(int query_left,int query_right) 
	{
		return query_util(0,size_-1,query_left,query_right,0);
	}
	
	void update(int index,int value)
	{
		if(!isValid(index, size_))
			return;

		return update_util(0,size_-1,index,value,0);
	}

	void update(int query_left,int query_right,int value)
	{
		if(!isValid(query_left,query_right, size_))
			return;

		return update_util(0,size_-1,query_left,query_right,value,0);
	}

	void add(int query_left,int query_right,int value)
	{
		if(!isValid(query_left,query_right, size_))
			return;

		return add_util(0,size_-1,query_left,query_right,value,0);
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
	
};
#endif