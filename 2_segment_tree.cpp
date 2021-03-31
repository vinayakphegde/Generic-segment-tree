#include <bits/stdc++.h>
using namespace std;

#define mid(l,r) (l+(r-l)/2)

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

template<typename T>
class gcdd
{
	public:
	T operator()(const T lhs,const T rhs) const 
	{
		return __gcd(lhs,rhs);
	}
};

template<typename T,typename pred_t>
class segment_tree
{
	private:
	T *tree; //for tree
	vector<T> A; //to hold elements
	int n;	//no of elements in the container
	
	void build_tree(const vector<T>&,T *tree,int start,int end,int np);
	
	T query_util(T *tree ,int start,int end,int query_start,int query_end,int np);
	
	void update_util(T *tree,int start,int end,int index,int value,int np);
	
	public:
	//constructor that takes pair of iterator
	template<class InputIterator>
	segment_tree( InputIterator first , InputIterator last );
	
	//copy constructor
	segment_tree(const segment_tree<T,pred_t>&);
	
	//constructor that takes initializer list
	segment_tree(std::initializer_list<T>);
	
	//assignment operator
	segment_tree<T,pred_t>& operator=(const segment_tree&);
	
	//destructors
	~segment_tree();
	
	T query(int query_start,int query_end);
	void update(int index,int value);
	
	//index operator overloading
	T operator[](int index);
	
	//some fuctionalities that almost all STL container provides 
	void push_back(T);
	int size();
	void pop_back();

	class Iterator
	{
		private:
		vector<T>::iterator ptr;
		public:
		Iterator(vector<T>::iterator other): ptr(other) {}
		
		T operator*()
		{
			return *ptr;
		}
		
		Iterator& operator++()
		{
			++ptr;
			return *this;
		}
		
		Iterator& operator++(int)
		{
			Iterator temp(*this);
			++*this;
			return temp;
		}	
		
		bool operator==(const Iterator& rhs) const
		{
			return rhs.ptr==ptr;
		}
		
		bool operator!=(const Iterator& rhs) const
		{
			return !(*this==rhs);
		}
	};
	
	Iterator begin()
	{
		return Iterator(A.begin());
	}
	
	Iterator end()
	{
		return Iterator(A.end());
	}
};


template<typename T,typename pred_t>
template<class InputIterator>
segment_tree<T,pred_t>::segment_tree( InputIterator first , InputIterator last )
{
	while(first!=last)
	{
		A.push_back(*first);
		++first;
	}
	n=A.size();
	tree=new T[4*n];
	build_tree(A,tree,0,n-1,0);
}


template<typename T,typename pred_t>
segment_tree<T,pred_t>::segment_tree(const segment_tree<T,pred_t>& rhs)
{
	n=rhs.n;
	delete [] tree;
	A.clear();
	tree=new T[4*n];
	for(int i=0;i<n;i++)
	{
		A.push_back(rhs.A[i]);
	}
	for(int i=0;i<4*n;i++)
	{
		tree[i]=rhs.tree[i];
	}
}

template<typename T,typename pred_t>
segment_tree<T,pred_t>::segment_tree(std::initializer_list<T> rhs)
{
	n=rhs.size();
	tree=new T[4*n];
	for(auto it=rhs.begin();it!=rhs.end();++it)
	{
		int i=it-rhs.begin();
		this->A.push_back(*it);
	}
	build_tree(A,tree,0,n-1,0);
}

template<typename T,typename pred_t>
segment_tree<T,pred_t>& segment_tree<T,pred_t>::operator=(const segment_tree& rhs)
{
	n=rhs->n;
	delete [] tree;
	delete [] A;
	tree=new T[4*n];
	for(int i=0;i<n;i++)
	{
		A[i]=rhs->A[i];
	}
	
	for(int i=0;i<4*n;i++)
	{
		tree[i]=rhs->tree[i];
	}
	return this;
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
		return T();
	}
	if(query_start<=start and query_end>=end)
	{
		return tree[np];
	}
	int mid=mid(start,end);
	T left=query_util(tree,start,mid,query_start,query_end,2*np+1);
	T right=query_util(tree,mid+1,end,query_start,query_end,2*np+2);
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
void segment_tree<T,pred_t>::push_back(T element)
{
	A.push_back(element);
	build_tree(A,tree,0,n-1,0);
}

template<typename T,typename pred_t>
void segment_tree<T,pred_t>::pop_back()
{
	A.pop_back();
	build_tree(A,tree,0,n-1,0);
}

template<typename T,typename pred_t>
int segment_tree<T,pred_t>::size()
{
	A.pop_back();
	return n;
}

template<typename T,typename pred_t>
T segment_tree<T,pred_t>::operator[](int index)
{	
	return A[index];
}


int main()
{
	#if 0
	//testing on methods and functors
	int n=10;
	segment_tree<int,minimum<int>> tree1{1,2,3,4,5,6,7,8,9,10};
	cout << "minimum : " << tree1.query(0,n-1) << endl;
	
	cout << "update index : " << 4 << " with : "<< 0 << endl;
	tree1.update(4,0);
	
	cout << "minimum : " << tree1.query(0,n-1) << endl;
	cout << endl;
	
	segment_tree<int,maximum<int>> tree2{1,2,3,4,5,6,7,8,9,10};
	cout << "maximum : " << tree2.query(0,n-1) << endl;
	
	cout << "update index : " << 4 << " with : "<< 20 << endl;
	tree2.update(4,20);
	
	cout << "maximum : " << tree2.query(0,n-1) << endl;
	cout << endl;
	
	segment_tree<int,summation<int>> tree3{1,2,3,4,5,6,7,8,9,10};
	cout << "sum : " << tree3.query(0,n-1) << endl;
	
	cout << "update index : " << 4 << " with : "<< 20 << endl;
	tree3.update(4,20);
	
	cout << "sum : " << tree3.query(0,n-1) << endl;
	cout << endl;
	
	
	segment_tree<int,gcdd<int>> tree4{1,2,3,4,5,6,7,8,9,10};
	cout << "gcd : " << tree4.query(0,n-1) << endl;
	#endif
	
	#if 0
	//testing on free algorithms
	segment_tree<int,gcdd<int>> tree1{1,2,3,4,5,6,7,8,9,10};
	
	auto it=find(tree1.begin(),tree1.end(),4);
	if(it!=tree1.end())
	{
		cout << "found " << *it << endl;
	}
	
	it=upper_bound(tree1.begin(),tree1.end(),5);
	if(it!=tree1.end())
	{
		cout << "upper bound of 4 is " << *it << endl;
	}
	
	for(auto it=tree1.begin();it!=tree1.end();++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	
	#endif
	
	#if 1
	//testing constructors
	int n=5;
	vector<int> v{6,7,8,9,10};
	segment_tree<int,maximum<int>> tree1{1,2,3,4,5};
	segment_tree<int,maximum<int>> tree2(tree1);
	segment_tree<int,maximum<int>> tree3(v.begin(),v.end());
	cout << "max : " << tree1.query(0,n-1) << endl;
	cout << "max : " << tree2.query(0,n-1) << endl;
	cout << "max : " << tree3.query(0,n-1) << endl;
	#endif
	
	return 0;	
}











