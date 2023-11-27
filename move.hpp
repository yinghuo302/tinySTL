/*
 * @Author: zanilia
 * @Date: 2021-11-05 18:27:20
 * @LastEditTime: 2022-03-29 14:55:43
 * @Descripttion: 
 */
#ifndef __MOVE__H__
#define __MOVE__H__
template<class DataType>
inline DataType&& move(DataType& data){
    return static_cast<DataType&&>(data);
}
template<class InputIterator,class OutputIterator>
inline void move(InputIterator begin,InputIterator end,OutputIterator result){
    while(begin!=end){
        *result = move(*end);
        ++result;
        ++begin;
    }
}
template<class Iterator>
void move_backforward(Iterator begin,Iterator last,Iterator dest){
    while(begin!=last){
        *dest = move(*begin);
        ++dest;
        ++begin;
    }
}
#endif