/*
 * @Author: zanilia
 * @Date: 2021-11-05 10:43:24
 * @LastEditTime: 2022-06-17 21:24:10
 * @Descripttion: 
 */
#ifndef __ITERATOR__H__
#define __ITERATOR__H__
#include "move.hpp"
template <class Iterator>
struct iterator_traits{
    typedef typename Iterator::value_type value_type;
};
template <class ValueType>
struct iterator_traits<ValueType*>{
    typedef ValueType value_type;
};
template <class Iterator>
void iter_swap(Iterator x,Iterator y){
    typename iterator_traits<Iterator>::value_type tem = move(*x);
    *x = move(*y);
    *y = move(tem);
}
#endif