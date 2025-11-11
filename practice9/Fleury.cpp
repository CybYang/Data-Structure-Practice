#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cstdio>
#define N 100050
using namespace std;
int n,m;
int head[N],Next[N<<1],ver[N<<1],tot=-1;
int deg[N],pre[N],vis[N<<1],path[N<<1],fa[N];
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
int Find(int x) {
    if(fa[x]==x) return x;
    return fa[x]=Find(fa[x]);
}
inline void Link(int x,int y) {
    int fx=Find(x);int fy=Find(y);
    if(fx!=fy) fa[fx]=fy;
}
inline int check(int p,int id) {
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int x=1;x<=n;x++) {
        for(int i=head[x];~i;i=Next[i]) {
            if(vis[i]) continue;
            if(i&1) continue;
            int y=ver[i];
            Link(x,y);
        }
    }
    int q=ver[id];
    return Find(p)!=Find(q);
}
inline void fleury(int x) {
    path[0]=x;
    for(int k=1;k<=m;k++) {
        int cnt=0;int first=0;
        for(int i=head[x];~i;i=Next[i]) {
            if(vis[i]) continue;
            if(!first) first=i;
            cnt++;
        }
        if(cnt==1) {
            vis[first]=1;
            vis[first^1]=1;
            path[k]=ver[first];
            x=ver[first];
        }
        else {
            int flag=0;
            for(int i=head[x];~i;i=Next[i]) {
                int y=ver[i];
                if(vis[i]) continue;
                vis[i]=1;
                vis[i^1]=1;
                if(check(x,i)) {
                    vis[i]=0;
                    vis[i^1]=0;
                }
                else {
                    path[k]=y;
                    x=y;
                    flag=1;
                    break;
                }
            }
            if(!flag) {
                vis[first]=1;
                vis[first^1]=1;
                path[k]=ver[first];
                x=ver[first];
            }
        }
    }
    
}
int main() {
    memset(head,-1,sizeof(head));
    n=read();m=read();
    for(int i=1;i<=m;i++) {
        int x=read();int y=read();
        ADD(x,y);ADD(y,x);
        deg[x]++;deg[y]++;
    }
    int cnt=0,s=1;
    for(int i=1;i<=n;i++) {
        if(deg[i]&1) {
            cnt++;
            if(!s) s=i;
        }
    }
    if(cnt!=0&&cnt!=2) cout<<"There is no Eulerian trail."<<endl;
    else {
        if(cnt==0) cout<<"There is an Eulerian circuit."<<endl;
        else cout<<"There is an Eulerian trail."<<endl;
        fleury(s);
        for(int i=0;i<=m;i++) cout<<path[i]<<" ";
        cout<<"\n";
    }
    return 0;
}
/*
input:
7 9
1 2
2 3
3 4
4 2
4 5
2 5
5 6
5 7
4 6

output:
1 2 5 6 4 2 3 4 5 7 
*/