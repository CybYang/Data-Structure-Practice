#pragma once
#include<utility>
template<typename T,typename Compare>
inline int partition(T a[],int l,int r,Compare cmp)
{
    T pivot=a[l];
    int i=l;
    for(int j=i+1;j<=r;j++)
        if(cmp(a[j],pivot)) { i++;std::swap(a[i],a[j]); }
    std::swap(a[i],a[l]);
    return i;
}

template<typename T,typename Compare>
inline void quick_sort(T a[],int l,int r,Compare cmp)
{
    if(l>=r) return;
    int mid=partition(a,l,r,cmp);
    quick_sort(a,l,mid-1,cmp);
    quick_sort(a,mid+1,r,cmp);
    return;
}

template<typename T>
inline void quick_sort(T a[],int l,int r)
{
    quick_sort(a,l,r,[](const T& x,const T& y) { return x<y; }); 
}

/*

    #pragma once
    #include <iterator>   // iterator_traits
    #include <functional> // std::less
    #include <utility>    // std::iter_swap

    namespace algo {

    template <class RandomIt, class Compare>
    void quick_sort(RandomIt first, RandomIt last, Compare comp) {
        if (first == last || first + 1 == last) return;
        auto pivot = *first;
        RandomIt i = first;
        for (RandomIt j = first + 1; j < last; ++j) {
            if (comp(*j, pivot)) { ++i; std::iter_swap(i, j); }
        }
        std::iter_swap(i, first);
        quick_sort(first, i, comp);
        quick_sort(i + 1, last, comp);
    }

    template <class RandomIt>
    void quick_sort(RandomIt first, RandomIt last) {
        using T = typename std::iterator_traits<RandomIt>::value_type;
        quick_sort(first, last, std::less<T>{});
    }

    template <class T, class Compare>
    void quick_sort(std::vector<T>& v, Compare comp) {
        quick_sort(v.begin(), v.end(), comp);
    }
    template <class T>
    void quick_sort(std::vector<T>& v) {
        quick_sort(v.begin(), v.end());
    }

    } // namespace algo


*/