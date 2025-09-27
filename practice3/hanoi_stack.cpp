#include<bits/stdc++.h>
using namespace std;
struct step{ int n,flag;char from,tmp,to; };
stack<step> S;
inline void hanoi()
{
    while(!S.empty())
    {
        step s=S.top();S.pop();
        if(!s.n) continue;
        if(!s.flag)
        {
            S.push({s.n-1,0,s.tmp,s.from,s.to});
            S.push({s.n,1,s.from,s.tmp,s.to});
            S.push({s.n-1,0,s.from,s.to,s.tmp});
        }
        else cout<<"Move disk "<<s.n<<": "<<s.from<<" -> "<<s.to<<"\n";
    }
}
int main()
{
    int n;
    cin>>n;
    S.push({n,0,'A','B','C'});
    hanoi();
    return 0;
}