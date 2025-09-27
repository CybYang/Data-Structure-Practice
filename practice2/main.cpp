#include <bits/stdc++.h>
#include "quicksort.hpp"
using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<int>a(n);
    for (int i=0;i<n;i++) cin>>a[i];
    vector<int>asc=a;
    if (n>0) quick_sort(asc.data(),0,n-1);
    for(int i=0;i<n;i++) cout<<asc[i]<<" ";
    cout<<endl;
    vector<int> desc = a;
    if (n>0) quick_sort(desc.data(),0,n-1,[](int x,int y){ return x>y; });
    for(int i=0;i<n;i++) cout<<desc[i]<<" ";
    return 0;
}