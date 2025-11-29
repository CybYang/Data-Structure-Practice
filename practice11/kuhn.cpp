#include<bits/stdc++.h>
#define N 1050
#define M 50050
using namespace std;
int n,m,e;
int head[N],ver[M],Next[M],tot=-1;
int vis[N],match[N],ans;
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
bool dfs(int x) {
    for(int i=head[x];~i;i=Next[i]) {
        int y=ver[i];
        if(vis[y]) continue;
        vis[y]=1;
        if(!match[y]||dfs(match[y]))  {
            match[y]=x;
            return true;
        }
    }
    return false;
}
inline void kuhn() {
    for(int x=1;x<=n;x++) {
        memset(vis,0,sizeof(vis));
        if(dfs(x)) ans++;
    }
}
int main() {
    memset(head,-1,sizeof(head));
    n=read();m=read();e=read();
    for(int i=1;i<=e;i++) {
        int u=read();int v=read();
        ADD(u,v+n);
    }
    kuhn();
    printf("%d\n",ans);
    return 0;
}
/*
input:
4 2 7
3 1
1 2
3 2
1 1
4 2
4 1
1 1

output: 2
*/