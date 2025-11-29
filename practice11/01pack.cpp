#include<bits/stdc++.h>
#define N 10050
using namespace std;
int n,V;
int w[N],c[N];
int f[N];
int main() {
    cin>>n>>V;
    for(int i=1;i<=n;i++) {
        cin>>w[i]>>c[i];
    }
    for(int i=1;i<=n;i++) {
        for(int j=V;j>=w[i];j--) {
            f[j]=max(f[j],f[j-w[i]]+c[i]);
        }
    }
    cout<<f[V]<<"\n";
    return 0;
}
/*
input:
4 70
71 100
69 1
1 2
70 5

output:5
*/