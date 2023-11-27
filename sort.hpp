/*
 * @Author: zanilia
 * @Date: 2021-10-18 19:35:06
 * @LastEditTime: 2022-03-29 11:11:14
 * @Descripttion: 
 */
#include "function.hpp"
#include "heap.hpp"
#include "move.hpp"
#include "iterator.hpp"
#define threshold 16
template <class Size>
inline Size _lg(Size n){
    Size k;
	for (k = 0; n > 1; n >>= 1) 
        ++k;
	return k;
}
template<class RandomAccessIterator>
void sort(RandomAccessIterator begin,RandomAccessIterator end){
    Less<typename iterator_traits<RandomAccessIterator>::value_type> cmp;
    sort(begin,end,cmp);
}
template<class RandomAccessIterator,class Compare>
void sort(RandomAccessIterator begin,RandomAccessIterator end,Compare cmp){
    if(begin!=end){
        introSort(begin,end,_lg((begin-end)<<1),cmp);
        // finalInsertionSort(begin,end,cmp);
        InsertSort(begin,end,cmp);
    }
}
// find the median and swap the median and result
template<class RandomAccessIterator,class Compare>
void getPivot(
    RandomAccessIterator result,
    RandomAccessIterator a,
    RandomAccessIterator b,
    RandomAccessIterator c,
    Compare cmp)
{
    if(cmp(*a,*b))
        if(cmp(*b,*c))
            iter_swap(b,result);
        else
            if(cmp(*a,*c))
                iter_swap(c,result);
            else
                iter_swap(a,result);
    else
        if(cmp(*a,*c))
            iter_swap(a,result);
        else
            if(cmp(*b,*c))
                iter_swap(c,result);
            else
                iter_swap(b,result);
}
template<class RandomAccessIterator,class Compare>
RandomAccessIterator getPartion(RandomAccessIterator begin,RandomAccessIterator end,Compare cmp){
    RandomAccessIterator mid = begin + (end-begin)/2;
    getPivot(begin,begin+1,mid,end-1,cmp);
    RandomAccessIterator pivot = begin;
    ++begin;
    while(true){
        while(cmp(*begin,*pivot))
            ++begin;
        --end;
        while(cmp(*pivot,*end))
            --end;
        if(!(begin<end))
            return begin;
        iter_swap(begin,end);
        ++begin;
    }
}

template<class RandomAccessIterator,class Size,class Compare>
void introSort(RandomAccessIterator begin,RandomAccessIterator end,Size depth_limit,Compare cmp){
    while(end-begin>=threshold){
        if(depth_limit==0){
            heapSort(begin,end,cmp);
            return ;
        }
        --depth_limit;
        RandomAccessIterator cut = getPartion(begin,end,cmp);
        introSort(cut,end,depth_limit,cmp);
        end = cut;
    }
}
template<class RandomAccessIterator,class Compare>
void InsertSort(RandomAccessIterator begin,RandomAccessIterator end,Compare cmp){
    if(begin==end)
        return ;
    RandomAccessIterator j = begin+1;
    while(j!=end){
        typename iterator_traits<RandomAccessIterator>::value_type val = move(*j);
        RandomAccessIterator i = j-1;
        while(i>=begin&&cmp(val,*i)){
            iter_swap(i,i+1);
            --i;
        }
        *(i+1) = move(val);
        ++j;
    }
}
template<class RandomAccessIterator,class Compare>
void heapSort(RandomAccessIterator begin,RandomAccessIterator end,Compare cmp){
    heapify(begin,end,cmp);
    unsigned size = end - begin;
    while(end!=begin){
        --end;
        typename iterator_traits<RandomAccessIterator>::value_type tem = move(*end);
        *end = move(*begin);
        *begin = move(tem);
        --size;
        downAdjust(begin,0,size,cmp);
    }
}
template<class Iterator,class Compare>
void merge_move(Iterator begin,Iterator mid,Iterator end,Compare cmp){
    Iterator begin2 = (++mid); 
    unsigned size = end - begin;
    Iterator begin1 = begin;
    typename iterator_traits<Iterator>::value_type tem[size];
    typename iterator_traits<Iterator>::value_type* result = tem;
    while(begin1!=mid&&begin2!=end){
        if(cmp(*begin1,*begin2)){
            *result = move(*begin1);
            ++begin1;
        }
        else{
            *result = move(*begin2);
            ++begin2;
        }
        ++result;
    }
    if(begin1!=mid)
        move(begin1,mid,result);
    else
        move(begin2,end,result);
    move(tem,tem+size,begin);
}
template<class Iterator,class Compare>
void mergeSort(Iterator begin,Iterator end,Compare cmp){
    if(begin+1>=end)
        return ;
    unsigned n = end - begin;
    Iterator mid = begin + n /2;
    mergeSort(begin,mid,cmp);
    mergeSort(mid,end,cmp);
    merge_move(begin,mid,end,cmp);
}
template<class RandomAccessIterator>
void mergeSort(RandomAccessIterator begin,RandomAccessIterator end){
    Less<typename iterator_traits<RandomAccessIterator>::value_type> cmp;
    return mergeSort(begin,end,cmp);
}