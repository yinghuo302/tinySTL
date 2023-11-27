/*
 * @Author: zanilia
 * @Date: 2021-11-02 10:22:24
 * @LastEditTime: 2022-03-28 23:22:16
 * @Descripttion: 
 */
#ifndef __HEAP__H__
#define __HEAP__H__
#include "function.hpp"
#include "iterator.hpp"
template<class DataType,class Compare = Less<DataType>>
class Heap {
private:
    DataType* _data;
    unsigned _size; //当前大小
    unsigned _capacity; //总容量
    void upAdjust();
    void downAdjust(int low=1);
public:
    Heap(); 
    Heap(unsigned Capacity);
    ~Heap();
    void push(const DataType& element); 
    const DataType& pop();
    const DataType& top();
    bool empty();
    unsigned int size(); 
    unsigned capacity();
};
template<class DataType,class Compare>
Heap<DataType,Compare>::Heap():_size(0),_capacity(20),_data(new DataType[21]){}

template<class DataType,class Compare>
Heap<DataType,Compare>::Heap(unsigned capacity):_size(0),_capacity(capacity),_data(new DataType[capacity+1]){}

template<class DataType,class Compare>
Heap<DataType,Compare>::~Heap(){
    delete[] _data;
    _size = 0;
    _capacity = 0;
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::upAdjust(){
    unsigned element_need_adjust = _size, parent = _size>>1;
    Compare cmp;
    while (parent>=1){
        if(!cmp(_data[element_need_adjust],_data[parent])){
            DataType tem = _data[element_need_adjust];
            _data[element_need_adjust] = _data[parent];
            _data[parent] = tem;
            element_need_adjust >>= 1;
            parent >>= 1;
        }
        else
            break;
    } 
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::downAdjust(int low){
    unsigned child = low<<1;
    Compare cmp;
    while (child <=_size){
        if(child<_size&&cmp(_data[child],_data[child+1]))
            ++child;
        if(cmp(_data[low],_data[child])){
            DataType tem = _data[low];
            _data[low] = _data[child];
            _data[child] = tem;
            low = child;
            child = low << 1;
        }
        else
            break;
    }
}

template<class DataType,class Compare>
void Heap<DataType,Compare>::push(const DataType& element){
    if(_size == _capacity){
        _capacity += 20;
        DataType* tem = new DataType[_capacity+1];
        for(unsigned i =1;i<=_size;++i)
            tem[i] = _data[i];
        delete[] _data;
        _data = tem;
    }
    _data[++_size] = element;
    upAdjust();
} 

template<class DataType,class Compare>
const DataType& Heap<DataType,Compare>::pop(){
    _data[0] = _data[1];
    _data[1] = _data[_size];
    --_size;
    downAdjust();
    return _data[0];
}

template<class DataType,class Compare>
const DataType& Heap<DataType,Compare>::top(){
    return _data[1];
}

template<class DataType,class Compare>
bool Heap<DataType,Compare>::empty(){
    return (_size==0);
}

template<class DataType,class Compare>
unsigned Heap<DataType,Compare>::size(){
    return _size;
}

template<class DataType,class Compare>
unsigned Heap<DataType,Compare>::capacity(){
    return _capacity;
}

template<class RandomAccessIterator,class Compare>
void heapify(RandomAccessIterator begin,RandomAccessIterator end,Compare cmp){
    unsigned size = end-begin;
    if(size<2)
        return ;
    unsigned parent = (size-2) / 2;
    while(true){
        downAdjust(begin,parent,size,cmp);
        if(parent==0)
            return ;
        --parent;
    }
}
template<class RandomAccessIterator,class Compare>
void downAdjust(RandomAccessIterator begin,unsigned index,unsigned size,Compare cmp){
    --begin;
    ++index;
    unsigned child = index<<1;
    while (child <=size){
        if(child<size&&cmp(begin[child],begin[child+1]))
            ++child;
        if(cmp(begin[index],begin[child])){
            typename iterator_traits<RandomAccessIterator>::value_type tem = begin[index];
            begin[index] = begin[child];
            begin[child] = tem;
            index = child;
            child = index << 1;
        }
        else
            break;
    }
}
template<class RandomAccessIterator,class Compare>
void upAdjust(RandomAccessIterator begin,unsigned index,Compare cmp){
    --begin;
    ++index;
    unsigned parent = index>>1;
    while (parent>=1){
        if(!cmp(begin[index],begin[parent])){
            typename iterator_traits<RandomAccessIterator>::value_type tem = begin[index];
            begin[index] = begin[parent];
            begin[parent] = tem;
            index >>= 1;
            parent >>= 1;
        }
        else
            break;
    } 
}
#endif