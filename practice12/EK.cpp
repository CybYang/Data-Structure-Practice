#include<bits/stdc++.h>
#define N 250
#define M 5050
#define INF 0x3f3f3f3f
using namespace std;
typedef long long ll;
int n,m,s,t;
int head[N],Next[M<<1],ver[M<<1],edge[M<<1],tot=-1;
int pre[N],flow[N],vis[N];
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
int bfs() {
    memset(vis,0,sizeof(vis));
    memset(pre,0,sizeof(pre));
    queue<int>Q;
    Q.push(s);
    vis[s]=1;
    flow[s]=INF;
    while(!Q.empty()) {
        int x=Q.front();Q.pop();
        for(int i=head[x];~i;i=Next[i]) {
            int y=ver[i];int z=edge[i];
            if(z>0&&!vis[y]) {
                vis[y]=1;
                pre[y]=i;
                flow[y]=min(flow[x],z);
                Q.push(y);
                if(y==t) return flow[y];
            }
        }
    }
    return 0;
}
inline void EK() {
    int f=0;
    while(f=bfs()) {
        int y=t;
        while(y!=s) {
            int x=pre[y];
            edge[x]-=f;
            edge[x^1]+=f;
            y=ver[x^1];
        }
        maxflow+=(ll)f;
    }
}
int main() {
    memset(head,-1,sizeof(head));
    n=read();m=read();s=read();t=read();
    for(int i=1;i<=m;i++) {
        int x=read(),y=read(),z=read();
        ADD(x,y,z);ADD(y,x,0);
    }
    EK();
    printf("%lld\n",maxflow);
    return 0;
}