#include<iostream>
#include<string>
#include"List.hpp"
#include"Stack.hpp"
#include"Queue.hpp"

int main() 
{
     using std::cout;
     using std::endl;
     List<int> L;
     L.push_back(1);
     L.push_back(2);
     L.push_front(0);
     cout<<"List size = "<<L.size()<<endl;
     cout<<"Front = "<<L.front()<<",Back = "<<L.back()<<endl;
     L.pop_front();
     cout<<"After pop_front, front = "<<L.front()<<endl;
     L.pop_back();
     cout<<"After pop_back, back = "<<L.back()<<endl;
     cout<<"List size = "<<L.size()<<endl;
     cout<<"List is empty? "<<(L.empty()?"Yes":"No")<<endl;

     cout<<"----"<<endl;

     Stack<int> S;
     S.push(10);
     S.push(20);
     cout<<"Stack size = "<<S.size()<<endl;
     cout<<"Top = "<<S.top()<<endl;
     S.pop();
     cout << "After pop, top = " << S.top() << endl;
     cout<<"Stack size = "<<S.size()<<endl;
     cout<<"Stack is empty? "<<(S.empty()?"Yes":"No")<<endl;

     cout<<"----"<<endl;

     Queue<std::string> Q;
     Q.push("hello");
     Q.push("world");
     cout<<"Queue size = "<<Q.size()<<endl;
     cout<<"Front = "<<Q.front()<<",Back = "<<Q.back()<<endl;
     Q.pop();
     cout<<"After pop, front = "<<Q.front()<<endl;
     cout<<"Queue size = "<<Q.size()<<endl;
     cout<<"Queue is empty? "<<(Q.empty()?"Yes":"No")<<endl;
     return 0;
}
