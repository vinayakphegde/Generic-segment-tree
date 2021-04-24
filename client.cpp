#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include "segment_tree.hpp"

int main()
{
	vector<int> a = {2,3,5,6,4,8,2,1,4,6};
	// segment_tree<int, operation::sum<int> > tree(a.begin()+2,a.begin()+a.size()-2);
	// tree.display();
	// cout<<tree.query(1,3)<<"\n";

	cout<<"\n"<<"SUM: "<<"\n";
	segment_tree<int, operation::sum<int> > tree(a.begin(),a.end());
	for(int i=0;i<a.size();++i)
	{
		cout<<tree.query(0,i)<<"\n";
	}

	cout<<"\n"<<"MIN: "<<"\n";
	segment_tree<int, operation::min<int> > tree2(a.begin(),a.end());
	for(int i=0;i<a.size();++i)
	{
		cout<<*tree2.query(0,i)<<"\n";
	}

	cout<<"\n"<<"MAX: "<<"\n";
	segment_tree<int, operation::max<int> > tree3(a.begin(),a.end());
	for(int i=0;i<a.size();++i)
	{
		cout<<*tree3.query(0,i)<<"\n";
	}
	return 0;	
}