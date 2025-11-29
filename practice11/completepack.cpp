#include<bits/stdc++.h>
#define N 10050
#define M 10000050
using namespace std;
typedef long long ll;
int n,V;
ll w[N],c[N];
ll f[M];
int main() {
    cin>>n>>V;
    for(int i=1;i<=n;i++) {
        cin>>w[i]>>c[i];
    }
    for(int i=1;i<=n;i++) {
        for(int j=w[i];j<=V;j++) {
            f[j]=max(f[j],f[j-w[i]]+c[i]);
        }
    }
    printf("%lld\n",f[V]);
    return 0;
}
/*
input:
3 70
71 100
69 1
1 2

output:140=(70*2)
*/