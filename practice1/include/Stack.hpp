#pragma once
#include"List.hpp"
#include<stdexcept>

template<typename T>
class Stack
{
private:
    List<T> list_;
public:
    bool empty() const { return list_.empty(); }

    std::size_t size() const { return list_.size(); }

    void push(const T& val) { list_.push_front(val); }
    void pop() { list_.pop_front(); }

    T& top() { return list_.front(); }
};