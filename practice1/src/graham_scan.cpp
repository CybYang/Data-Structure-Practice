#include<bits/stdc++.h>
#include"Stack.hpp"
#define N 100050
using namespace std;
const double eps=1e-12;
int n,tot;
double ans;
struct point { double x,y,angle,dis; }a[N],s[N];
bool cmp(point x,point y) 
{
	if(fabs(x.angle-y.angle)>eps) return x.angle<y.angle; 
	return x.dis<y.dis;
}
double cross(point a,point b,point c) { return (b.x-a.x)*(c.y-b.y)-(b.y-a.y)*(c.x-b.x);  }
double dist(point a,point b) { return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y;
	int pos=1;
	for(int i=2;i<=n;i++)
		if(a[i].y<a[pos].y||(a[i].y==a[pos].y&&a[i].x<a[pos].x)) pos=i;
	swap(a[1],a[pos]);
	for(int i=2;i<=n;i++)
	{
		a[i].angle=atan2((a[i].y-a[1].y),(a[i].x-a[1].x));
		a[i].dis=dist(a[i],a[1]);
	}
	sort(a+2,a+1+n,cmp);
	vector<point> map;
	map.push_back(a[1]);
	for(int i=2;i<=n;)
	{
		int j=i+1;
		while(j<=n&&(fabs(a[i].angle-a[j].angle)<eps)) j++;
		map.push_back(a[j-1]);
		i=j;
	}
	if(map.size()==2)
	{
		ans=2.0*dist(map[0],map[1]);
		printf("%.2lf\n",ans);
		return 0;
	}
	Stack<point>S;
	S.push(map[0]);S.push(map[1]);
	for(size_t i=2;i<map.size();i++)
	{
		while(S.size()>=2)
		{
			point t1=S.top();S.pop();
			point t2=S.top();
			if(cross(t2,t1,map[i])>0) { S.push(t1);break; } 
		}
		S.push(map[i]);
	}
    printf("The points on the convex hull are:\n");
	while(!S.empty())
	{
		point p=S.top();S.pop();
		s[++tot]=p;
        printf("(%.2lf,%.2lf)\n",p.x,p.y);
	}
	s[++tot]=s[1];
	for(int i=2;i<=tot;i++) ans+=dist(s[i],s[i-1]);
	printf("The circumference of the convex hull is %.2lf\n",ans);
	return 0;
}
/*
4
4 8
4 12
5 9.3
7 8
*/