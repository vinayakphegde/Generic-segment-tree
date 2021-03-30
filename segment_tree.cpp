#include<bits/stdc++.h>
#define mid(l,r) (l+(r-l)/2)
using namespace std;


template<typename T>
class minimum
{
	public:
	T operator() (T lhs,T rhs) const {
		return (lhs<rhs) ? lhs : rhs;
	}
};

template<typename T>
class maximum
{
	public:
	T operator()(const T lhs,const T rhs) const 
	{
		return (lhs>rhs) ? lhs : rhs;
	}
};

template<typename T>
class summation
{
	public:
	T operator()(const T lhs,const T rhs) const 
	{
		return lhs+rhs;
	}
};


template<typename T,typename pred_t>
class segment_tree
{
	private:
	T *tree;
	int n;
	
	void build_tree(const vector<T>&,T *tree,int start,int end,int np);
	T query_util(T *tree ,int start,int end,int query_start,int query_end,int np);
	void update_util(T *tree,int start,int end,int index,int value,int np);
	
	public:
	segment_tree(const vector<T>&);
	~segment_tree();
	T query(int query_start,int query_end);
	void update(int index,int value);
	T operator[](int index);
};

template<typename T,typename pred_t>
segment_tree<T,pred_t>::segment_tree(const vector<T> &v) : tree(new T[4*(v.size())] ) , n(v.size())
{
	build_tree(v,tree,0,n-1,0);
}

template<typename T,typename pred_t>
segment_tree<T,pred_t>::~segment_tree()
{
	delete [] tree; 
}


template<typename T,typename pred_t>
T segment_tree<T,pred_t>::query(int query_start,int query_end)
{
	return query_util(this->tree,0,n-1,query_start,query_end,0);
}

template<typename T,typename pred_t>
void segment_tree<T,pred_t>::update(int index,int value)
{
	return update_util(this->tree,0,n-1,index,value,0);
}

template<typename T,typename pred_t>
void segment_tree<T,pred_t>::build_tree(const vector<T> &A,T *tree,int start,int end,int np)
{
	if(start==end)
	{
		tree[np]=A[start];
		return;
	}
	int mid=mid(start,end);
	build_tree(A,tree,start,mid,2*np+1);
	build_tree(A,tree,mid+1,end,2*np+2);
	tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
}

template<typename T,typename pred_t>
T segment_tree<T,pred_t>::query_util(T *tree,int start,int end,int query_start,int query_end,int np)
{
	if(start>query_end or end<query_start)
	{
		return 0;
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

template<typename T,typename pred_t>
void segment_tree<T,pred_t>::update_util(T *tree,int start,int end,int index,int value,int np)
{
	if(index<start or index>end)
	{
		return;
	}
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

template<typename T,typename pred_t>
T segment_tree<T,pred_t>::operator[](int index)
{
	return query(index,index);
}

int main()
{
	int n;
	n=8;
  vector<int> v{1,2,3,4,5,6,7,8};
	int sum=0;
	segment_tree<int,summation<int>> tree1(v);
	cout << tree1[1] << endl;
	return 0;	
}
