/*
 * @Author: zanilia
 * @Date: 2021-07-22 00:20:05
 * @LastEditTime: 2021-11-23 10:44:07
 * @Descripttion: 
 */
#include <assert.h>
template<class DataType>
class Stack{
    DataType* arr;
    unsigned _size;
    unsigned capacity;
public:
    Stack():data(new DataType(10)),_size(0),capacity(10){}
    Stack(unsigned _capacity):capacity(_capacity),_size(0),data(new DataType(_capacity)){}
    void push(const DataType& data){
        if(_size==capacity)
            reserve(capacity<<1);
        arr[_size++] = data;
    }
    DataType& pop(){
        assert(_size);
        return arr[--_size];
    }
    DataType& top(){
        return arr[_size-1];
    }
    unsigned size(){
        return _size;
    }
    bool empty(){
        return _size;
    }
    void reserve(unsigned _capacity){
        if(_capacity<=capacity)
            return ;
        DataType* tem = new DataType(_capacity);
        for(int i =0;i<_size;++i)
            tem[i] = arr[i];
        capacity = _capacity;
        delete(arr);
        arr = tem;
    }
};