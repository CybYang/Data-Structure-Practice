#include<bits/stdc++.h>
#define N 10050
#define M 10050
using namespace std;
typedef long long ll;
int n,V;
ll w[N],c[N],a[N];
ll f[M];
int main() {
    cin>>n>>V;
    for(int i=1;i<=n;i++) {
        cin>>w[i]>>c[i]>>a[i];
    }
    for(int i=1;i<=n;i++) {
        for(int j=V;j>=w[i];j--) {
            for(int k=1;k<=a[i]&&k*w[i]<=j;k++) {
                f[j]=max(f[j],f[j-k*w[i]]+k*c[i]);
            }
        }
    }
    printf("%lld\n",f[V]);
    return 0;
}