#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <bits/stdc++.h>
#include <iterator>
#include <typeinfo>
using namespace std;

#define mid(l,r) (l+(r-l)/2)

namespace operation 
{
	template<typename T>
	class min
	{
		public:
		static const int n_element = INT_MAX;
		T operator() (T lhs,T rhs) const {
			return (lhs<rhs) ? lhs : rhs;
		}
	};

	template<typename T>
	class max
	{
		public:
		static const int n_element = INT_MIN;
		T operator()(const T lhs,const T rhs) const 
		{
			return (lhs>rhs) ? lhs : rhs;
		}
	};

	template<typename T>
	class sum
	{
		public:
		static const int n_element = 0;
		T operator()(const T lhs,const T rhs) const 
		{
			return lhs+rhs;
		}
	};

	template<typename T>
	class gcd
	{
		public:
		static const int n_element = 0;
		T operator()(const T lhs,const T rhs) const 
		{
			return __gcd(lhs,rhs);
		}
	};

}

template<typename T,typename pred_t,typename iter>
class segment_tree
{
	private:
	vector<T> tree;
	int n;
	int size_;

	// DO NOT USE THIS VARIABLE ANYWHERE except in get_ele()
	iter begin_;
	iter end_;

	int find_size(iter begin, iter end, input_iterator_tag) const
	{
		int i=0;
		while(begin != end)
		{
			i++;
			begin++;
		}
		return i;
	}
	int find_size(iter begin, iter end, bidirectional_iterator_tag ) const
	{
		return find_size(begin, end, std::input_iterator_tag{});
	}
	int find_size(iter begin, iter end, random_access_iterator_tag) const
	{
		return end - begin;
	}
	
	T get_ele()
	{
		if(begin_!=end_)
			return *begin_++;

		cout<<"WARNING: Returning out of range!";
		return *end_;
	}
	void build_tree(int start,int end, int np)
	{
		if(end - start == 1)
		{
			tree[np] = get_ele();
			return;
		}
		int mid=mid(start,end);
		build_tree(start,mid,2*np+1);
		build_tree(mid,end,2*np+2);

		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	}
	T query_util(int start,int end,int query_start,int query_end,int np) const
	{
		if(start>query_end or end<query_start)
		{
			return pred_t().n_element;
		}
		if(query_start<=start and query_end>=end)
		{
			return tree[np];
		}
		int mid=mid(start,end);
		int left=query_util(start,mid,query_start,query_end,2*np+1);
		int right=query_util(mid+1,end,query_start,query_end,2*np+2);
		return pred_t()(left,right);
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

		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	}
	

	public:
	// Default Constructor
	segment_tree() = delete;
	// Parameterized Constructor
	segment_tree(iter begin, iter end): begin_(begin), end_(end)
	{
		size_ =  find_size(begin, end, typename iterator_traits<iter>::iterator_category());
		n = 1;
		while(n <= size_){
			n = n*2;
		}
	
		tree.resize(n,0);
		build_tree(0, size_, 0);
	}
	// Copy Constructor - TODO
	segment_tree(const segment_tree<T,pred_t,iter>& other): size_(other.size_), n(other.n)
	{
		// DO SOMETHING THAT WORKS
	}
	// Destructor
	~segment_tree()
	{
		// DO NOTHING
	}
	
	
	T query(int query_start,int query_end) const
	{
		return query_util(0,size_-1,query_start,query_end,0);
	}
	void update(int index,int value)
	{
		return update_util(0,size_-1,index,value,0);
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