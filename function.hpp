/*
 * @Author: zanilia
 * @Date: 2021-11-02 10:23:30
 * @LastEditTime: 2021-12-07 23:51:05
 * @Descripttion: 
 */
#ifndef __FUNCTIONAL__H__
#define __FUNCTIONAL__H__
template<class ValueType>
class Greater{
public:
    bool operator()(const ValueType& a,const ValueType& b){
        return a>b;
    }
};
template<class ValueType>
class Less{
public:
    bool operator()(const ValueType& a,const ValueType& b){
        return a<b;
    }
};
template<class ValueType>
class Equal{
public:
    bool operator()(const ValueType& a,const ValueType& b){
        return a==b;
    }
};
unsigned hash(char* s,unsigned size){
    unsigned ret = 0;
    for(int i=0;i<size;++i,++s)
        ret = (ret<<4) + (*s);
    return ret;
}
template<class ValueType>
class Hash{
public:
    unsigned operator()(const ValueType& a){
        return hash((char*)&a,sizeof(ValueType));
    }
};

#endif