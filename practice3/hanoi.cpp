#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll lowbit(ll x) { return x&-x; }
int main()
{
    int n;
    cin>>n;
    ll k=(1<<n)-1;
    const char name[3]={'A','B','C'};
    for(ll i=1;i<=k;i++)
    {
        ll d=lowbit(i);
        ll disk=0,dir=0;
        while(d>>=1) disk++;
        ll cnt=((i>>disk)+1)>>1;
        dir=(((n-(disk+1))&1)==0) ?-1:+1;
        int from=((dir*(cnt-1))%3+3)%3;
        int to=(from+dir+3)%3;
        cout<<"Move disk "<<(disk + 1)<<": "<<name[from]<<" -> "<<name[to]<<"\n";
    }
    return 0;
}