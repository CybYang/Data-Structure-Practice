#include<iostream>
#define N 100050
using namespace std;
int a[N];
void quick_sort(int l,int r)
{
	if(l>=r) return;
	int i=l;
	for(int j=l+1;j<=r;j++)
		if(a[j]<a[l]) { i++;swap(a[i],a[j]); }
	swap(a[i],a[l]);
	quick_sort(l,i-1);quick_sort(i+1,r);
	return;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	quick_sort(1,n);
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	cout<<endl;
	return 0;
}
