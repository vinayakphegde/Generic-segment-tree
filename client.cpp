#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include "segment_tree.hpp"

int main()
{
				//  = {2,10,10,10,10}
	vector<int> a = {2,3,1,6};
	// segment_tree<int, operation::sum<int> > tree(a.begin()+2,a.begin()+a.size()-2);
	// tree.display();
	// cout<<tree.query(1,3)<<"\n";
	#if 0
	cout<<"\n"<<"SUM: "<<"\n";
	segment_tree<int, operation::sum<int> > tree(a.begin(),a.end());
	tree.updateRange(1,4,10);
	for(int i=0;i<a.size();++i)
	{
		cout<<tree.query(0,i)<<"\n";
	}
	#endif

	#if 1
	cout<<"\n"<<"MIN: "<<"\n";
	segment_tree<int, operation::min<int>> tree2(a.begin(),a.end());
	for(int i=0;i<a.size();++i)
	{
		cout<< tree2.query(0,i)<<"\n";
	}
	// tree2.display();
	// tree2.updateRange(0,3,10);

	// cout<<*tree2.query(1,3)<<"\n";

	// tree2.display();

	// cout<<"\n"<<"MAX: "<<"\n";
	// segment_tree<int, operation::max<int> > tree3(a.begin(),a.end());
	// for(int i=0;i<a.size();++i)
	// {
	// 	cout<<*tree3.query(0,i)<<"\n";
	// }
	#endif
	return 0;	
}