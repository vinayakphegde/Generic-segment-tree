#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include "segment_tree.hpp"

int main()
{
	#if 1
	vector<int> a = {2,3,1,6};
	{
		cout<<"\n"<<"SUM: "<<"\n";
		cout << "\n";
		segment_tree<int, operation::sum<int> > tree(a.begin(),a.end());
		cout<< "The segment_tree:"<<"\n";
		tree.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout<< "Performing Lazy assign Operation from index 1 to 3:" <<"\n";
		tree.update(1,3,10);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout<< "Performing lazy update operation from index 0 to 2:" <<"\n";
		tree.add(0,2,100);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout << "Performing lazy assign and update operation one after another:\n";
		tree.update(1,3,10);
		tree.add(0,2,100);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout << "\n";
	}
	{
		cout<<"\n"<<"MIN: "<<"\n";
		segment_tree<int, operation::min<int>> tree2(a.begin(),a.end());
		cout<< "The segment_tree:"<<"\n";
		tree2.display();
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::min<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout<< "Performing Lazy assign Operation from index 1 to 3:" <<"\n";
		tree2.update(1,3,10);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::min<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout<< "Performing lazy update operation from index 0 to 2:" <<"\n";
		tree2.add(0,2,100);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::min<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout << "Performing lazy assign and update operation one after another:\n";
		tree2.update(1,3,10);
		tree2.add(0,2,100);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::min<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout << "\n";
	}
	{
		cout<<"\n"<<"MAX: "<<"\n";
		segment_tree<int, operation::max<int>> tree2(a.begin(),a.end());
		cout<< "The segment_tree:"<<"\n";
		tree2.display();
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::max<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout<< "Performing Lazy assign Operation from index 1 to 3:" <<"\n";
		tree2.update(1,3,10);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::max<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout<< "Performing lazy update operation from index 0 to 2:" <<"\n";
		tree2.add(0,2,100);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::max<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout << "Performing lazy assign and update operation one after another:\n";
		tree2.update(1,3,10);
		tree2.add(0,2,100);
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::max<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout << "\n";
	}
	#endif
	return 0;	
}