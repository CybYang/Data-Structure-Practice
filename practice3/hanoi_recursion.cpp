#include <bits/stdc++.h>
using namespace std;
void hanoi(int n,char from,char tmp,char to) //确定起点和终点另一个就是辅助
{
    if (n==0) return;
    hanoi(n-1,from,to,tmp);
    cout<<"Move disk "<<n<<": "<<from<<" -> "<<to<<"\n";
    hanoi(n-1,tmp,from,to);
}
int main() 
{
    int n;
    cin>>n;
    hanoi(n,'A','B','C');
    return 0;
}