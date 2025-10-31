#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<array>
#include<vector>
#include<stack>
#include<limits>
#include<utility>

typedef long double ld;
using std::array;
using std::vector;
using std::stack;
using std::size_t;
using std::min;
using std::max;
using std::cout;

template<typename T,int D>
class KDTree {
public:
    class Node {
    public:
        array<T,D> p;
        array<T,D> mn,mx;
        Node* left;
        Node* right;
        int axis;
        explicit Node(const array<T,D>& p):p(p),left(nullptr),right(nullptr),axis(0) {
            mn=p;mx=p;
        }
    };

private:
    Node* root_=nullptr;
    size_t sz_=0;

public:
    KDTree()=default;
    ~KDTree() { clear(); }

    bool empty() const { return sz_==0; }
    size_t size() const { return sz_; }

    void clear() {
        if(!root_) { sz_=0;return ; }
        stack<Node*> S;
        Node* cur=root_;
        Node* pre=nullptr;
        while(cur||!S.empty()) {
            if(cur) { S.push(cur);cur=cur->left; }
            else {
                Node* s=S.top();
                if(s->right&&pre!=s->right) cur=s->right;
                else {
                    S.pop();
                    pre=s;
                    delete s;
                }
            }
        }
        root_=nullptr;
        sz_=0;
    }

    void build(const vector<array<T,D>>& points) {
        clear();
        if(points.empty()) return ;
        vector<array<T,D>> a=points;
        root_=build(a,0,(int)a.size()-1);
        sz_=a.size();
    }

    void insert(const array<T,D>& p) {
        if(!root_) {
            root_=new Node(p);
            root_->axis=0;
        }
        else {
            root_=insert(root_,p,(root_->axis+1)%D);
        }
        sz_++;
    }

    bool erase(const array<T,D>& p) {
        bool ok=false;
        root_=erase(root_,p,ok);
        if(ok) sz_--;
        return ok;
    }

    std::pair<array<T,D>,ld> nearest(const array<T,D>& q) const {
        if(!root_) return {array<T,D>{},std::numeric_limits<ld>::infinity()};
        array<T,D> best_p=root_->p;
        ld dist_point=dist2_point(root_->p,q);
        nearest(root_,q,best_p,dist_point);
        return {best_p,dist_point};
    }

    void range_query(const array<T,D>& low,const array<T,D>& high,vector<array<T,D>>& out) const {
        out.clear();
        range_query(root_,low,high,out);
    }

private:
    static int choose_axis(const vector<array<T,D>>& a,int l,int r) {
        array<T,D> low=a[l],high=a[l];
        for(int k=0;k<D;k++) {
            for(int i=l+1;i<=r;i++) {
                low[k]=min(low[k],a[i][k]);
                high[k]=max(high[k],a[i][k]);
            }
        }
        int ax=0;
        ld best=(ld)high[0]-(ld)low[0];
        for(int k=1;k<D;k++) {
            ld x=(ld)high[k]-(ld)low[k];
            if(x>best) { best=x;ax=k; }
        }
        return ax;
    }

    static void push_up(Node* x) {
        for(int k=0;k<D;k++) x->mn[k]=x->mx[k]=x->p[k];
        if(x->left) {
            for(int k=0;k<D;k++) {
                x->mn[k]=min(x->mn[k],x->left->mn[k]);
                x->mx[k]=max(x->mx[k],x->left->mx[k]);
            }
        }
        if(x->right) {
            for(int k=0;k<D;k++) {
                x->mn[k]=min(x->mn[k],x->right->mn[k]);
                x->mx[k]=max(x->mx[k],x->right->mx[k]);
            }
        }
    }

    static Node* find_min(Node* x,int axis) {
        if(!x) return nullptr;
        if(x->axis==axis) {
            return x->left?find_min(x->left,axis):x;
        }
        else {
            Node* res=x;
            Node* l=find_min(x->left,axis);
            Node* r=find_min(x->right,axis);
            if(l&&l->p[axis]<res->p[axis]) res=l;
            if(r&&r->p[axis]<res->p[axis]) res=r;
            return res;
        }
    }

    static Node* insert(Node* x,const array<T,D>& p,int new_axis) {
        if(!x) {
            Node* t=new Node(p);
            t->axis=new_axis;
            return t;
        }
        int ax=x->axis;
        if(p[ax]<x->p[ax]) x->left=insert(x->left,p,(x->axis+1)%D);
        else x->right=insert(x->right,p,(x->axis+1)%D);
        push_up(x);
        return x;
    }

    static Node* erase(Node* x,const array<T,D>& p,bool& ok) {
        if(!x) return nullptr;
        if(x->p==p) {
            ok=true;
            if(x->right) {
                Node* rep=find_min(x->right,x->axis);
                x->p=rep->p;
                x->right=erase(x->right,rep->p,ok);
            }
            else if(x->left) {
                Node* rep=find_min(x->left,x->axis);
                x->p=rep->p;
                bool lazy=false;
                x->left=erase(x->left,rep->p,lazy);
                x->right=x->left;
                x->left=nullptr;
            }
            else {
                delete x;
                return nullptr;
            }
        }
        else {
            int ax=x->axis;
            if(p[ax]<x->p[ax]) x->left=erase(x->left,p,ok);
            else x->right=erase(x->right,p,ok);
        }
        push_up(x);
        return x;
    }

    Node* build(vector<array<T,D>>& a,int l,int r) {
        if(l>r) return nullptr;
        int ax=choose_axis(a,l,r);
        int mid=(l+r)>>1;
        std::nth_element(a.begin()+l,a.begin()+mid,a.begin()+r+1,
            [ax](const array<T,D>& u,const array<T,D>& v){ return u[ax]<v[ax]; });
        Node* x=new Node(a[mid]);
        x->axis=ax;
        x->left=build(a,l,mid-1);
        x->right=build(a,mid+1,r);
        push_up(x);
        return x;
    }

    static ld dist2_point(const array<T,D>& a,const array<T,D>& b) {
        ld res=0;
        for(int k=0;k<D;k++) {
            ld d=(ld)a[k]-(ld)b[k];
            res+=d*d;
        }
        return res;
    }

    static ld dist2_box(const Node* x,const array<T,D>& q) {
        ld res=0;
        for(int k=0;k<D;k++) {
            ld v=(ld)q[k];
            if(v<(ld)x->mn[k]) res+=((ld)x->mn[k]-v)*((ld)x->mn[k]-v);
            else if(v>(ld)x->mx[k]) res+=(v-(ld)x->mx[k])*(v-(ld)x->mx[k]);
        }
        return res;
    }

    void nearest(Node* x,const array<T,D>& q,array<T,D>& best_p,ld& best) const {
        if(!x) return ;
        ld d0=dist2_point(x->p,q);
        if(d0<best) { best=d0;best_p=x->p; }
        Node* first;
        Node* second;
        if((ld)q[x->axis]<(ld)x->p[x->axis]) { 
            first=x->left;
            second=x->right;
        }
        else {
            first=x->right;
            second=x->left;
        }
        if(first) {
            ld dist_box=dist2_box(first,q);
            if(dist_box<=best) nearest(first,q,best_p,best);
        }
        if(second) {
            ld dist_box=dist2_box(second,q);
            if(dist_box<=best) nearest(second,q,best_p,best);
        }
    }

    void range_query(Node* x,const array<T,D>& low,const array<T,D>& high,vector<array<T,D>>& out) const {
        if(!x) return ;
        for(int k=0;k<D;k++) {
            if(x->mn[k]>high[k]||x->mx[k]<low[k]) return ;
        }
        bool in=true;
        for(int k=0;k<D;k++) {
            if(x->p[k]<low[k]||x->p[k]>high[k]) { in=false;break; }
        }
        if(in) out.push_back(x->p);
        range_query(x->left,low,high,out);
        range_query(x->right,low,high,out);
    }
};

template<typename T,size_t D>
static void print_pt(const array<T,D>& p) {
    cout<<"(";
    for(size_t i=0;i<D;i++) {
        if(i) cout<<",";
        cout<<p[i];   
    }
    cout<<")";
}

int main() {
    using Pt=array<double,2>;
    KDTree<double,2> kdt;
    vector<Pt> pts={
        {0.0,0.0},{1.0,2.0},{3.0,1.0},{-1.0,4.0},{2.0,2.0},
        {5.0,5.0},{-2.0,-1.0},{4.0,0.5},{2.5,3.0},{-3.0,2.0}
    };
    kdt.build(pts);
    cout<<"[Build] size = "<<kdt.size()<<"\n";

    vector<Pt> queries={ {1.6,1.4},{4.2,0.2},{-2.2, 2.1},{100.0,100.0} };
    cout<<"\n[Nearest]\n";
    for(auto &q:queries) {
        auto ans=kdt.nearest(q);
        const Pt& best=ans.first;
        ld d2=ans.second;
        cout<<"  q="; 
        print_pt(q);
        cout<<" -> nn="; 
        print_pt(best);
        cout<<"  dist2="<<d2<<"\n";
    }

    Pt low{0.0, 0.0},high{3.0, 3.0};
    vector<Pt> in_box;
    kdt.range_query(low,high,in_box);
    cout<<"\n[Range Query] box: ";
    print_pt(low);
    cout<< " .. "; 
    print_pt(high);
    cout<< "\n";
    cout<<"  count = "<<in_box.size()<<"\n";
    cout<<"  points:";
    for(auto &p:in_box) { cout<<" ";print_pt(p); }
    cout<<"\n";
    return 0;
}