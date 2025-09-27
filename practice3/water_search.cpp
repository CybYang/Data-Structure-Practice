#include<bits/stdc++.h>
using namespace std;
int A,B,C;
int w,N,flag=-1;
const char* name[6]={ "Fill A","Fill B","Empty A","Empty B","Pour A->B","Pour B->A" };
inline int GCD(int x,int y)
{
    if(A<B) swap(A,B);
    while(y)
    {
        int tmp=x%y;
        x=y;
        y=tmp;
    }
    return x;
}
inline int code(int x,int y) { return x*w+y; }
inline pair<int,int> decode(int x) { return {x/w,x%w}; }
inline void bfs()
{
    w=B+1;N=(A+1)*(B+1);
    vector<int>vis(N,0);
    vector<int>pre(N,-1),op(N,-1);
    queue<int>Q;
    int root=code(0,0);
    Q.push(root);vis[root]=1;
    while(!Q.empty())
    {
        int x=Q.front();Q.pop();
        auto [a,b]=decode(x);
        if(a==C||b==C) { flag=x;break; }
        auto try_push=[&](int dx,int dy,int opt)
        {
            int y=code(dx,dy);
            if(!vis[y]) { vis[y]=1;pre[y]=x;op[y]=opt;Q.push(y); }
        };
        if(a<A) try_push(A,b,0);
        if(b<B) try_push(a,B,1);
        if(a>0) try_push(0,b,2);
        if(b>0) try_push(a,0,3);
        if(a>0&&b<B)
        {
            int t=min(a,B-b);
            try_push(a-t,b+t,4);
        }
        if(a<A&&b>0)
        {
            int t=min(A-a,b);
            try_push(a+t,b-t,5);
        }
    }
    vector<int> opts;
    for(int x=flag;~pre[x];x=pre[x]) opts.push_back(op[x]);
    reverse(opts.begin(),opts.end());
    int x=0,y=0;
    for(int opt:opts)
    {
        if(opt==0) x=A;
        else if(opt==1) y=B;
        else if(opt==2) x=0;
        else if(opt==3) y=0;
        else if(opt==4)
        {
            int t=min(x,B-y);
            x-=t;y+=t;
        }
        else
        {
            int t=min(A-x,y);
            x+=t;y-=t;
        }
        cout<<name[opt]<<"\n result: [A="<<x<<",B="<<y<<"]\n";
    }
}
int main()
{
    cin>>A>>B>>C;
    int g=GCD(A,B);
    if(C%g!=0) { puts("No");return 0; }
    puts("Yes");
    bfs();
    return 0;
}