#ifndef __VECTOR__
#define __VECTOR__
template<class DataType>
class Vector{
private:
    DataType* _data;
    unsigned int _size;
    unsigned int _capacity;
public:
    class iterator;
    Vector():_data(new DataType[20]),_size(0),_capacity(20){}
    Vector(const Vector& other) = default;
    Vector(const Vector&& other):_data(other._data),_size(other._size),_capacity(other._capacity){}
    Vector(unsigned int capacity):_capacity(capacity),_size(0),_data(new DataType[_capacity]){}
    void push_back(const DataType& data);
    DataType& pop_back();
    DataType& operator[](unsigned int i);
    unsigned int size();
    bool empty();
    void insert(unsigned int pos,const DataType& data);
    void insert(iterator pos,const DataType& data);
    // void insert(iterator pos,const DataType& data,int num);
    // void insert(unsigned int pos,const DataType& data,int num);
    void clear();
    void erase(unsigned int pos);
    void erase(iterator pos);
    void erase(iterator first,iterator last);
    void reserve(unsigned int capacity);
    iterator begin();
    iterator end();
};
template<class DataType>
void Vector<DataType>::push_back(const DataType& data){
    if(_size==_capacity)
        reserve(_capacity<<1);
    _data[_size++] = data;
}
template<class DataType>
DataType& Vector<DataType>::pop_back(){
    return _data[--_size];
}
template<class DataType>
DataType& Vector<DataType>::operator[](unsigned int i){
    if(i>=_size)
        throw -1;
    return _data[i];
}
template<class DataType>
unsigned int Vector<DataType>::size(){
    return _size;
}
template<class DataType>
bool Vector<DataType>::empty(){
    return _size==0;
}
template<class DataType>
void Vector<DataType>::clear(){
    _size = 0;
}
template<class DataType>
void Vector<DataType>::reserve(unsigned int capacity){
    if(capacity>_capacity){
        DataType *tem = new DataType [capacity];
        capacity = _capacity;
        for(int i=0;i<_size;++i)
            tem[i] = _data[i];
        delete []_data;
        _data = tem;
    }
}

template<class DataType>
void Vector<DataType>::insert(iterator pos,const DataType& data){
    if(_size==_capacity)
        reserve(_capacity<<1);
    move_backforward(pos,iterator(_data+_size),pos+1);
    *pos = move(data);
}

template<class DataType>
void Vector<DataType>::insert(unsigned int pos,const DataType& data){
    if(_size==_capacity)
        reserve(_capacity<<1);
    move_backforward(_data+pos,_data+_size,_data+pos+1);
    _data[pos] = data;
    ++_size;
}

template<class DataType>
void Vector<DataType>::erase(unsigned int pos){
    if(pos>=_size)
        return ;
    if(pos==_size-1){
        --_size;
        return ;
    }
    move_backforward(_data+pos+1,_data+_size,_data+pos);
    --_size;
}

template<class DataType>
void Vector<DataType>::erase(iterator pos){
    if(pos==end())
        return ;
    if(pos+1==end()){
        --_size;
        return ;
    }
    move_backforward(pos+1,end(),pos);
    --_size;
}
template<class DataType>
void Vector<DataType>::erase(iterator first,iterator last){
    iterator _end = end();
    if(first==_end)
        return ;
    if(last>_end){
        _size -= 1;
        return ;
    }
    move_backforward(first,last,last);
    _size -= (last - first);
}

template<class DataType>
typename Vector<DataType>::iterator Vector<DataType>::begin(){
    return _data;
}
template<class DataType>
typename Vector<DataType>::iterator Vector<DataType>::end(){
    return _data+_size;
}

// RandomAccessIterator for vector
template<class DataType>
class Vector<DataType>::iterator{
    DataType* p;
public:
    iterator():p(NULL){}
    iterator(DataType *p1):p(p1){}
    typedef DataType value_type;
    const iterator& operator++(){
        ++p;
        return *this;
    }
    const iterator& operator--(){
        --p;
        return *this;
    }
    bool operator< (const iterator& other){
        return p < other.p;
    }
    bool operator<= (const iterator& other){
        return p <= other.p;
    }
    bool operator> (const iterator& other){
        return p > other.p;
    }
    bool operator>= (const iterator& other){
        return p >= other.p;
    }
    bool operator== (const iterator& other){
        return p == other.p;
    }
    bool operator!= (const iterator& other){
        return p != other.p;
    }
    iterator operator-(unsigned int n){
        return iterator(p-n);
    }
    iterator operator+(unsigned int n){
        return iterator(p+n);
    }
    unsigned operator-(iterator i){
        return p-i.p;
    }
    friend typename Vector<DataType>::iterator operator+(unsigned int n,typename Vector<DataType>::iterator i);
    friend typename Vector<DataType>::iterator operator-(unsigned int n,typename Vector<DataType>::iterator i);
    value_type& operator*(){
        return *p;
    }
    value_type& operator[](const unsigned int n){
        return *(p+n);
    }
};
template<class DataType>
typename Vector<DataType>::iterator operator+(unsigned int n,typename Vector<DataType>::iterator i){
    return Vector<DataType>::iterator(i.p+n);
}
template<class DataType>
typename Vector<DataType>::iterator operator-(unsigned int n,typename Vector<DataType>::iterator i){
    return Vector<DataType>::iterator(i.p-n);
}
#endif