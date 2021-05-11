#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

#include "segment_tree.hpp"

vector<int> get_random_vector(int n)
{
    vector<int> a(n,0);
    for(int i=0;i<n;++i)
    {
        a[i] = rand() % 10;
    }

    return a;
}

template<typename pred_t> 
void compute(vector<int> &a, int l, int r)
{
    int sum = 0;
    for(int i=l;i<=r;++i)
        sum+=a[i];
    
}

int main()
{
    vector<int> sizes = {100, 1000, 10000, 100000};
    srand(6);

    for(int size:sizes)
    {
        vector<int> a = get_random_vector(size);
        segment_tree<int, operation::sum<int> > tree(a.begin(),a.end());

        int l = rand() % size/2;
        int r = rand() % size;
        cout<<"Querying for range ["<<l<<","<<r<<"]\n";
        // Query normally
        auto start = std::chrono::high_resolution_clock::now();
        compute<operation::sum<int> >(a,l,r);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by normal query: " << duration.count() << " microseconds" << endl;

        // Query on segment tree
        start = std::chrono::high_resolution_clock::now();
        tree.query(l,r);
        stop = std::chrono::high_resolution_clock::now();

        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout << "Time taken by segment tree: " << duration.count() << " microseconds" << endl << endl;
    }
}