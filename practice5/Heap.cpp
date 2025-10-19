#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
using std::vector;
using std::size_t;

template<typename T,class Cmp=std::less<T>>
class Heap {
public:
    explicit Heap(const vector<T>& v) { build(v); }

private:
    vector<T> val_;
    size_t sz_=0;
    Cmp cmp_;

public:
    Heap()=default;
    ~Heap() { clear(); }

    bool empty() const { return sz_==0; }
    size_t size() const { return sz_; }
    const T& top() const { return val_.front(); }
    T& top() { return val_.front(); }

    void build(const vector<T>& v) {
        val_=v;
        sz_=val_.size();
        if(sz_<=1) return ;
        for(int i=(sz_-1)>>1;i>=0;i--) push_down(i);
    }

    void push(const T& x) {
        val_.push_back(x);
        sz_++;
        push_up(sz_-1);
    }
    void pop() {
        if(sz_==0) return ;
        std::swap(val_[0],val_[sz_-1]);
        sz_--;
        val_.pop_back();
        if(sz_) push_down(0);
    }

    void clear() { val_.clear();sz_=0; }

private:
    void push_down(size_t x) {
        size_t l=2*x+1;
        while(l<=sz_-1) {
            if(l<sz_-1&&cmp_(val_[l+1],val_[l])) l++;
            if(cmp_(val_[l],val_[x])) {
                std::swap(val_[x],val_[l]);
                x=l;
                l=2*x+1;
            }
            else break;
        }
    }
    void push_up(size_t x) {
        size_t fa=(x-1)>>1;
        while(x>0) {
            if(cmp_(val_[x],val_[fa])) {
                std::swap(val_[x],val_[fa]);
                x=fa;
                fa=(x-1)>>1;
            }
            else break;
        }
    }
};

int main()
{
    Heap<int>H;
    vector<int>v={5,3,8,1,4,7,9,6};
    H.build(v);
    while(!H.empty()) {
        std::cout<<H.top()<<" ";
        H.pop();
    }
    std::cout<<"\n";
    for(int x:v) H.push(x);
    while(!H.empty()) {
        std::cout<<H.top()<<" ";
        H.pop();
    }
    return 0;
}