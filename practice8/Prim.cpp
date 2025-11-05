#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<queue>
#include<utility>
#define N 100050

using std::cin;
using std::cout;
using std::priority_queue;
using std::pair;
using std::make_pair;

int n,m;
int ver[N<<1],edge[N<<1],Next[N<<1],head[N],tot=-1;
int dist[N],vis[N];
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
inline int Prim(int root) {
    priority_queue<pair<int,int>>Q;
    memset(dist,0x3f,sizeof(dist));
    dist[root]=0;
    Q.push(make_pair(-0,root));
    int sum=0,cnt=0;
    while(!Q.empty()) {
        if(cnt==n) break;
        int x=Q.top().second;
        Q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        sum+=dist[x];cnt++;
        for(int i=head[x];~i;i=Next[i]) {
            int y=ver[i];int z=edge[i];
            if(z<dist[y]) {
                dist[y]=z;
                if(!vis[y]) Q.push(make_pair(-dist[y],y));
            }
        }
    }
    if(cnt==n) return sum;
    return -1;
}
int main() {
    memset(head,-1,sizeof(head));
    n=read();m=read();
    for(int i=1;i<=m;i++) {
        int x=read();int y=read();int z=read();
        ADD(x,y,z);ADD(y,x,z);
    }
    cout<<Prim(1)<<"\n";
    return 0;
}
/*
input:
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3

output:
7
*/