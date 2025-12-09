#include<bits/stdc++.h>
#define N 250
#define M 5050
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
int n,m,s,t;
int head[N],Next[M<<1],ver[M<<1],edge[M<<1],tot=-1;
int dep[N],cur[N];
ll maxflow;
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1;ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=x*10+ch-48;ch=getchar(); }
    return x*f;
}
inline void ADD(int x,int y,int z) {
    ver[++tot]=y;
    edge[tot]=z;
    Next[tot]=head[x];
    head[x]=tot;
}
inline int bfs() {
    memset(dep,-1,sizeof(dep));
    dep[s]=0;
    queue<int>Q;
    Q.push(s);
    while(!Q.empty()) {
        int x=Q.front();Q.pop();
        for(int i=head[x];~i;i=Next[i]) {
            int y=ver[i];int z=edge[i];
            if(z>0&&dep[y]==-1) {
                dep[y]=dep[x]+1;
                Q.push(y);
                if(y==t) return 1;
            }
        }
    }
    return dep[t]!=-1;
}
int dfs(int x,int f) {
    if(x==t) return f;
    int used=0;
    for(int &i=cur[x];~i;i=Next[i]) {
        int y=ver[i];int z=edge[i];
        if(z>0&&dep[y]==dep[x]+1) {
            int w=dfs(y,min(f-used,z));
            if(w>0) {
                edge[i]-=w;
                edge[i^1]+=w;
                used+=w;
                if(used==f) return used;
            }
        }
    }
    if(!used) dep[x]=-1;
    return used;
}
inline void Dinic() {
    while(bfs()) {
        memcpy(cur,head,sizeof(head));
        int f=0;
        while(f=dfs(s,INF)) maxflow+=(ll)f;
    }
}
int main() {
    memset(head,-1,sizeof(head));
    n=read();m=read();s=read();t=read();
    for(int i=1;i<=m;i++) {
        int x=read(),y=read(),z=read();
        ADD(x,y,z);ADD(y,x,0);
    }
    Dinic();
    printf("%lld\n",maxflow);
    return 0;
}
/*
input:
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 30

output:50
*/