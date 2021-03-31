#include<bits/stdc++.h>
#define mid(l,r) (l+(r-l)/2)
using namespace std;
#include <list>

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


template<typename T,typename pred_t,typename iter>
class segment_tree
{
	private:
	T *tree;
	int n;
	int size;
	
	void build_tree(iter begin,T *tree,int start,int end, int np);
	T query_util(T *tree ,int start,int end,int query_start,int query_end,int np);
	void update_util(T *tree,int start,int end,int index,int value,int np);

	int find_size(iter begin, iter end, bidirectional_iterator_tag );
	int find_size(iter begin, iter end, random_access_iterator_tag);
	int find_size(iter begin, iter end, input_iterator_tag);

	T find_ele(iter begin, int index, bidirectional_iterator_tag );
	T find_ele(iter begin, int index, random_access_iterator_tag);
	T find_ele(iter begin, int index, input_iterator_tag);

	public:
	segment_tree(iter start, iter end);
	~segment_tree();
	T query(int query_start,int query_end);
	void update(int index,int value);
	T operator[](int index);
	void disp();
};

template<typename T,typename pred_t,typename iter>
void segment_tree<T,pred_t,iter>::disp(){
	//cout << "hey\n";
	//cout << n << "\n";
	for(int i=0 ; i<n; i++){
		//cout << "hi" <<"\n";
		cout << *(tree+i) <<"\t"; 
	}
	cout << "\n";
}

template<typename T,typename pred_t,typename iter>
int segment_tree<T,pred_t,iter>::find_size(iter begin,iter end, random_access_iterator_tag){
	return end - begin;
}

template<typename T,typename pred_t,typename iter>
int segment_tree<T,pred_t,iter>::find_size(iter begin,iter end, bidirectional_iterator_tag){
	int i=0;
	while(begin != end)
	{
		i++;
		begin++;
	}
	return i;

}

template<typename T,typename pred_t,typename iter>
int segment_tree<T,pred_t,iter>::find_size(iter begin,iter end, input_iterator_tag){
	int i=0;
	while(begin != end)
	{
		i++;
		begin++;
	}
	return i;

}

template<typename T,typename pred_t,typename iter>
T segment_tree<T,pred_t,iter>::find_ele(iter begin,int index, random_access_iterator_tag){
	return *(begin + index);
}

template<typename T,typename pred_t,typename iter>
T segment_tree<T,pred_t,iter>::find_ele(iter begin,int index, bidirectional_iterator_tag){
	while(index > 0)
	{
		begin++;
		index--;
	}
	return *begin;
}

template<typename T,typename pred_t,typename iter>
T segment_tree<T,pred_t,iter>::find_ele(iter begin,int index, input_iterator_tag){
	while(index > 0)
	{
		begin++;
		index--;
	}
	return *begin;
}

template<typename T,typename pred_t,typename iter>
segment_tree<T,pred_t,iter>::segment_tree(iter begin,iter end) 
{
	//cout << "hey";
	size =  find_size(begin, end, typename iterator_traits<iter>::iterator_category());
	//cout <<"hello"<<"\n";
	n = 1;
	while(n < size){
		n = n*2;
	}
	n = n*2;
	cout << n <<"\n";
	tree =  new int[n];
	build_tree(begin,tree, 0 , size,  0);
}

template<typename T,typename pred_t,typename iter>
segment_tree<T,pred_t,iter>::~segment_tree()
{
	delete [] tree; 
}


template<typename T,typename pred_t, typename iter>
T segment_tree<T,pred_t,iter>::query(int query_start,int query_end)
{
	return query_util(this->tree,0,size-1,query_start,query_end,0);
}

template<typename T,typename pred_t, typename iter>
void segment_tree<T,pred_t,iter>::update(int index,int value)
{
	return update_util(this->tree,0,size-1,index,value,0);
}

template<typename T,typename pred_t, typename iter>
void segment_tree<T,pred_t,iter>::build_tree(iter begin,T *tree,int start,int end,int np)
{
	//cout << "In build_tree" << "\t" <<start << "\t" << end << np << "\n";
	if(end - start == 1)
	{
		
		tree[np] = find_ele(begin, start,typename iterator_traits<iter>::iterator_category());
	//	cout << "hey" << tree[np]<<"\n";
		return;
	}
	int mid=mid(start,end);
	build_tree(begin,tree,start,mid,2*np+1);
	build_tree(begin,tree,mid,end,2*np+2);
	tree[np]=pred_t()(tree[2*np+1],tree[2*np+2]);
	//cout << "after build np:" << tree[np] << "\n";
}

template<typename T,typename pred_t, typename iter>
T segment_tree<T,pred_t,iter>::query_util(T *tree,int start,int end,int query_start,int query_end,int np)
{
	//cout << start <<"\t"<< end <<"\t"<< query_start<<"\t" << query_end << "\t" << np << "\n";
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

template<typename T,typename pred_t, typename iter>
void segment_tree<T,pred_t,iter>::update_util(T *tree,int start,int end,int index,int value,int np)
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

template<typename T,typename pred_t,typename iter>
T segment_tree<T,pred_t,iter>::operator[](int index)
{
	return query(index,index);
}

int main()
{
	int n;
	n=8;
 	list<int> v{1,2,3,4,5,6,7,8};
	int sum=0;
	segment_tree<int,summation<int>, list<int>::iterator> tree1(v.begin(),v.end());
	tree1.disp();
	cout<< tree1.query(0,5) << "\n";
	tree1.disp();
	tree1.update(1,4);
	tree1.disp();
	cout<<"end\n";



	// cout << tree1[1] << endl;
	return 0;	
}
