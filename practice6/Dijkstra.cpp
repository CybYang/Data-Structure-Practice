#include<iostream>
#include<algorithm>
#include<functional>
#include<queue>
#include<cstring>

#define N 100050
#define M 200050
using namespace std;
int head[N],Next[M],ver[M],edge[M],tot=-1;
int dist[N],vis[N],pre[N];
int n,m,s;
priority_queue<pair<int,int>>Q;
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
void dijkstra(int root) {
    dist[root]=0;
    Q.push(make_pair(-0,root));
    while(!Q.empty()) {
        int x=Q.top().second;Q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];~i;i=Next[i]) {
            int y=ver[i];int z=edge[i];
            if(dist[y]>dist[x]+z) {
                dist[y]=dist[x]+z;
                if(!vis[y]) {
                    pre[y]=x;
                    Q.push(make_pair(-dist[y],y));
                }
            }
        }
    }
}
void print(int x) {
    if(x==s) {
        cout<<s<<" ";
        return ;
    }
    print(pre[x]);
    cout<<x<<" ";
}
int main() {
    memset(head,-1,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(dist,0x3f,sizeof(dist));
    n=read();m=read();s=read();
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        x=read();y=read();z=read();
        ADD(x,y,z);ADD(y,x,z);
    }
    dijkstra(s);
    for(int i=1;i<=n;i++) {
        cout<<"The shortest dist:"<<dist[i]<<"\n";
        cout<<"The path:";
        print(i);
        cout<<"\n";
    }
    return 0;
}
/*
input:
4 6 1
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4

output:
0 2 4 3
*/