#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#include "segment_tree.hpp"

int main()
{
	#if 0
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
		tree.assignRange(1,3,10);
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout<< "Performing lazy update operation from index 0 to 2:" <<"\n";
		tree.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout << "Performing lazy assign and update operation one after another:\n";
		tree.assignRange(1,3,10);
		tree.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
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
		tree2.assignRange(1,3,10);
		cout << "The current state of the tree:" << "\n";
		tree2.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree2.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::min<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout<< "Performing lazy update operation from index 0 to 2:" <<"\n";
		tree2.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree2.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree2.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::min<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout << "Performing lazy assign and update operation one after another:\n";
		tree2.assignRange(1,3,10);
		tree2.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree2.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree2.display();
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
		tree2.assignRange(1,3,10);
		cout << "The current state of the tree:" << "\n";
		tree2.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree2.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::max<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout<< "Performing lazy update operation from index 0 to 2:" <<"\n";
		tree2.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree2.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree2.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			segment_tree<int, operation::max<int> >::iterator it = tree2.query(0,i);
			cout<<*it<<"\n";
		}
		cout << "\n";
		cout << "Performing lazy assign and update operation one after another:\n";
		tree2.assignRange(1,3,10);
		tree2.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree2.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree2.display();
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
	{
		cout<<"\n"<<"GCD: "<<"\n";
		segment_tree<int, operation::gcd<int> > tree(a.begin(),a.end());
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
		tree.assignRange(1,3,10);
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout<< "Performing lazy update operation from index 0 to 2:" <<"\n";
		tree.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<a.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		cout << "\n";
		cout << "Performing lazy assign and update operation one after another:\n";
		tree.assignRange(1,3,10);
		tree.updateRange(0,2,100);
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
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
		vector<int> b = {1,2,2,3,6};
		cout << "Some of the STL queries" << "\n";
		segment_tree<int, operation::sum<int>> tree2(b.begin(),b.end());
		// segment_tree<int, operation::sum<int> >::iterator it=lower_bound(tree2.begin(),tree2.end(),2);
		// cout << *it<<"\n";
		cout<<"The segment tree:\n";
		tree2.display();
		cout << "Lower Bound of 2: ";
		cout << *lower_bound(tree2.begin(), tree2.end(),2)<<"\n";
		cout << "upper Bound of 2: ";
		cout << *upper_bound(tree2.begin(), tree2.end(),2)<<"\n";
		cout << "Find 2, Found at: ";
		cout << find(tree2.begin(), tree2.end(),2) - tree2.begin()<<"\n";
		cout << "equal_range of 2: ";
		typedef segment_tree<int, operation::sum<int> >::iterator stType;
		pair<stType,stType> p =  equal_range(tree2.begin(), tree2.end(),2);
		cout << p.first - tree2.begin() <<" " << p.second -  tree2.begin()<<"\n";
		cout << "Find if, even number found at: ";
		cout << find_if(tree2.begin(), tree2.end(),[](int x){return x%2 == 0;}) - tree2.begin()<< "\n";
		cout << "Minimum element: ";
		cout << *min_element(tree2.begin(),tree2.end()) << "\n";
		cout<<"Count of element: 3 ";
		cout << count(tree2.begin(),tree2.end(),3) << "\n";
	}
	#endif
	{
		vector<string> s = {"a", "b" ,"c" ,"d"};
		segment_tree<string, operation::concat<string> > tree(s.begin(),s.end());
		cout<< "The segment_tree:"<<"\n";
		tree.display();
		cout<< "Performing Query Operation:" <<"\n";
		for(int i=0;i<s.size();++i)
		{
			cout << "Query from index 0 till " << i <<": ";
			cout<<tree.query(0,i)<<"\n";
		}
		tree.assignRange(1,3,"e");
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
		tree.updateRange(0,2,"f");
		cout << "The current state of the tree:" << "\n";
		tree.display_WU();
		cout<< "After Propogating the updates/assign" << "\n";
		tree.display();
	}
	return 0;	
}