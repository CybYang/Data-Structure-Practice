#pragma once
#include"List.hpp"
#include<stdexcept>

template<typename T>
class Queue
{
private:
    List<T>list_;
public:
    bool empty() const { return list_.empty(); }

    std::size_t size() const { return list_.size(); }

    void push(const T& val) { list_.push_back(val); }
    void pop() { list_.pop_front(); }

    T& front() { return list_.front(); }
    T& back() { return list_.back(); }

};