#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <iostream>
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
	T *tree;
	int n;
	int size;
	
	void build_tree(iter begin,T *tree,int start,int end, int np)
	{
		if(end - start == 1)
		{
			tree[np] = find_ele(begin, start,typename iterator_traits<iter>::iterator_category());
			return;
		}
		int mid=mid(start,end);
		build_tree(begin,tree,start,mid,2*np+1);
		build_tree(begin,tree,mid,end,2*np+2);

		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	}
	T query_util(T *tree ,int start,int end,int query_start,int query_end,int np)
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
		int left=query_util(tree,start,mid,query_start,query_end,2*np+1);
		int right=query_util(tree,mid+1,end,query_start,query_end,2*np+2);
		return pred_t()(left,right);
	}
	void update_util(T *tree,int start,int end,int index,int value,int np)
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
			update_util(tree,mid+1,end,index,value,2*np+2);
		}
		else
		{
			update_util(tree,start,mid,index,value,2*np+1);
		}

		tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	}

	int find_size(iter begin, iter end, input_iterator_tag)
	{
		int i=0;
		while(begin != end)
		{
			i++;
			begin++;
		}
		return i;
	}
	int find_size(iter begin, iter end, bidirectional_iterator_tag )
	{
		return find_size(begin, end, std::input_iterator_tag{});
	}
	int find_size(iter begin, iter end, random_access_iterator_tag)
	{
		return end - begin;
	}
	
	T find_ele(iter begin, int index, input_iterator_tag)
	{
		while(index > 0)
		{
			begin++;
			index--;
		}
		return *begin;
	}
	T find_ele(iter begin, int index, bidirectional_iterator_tag )
	{
		return find_ele(begin, index, std::input_iterator_tag{});
	}
	T find_ele(iter begin, int index, random_access_iterator_tag)
	{
		return *(begin + index);
	}
	

	public:
	segment_tree(iter begin, iter end)
	{
		size =  find_size(begin, end, typename iterator_traits<iter>::iterator_category());
		n = 1;
		while(n < size){
			n = n*2;
		}
		n = n*2;
	
		tree =  new int[n];
		build_tree(begin,tree, 0 , size,  0);
	}
	~segment_tree()
	{
		delete [] tree;
	}
	T query(int query_start,int query_end)
	{
		return query_util(this->tree,0,size-1,query_start,query_end,0);
	}
	void update(int index,int value)
	{
		return update_util(this->tree,0,size-1,index,value,0);
	}
	T operator[](int index)
	{
		return query(index,index);
	}
	void display()
	{
		for(int i=0;i<n;i++)
		{
			cout << *(tree+i) <<"  "; 
		}
		cout << "\n";
	}
};

#endif