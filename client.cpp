#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "segment_tree.hpp"

int main()
{
    {
        vector<int> a = {2, 3, 1, 6, 5};

        segment_tree<int, operation::min<int> > tree1(a.begin(), a.end());
        segment_tree<int, operation::min<int> >::iterator it = tree1.query(0,3);

        segment_tree<int, operation::sum<int> > tree2(a.begin(), a.end());
        int sum = tree2.query(0,3);

        cout<<sum<<"\n";
    }
    {
        vector<int> a = {2, 3, 1, 6, 5};

        segment_tree<int, operation::min<int> > tree(a.begin(), a.end());
        tree.update(2,15);

        tree.display();
    }
    {
        vector<int> a = {2, 3, 1, 6, 5};

        segment_tree<int, operation::min<int> > tree(a.begin(), a.end());
        tree.update(2,4,15);

        tree.display();
    }
    {
        vector<int> a = {2, 3, 1, 6, 5};

        segment_tree<int, operation::max<int> > tree(a.begin(), a.end());
        tree.add(2,4,10);

        tree.display();
    }
    {
        vector<int> b = {1,2,2,3,6};
        segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
        segment_tree<int, operation::sum<int> >::iterator it = lower_bound(tree.begin(), tree.end(), 2);

        cout<<*it<<"\n";
    }
    {
        vector<int> b = {1,2,2,3,6};
        segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
        segment_tree<int, operation::sum<int> >::iterator it = find(tree.begin(), tree.end(), 2);

        cout<<*it<<"\n";
    }
    {
        vector<int> b = {1,2,2,3,6};
        segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
        typedef segment_tree<int, operation::sum<int> >::iterator seg_tree_iter;
        pair<seg_tree_iter, seg_tree_iter> p =  equal_range(tree.begin(), tree.end(), 2);

        cout<<*p.first<<" "<<*p.second<<"\n";
    }
    {
        vector<int> b = {1,2,2,3,6};
        segment_tree<int, operation::sum<int> > tree(b.begin(), b.end());
        segment_tree<int, operation::sum<int> >::iterator it = find_if(tree.begin(), tree.end(), [](int x){return x%2 == 0;});

        cout<<*it<<"\n";
    }
}