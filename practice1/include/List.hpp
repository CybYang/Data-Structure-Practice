#pragma once
#include<cstddef>
#include<stdexcept>

template<typename T>
class List
{

private:
    struct Node
    {
        T val;
        Node* next;
        Node(const T& v):val(v),next(nullptr) {}
    };
    Node* head_;
    Node* tail_;
    std::size_t size_;

public:
    List():head_(nullptr),tail_(nullptr),size_(0) {}
    ~List() { clear();}

    List(const List&)=delete;
    List& operator=(const List&)=delete;

    void clear()
    {
        Node* cur=head_;
        while(cur!=nullptr)
        {
            Node* tmp=cur->next;
            delete cur;
            cur=tmp;
        }
        head_=tail_=nullptr;
        size_=0;
    }

    bool empty() const { return size_==0; }

    std::size_t size() const { return size_; }

    void push_back(const T& val)
    {
        Node* newNode=new Node(val);
        if(tail_==nullptr) head_=tail_=newNode;
        else { tail_->next=newNode;tail_=newNode; }
        size_++;
    }
    void push_front(const T& val)
    {
        Node* newNode=new Node(val);
        if(head_==nullptr) head_=tail_=newNode;
        else { newNode->next=head_;head_=newNode; }
        size_++;
    }

    void pop_back()
    {
        if(tail_==nullptr) throw std::out_of_range("Pop_back on an empty List!");
        if(head_==tail_) { delete head_;head_=tail_=nullptr; }
        else
        {
            Node* cur=head_;
            while(cur->next!=tail_) cur=cur->next;
            delete tail_;
            tail_=cur;
            tail_->next=nullptr;
        }
        size_--;
    }
    void pop_front()
    {
        if(head_==nullptr) throw std::out_of_range("Pop_front on an empty List!");
        Node* tmp=head_->next;
        delete head_;
        head_=tmp;
        if(head_==nullptr) tail_=nullptr;
        size_--;
    }

    T& front()
    {
        if(head_==nullptr) throw std::out_of_range("Front on an empty List!");
        return head_->val;
    }
    T& back()
    {
        if(tail_==nullptr) throw std::out_of_range("Back on an empty List!");
        return tail_->val;
    }

    const T& front() const
    {
        if(head_==nullptr) throw std::out_of_range("Front on an empty List!");
        return head_->val;
    }
    const T& back() const
    {
        if(tail_==nullptr) throw std::out_of_range("Back on an empty List!");
        return tail_->val;
    }
};