#include<iostream>
#include<vector>
#include<cstring>
#include<stack>

using std::stack;
using std::vector;
using std::max;

template<typename T>
class AVLTree {
public:
    class Node {
    public:
        T val;
        Node* left;
        Node* right;
        int h;
        explicit Node(const T& v):val(v),left(nullptr),right(nullptr),h(1) {}
    };

private:
    Node* root_=nullptr;
    size_t sz_=0;

public:
    AVLTree()=default;
    ~AVLTree() { clear(); }

    bool empty() const { return sz_==0; }

    size_t size() const { return sz_; }

    bool Find(const T& x) const {
        Node* cur=root_;
        while(cur) {
            if(x==cur->val) return true;
            else if(x<cur->val) cur=cur->left;
            else cur=cur->right;
        }
        return false;
    }

    void insert(const T& x) {
        if(!root_) { root_=new Node(x);sz_++;return ; }
        stack<Node*> path;
        Node* cur=root_;
        while(cur) {
            path.push(cur);
            if(x<cur->val) {
                if(!cur->left) { cur->left=new Node(x);sz_++;path.push(cur->left);break; }
                cur=cur->left;
            }
            else if(x>cur->val) {
                if(!cur->right) { cur->right=new Node(x);sz_++;path.push(cur->right);break; }
                cur=cur->right;
            }
            else return ;
        }
        path.pop();
        while(!path.empty()) {
            Node* p=path.top();path.pop();
            push_up(p);
            Node* q=balance(p);
            if(path.empty()) root_=q;
            else {
                Node* fa=path.top();
                if(fa->left==p) fa->left=q;
                else fa->right=q;
            }
        }
    }

    void erase(const T& x) {
        if(!root_) return ;
        stack<Node*> path;
        Node* cur=root_;
        while(cur&&cur->val!=x) {
            path.push(cur);
            if(x<cur->val) cur=cur->left;
            else cur=cur->right;
        }
        if(!cur) return ;
        if(cur->left&&cur->right) {
            path.push(cur);
            Node* x=cur->right;
            while(x->left) {
                path.push(x);
                x=x->left;
            }
            cur->val=x->val;
            cur=x;
        }
        Node* tmp=cur->left?cur->left:cur->right;
        if(path.empty()) {
            delete cur;
            root_=tmp;
            sz_--;
        }
        else {
            Node* fa=path.top();
            if(fa->left==cur) fa->left=tmp;
            else fa->right=tmp;
            delete cur;
            sz_--;
        }
        while(!path.empty()) {
            Node* p=path.top();path.pop();
            push_up(p);
            Node* q=balance(p);
            if(path.empty()) root_=q;
            else {
                Node* fa=path.top();
                if(fa->left==p) fa->left=q;
                else fa->right=q;
            }
        }
    }

    void preorder(std::vector<T>& res) const {
        if(!root_) return ;
        stack<Node*> S;S.push(root_);
        while(!S.empty()) {
            Node* cur=S.top();S.pop();
            res.push_back(cur->val);
            if(cur->right) S.push(cur->right);
            if(cur->left) S.push(cur->left);
        }
    }
    void inorder(std::vector<T>& res) const {
        if(!root_) return ;
        stack<Node*> S;
        Node* cur=root_;
        while(cur||!S.empty()) {
            while(cur) { S.push(cur);cur=cur->left; }
            cur=S.top();S.pop();
            res.push_back(cur->val);
            cur=cur->right;
        }
    }
    void postorder(std::vector<T>& res) const {
        if(!root_) return ;
        stack<Node*> S;
        Node* cur=root_;
        Node* pre=nullptr;
        while(cur||!S.empty()) {
            if(cur) { S.push(cur);cur=cur->left; }
            else {
                Node* s=S.top();
                if(s->right&&pre!=s->right) cur=s->right;
                else {
                    res.push_back(s->val);
                    pre=s;
                    S.pop();
                }
            }
        }
    }

    void clear() {
        Node* cur=root_;
        Node* pre=nullptr;
        stack<Node*> S;
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

private:
    static int height(Node* x) { return x?x->h:0; }
    static int check(Node* x) { return x?height(x->left)-height(x->right):0; }

    static void push_up(Node* x) {
        if(!x) return ;
        int hl=height(x->left);int hr=height(x->right);
        x->h=max(hl,hr)+1;
    }

    static Node* balance(Node* x) {
        if(!x) return nullptr;
        int dir=check(x);
        if(dir<-1) {
            if(check(x->right)>0) x->right=rotateRight(x->right);
            return rotateLeft(x);
        }
        else if(dir>1) {
            if(check(x->left)<0) x->left=rotateLeft(x->left);
            return rotateRight(x);
        }
        else return x;
    }

    static Node* rotateRight(Node* x) {
        Node* y=x->left;
        Node* z=y->right;
        y->right=x;
        x->left=z;
        push_up(x);
        push_up(y);
        return y;
    }
    static Node* rotateLeft(Node* x) {
        Node* y=x->right;
        Node* z=y->left;
        y->left=x;
        x->right=z;
        push_up(x);
        push_up(y);
        return y;
    }
};
int main() {
    AVLTree<int> avl;
    for (int v:{5,3,8,1,4,7,9,2,6}) avl.insert(v);
    std::vector<int> pre,in,post;
    avl.preorder(pre);
    avl.inorder(in);
    avl.postorder(post);
    auto print=[](std::string name,const std::vector<int>& a) {
        std::cout<<name<<":"<<"\n";
        for(int x:a) std::cout<<x<<" ";
        std::cout<<"\n";
    };
    print("Preorder",pre);
    print("Inorder",in);
    print("Postorder",post);
    for(int v:{1,3,5,7,9}) avl.erase(v);
    pre.clear();in.clear();post.clear();
    avl.preorder(pre);
    avl.inorder(in);
    avl.postorder(post);
    print("Preorder after deletions",pre);
    print("Inorder after deletions",in);
    print("Postorder after deletions",post);
    return 0;
}