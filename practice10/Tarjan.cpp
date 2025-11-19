#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
#define N 10050
#define M 100050
int n,m;
int tot=-1,head[N],Next[M],ver[M];
int clk,instack[N],dfn[N],low[N],cnt;
int id[N];
stack<int>S;
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1;ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=x*10+ch-48;ch=getchar(); }
    return x*f;
}
inline void ADD(int x,int y) {
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
}
void tarjan(int x) {
    S.push(x);
    instack[x]=1;
    low[x]=dfn[x]=++clk;
    for(int i=head[x];~i;i=Next[i]) {
        int y=ver[i];
        if(!dfn[y]) {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(instack[y]) {
            low[x]=min(low[x],dfn[y]);
        }
    }
    if(low[x]==dfn[x]) {
        cnt++;
        int y;
        do {
            y=S.top();
            S.pop();
            instack[y]=0;
            id[y]=cnt;
        }
        while(x!=y);
    }
    return ;
}
int main() {
    memset(head,-1,sizeof(head));
    n=read();m=read();
    for(int i=1;i<=m;i++) {
        int x=read();int y=read();
        ADD(x,y);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
    for(int i=1;i<=n;i++) cout<<id[i]<<" ";
    cout<<"\n";
    return 0;
}
/*
input:
6 7
1 2
2 3
3 4
4 2
4 1
3 5
5 6

output:
3 3 3 3 2 1
*/