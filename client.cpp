#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include "segment_tree.hpp"
using namespace operation;

int main()
{
	int n;
	n=8;
 	list<int> v{1,2,3,4,5,6,7,8};
	int sum=0;
	segment_tree<int,operation::min<int>, list<int>::iterator> tree1(v.begin(),v.end());
	tree1.display();
	cout<< tree1.query(0,5) << "\n";
	tree1.display();
	tree1.update(1,4);
	tree1.display();

	vector<int> a = {2,3,5,6,4,8,2,1,4,6};
	segment_tree<int, operation::sum<int>,vector<int>::iterator> tree(a.begin()+2,a.begin()+a.size()-2);
	tree.display();
	cout<<tree.query(1,3)<<"\n";
	return 0;	
}