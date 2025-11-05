#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdio>
#define N 100050

using std::cout;
using std::cin;
using std::sort;

int n,m;
int fa[N];
struct Edge {
    int x,y,z;
    bool operator <(const Edge &e) const {
        return z<e.z;
    }
}edge[N];
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1;ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=x*10+ch-48;ch=getchar(); }
    return x*f;
}
inline void init() {
    for(int i=1;i<=n;i++) fa[i]=i;
}
int Find(int x) {
    if(fa[x]==x) return x;
    return fa[x]=Find(fa[x]);
}
inline int kruskal() {
    int cnt=0,sum=0;
    for(int i=1;i<=m;i++) {
        int x=edge[i].x;int y=edge[i].y;int z=edge[i].z;
        int xx=Find(x);int yy=Find(y);
        if(xx==yy) continue;
        fa[xx]=yy;
        sum+=z;
        cnt++;
        if(cnt==n-1) break;
    }
    if(cnt==n-1) return sum;
    return -1;
}
int main() {
    n=read();m=read();
    init();
    for(int i=1;i<=m;i++) {
        edge[i].x=read();
        edge[i].y=read();
        edge[i].z=read();
    }
    sort(edge+1,edge+1+m);
    cout<<kruskal()<<"\n";
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