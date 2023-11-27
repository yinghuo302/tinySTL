/*
 * @Author: zanilia
 * @Date: 2022-06-15 14:07:58
 * @LastEditTime: 2022-07-24 17:18:06
 * @Descripttion: 
 */
#include "iterator.hpp"
// template<class RAIterator>
// RAIterator upperBound(RAIterator begin,RAIterator end,typename iterator_traits<RAIterator>::value_type val){
// 	while(begin!=end){
// 		RAIterator mid = (end-begin)/2+begin;
// 		if(*mid>val)
// 			end = mid;
// 		else
// 			begin = mid+1;
// 	}
// 	return begin;
// }
// template<class RAIterator,class Cmp>
// RAIterator upperBound(RAIterator begin,RAIterator end,typename iterator_traits<RAIterator>::value_type val,Cmp cmp){
// 	while(begin!=end){
// 		RAIterator mid = (end-begin)/2+begin;
// 		if(cmp(*mid,val))
// 			end = mid;
// 		else
// 			begin = mid+1;
// 	}
// 	return begin;
// }
template<class RAIterator>
RAIterator lowerBound(RAIterator begin,RAIterator end,typename iterator_traits<RAIterator>::value_type val){
	while(begin!=end){
		RAIterator mid = (end-begin)/2+begin;
		if(*mid<val)
			end = mid -1;
		else
			begin = mid;
	}
	return begin;
}
template<class RAIterator,class Cmp>
RAIterator lowerBound(RAIterator begin,RAIterator end,typename iterator_traits<RAIterator>::value_type val,Cmp cmp){
	while(begin!=end){
		RAIterator mid = (end-begin)/2+begin;
		if(cmp(*mid,val))
			end = mid;
		else
			begin = mid+1;
	}
	return begin;
}
template<class RAIterator,class Cmp>
RAIterator binarySearch(RAIterator begin,RAIterator end,typename iterator_traits<RAIterator>::value_type val,Cmp cmp){
	RAIterator i = end;
	while(begin!=end){
		RAIterator mid = (end-begin)/2+begin;
		int t = cmp(*mid,val);
		if(t==0)
			return mid;
		else if(t>0)
			end = mid-1;
		else
			begin = mid+1;
	}
	return i;
}
template<class RAIterator,class Function>
RAIterator binarySearch(RAIterator begin,RAIterator end,Function check){
	if(check(begin)==1||check(end-1)==-1)
		return end;
	RAIterator ret = end;
	while(begin<end){
		RAIterator mid = (end-begin)/2+begin;
		int t = check(mid);
		if(t==0)
			return mid;
		else if(t>0)
			end = mid;
		else
			begin = mid+1;
	}
	return ret;
}
/**
 * @return {RAIterator} return the first iterator i that f(i) = 1.
 * @param {RAIterator} begin
 * @param {RAIterator} end
 * @param {Function} f the parameter of f is RAITERATOR and {f(i)} = {-1,0,1};
 */
template<class RAIterator,class Function>
RAIterator upperBound(RAIterator begin,RAIterator end,Function f){
	RAIterator ret = end;
	if(f(--end)<=0)
		return ret;
	while(begin<end){
		RAIterator mid = (end-begin)/2+begin;
		int t = f(mid);
		if(t>0)
			end = mid;
		else
			begin = mid+1;
	}
	return begin;
}
/**
 * @return {RAIterator} return the first iterator i that f(i) = 1.
 * @param {RAIterator} begin
 * @param {RAIterator} end
 * @param {Median} a function that returns the median of two iterator
 * @param {Function} f the parameter of f is RAITERATOR and {f(i)} = {-1,0,1};
 */
template<class RAIterator,class Median,class Function>
RAIterator upperBound(RAIterator begin,RAIterator end,Median median,Function f){
	RAIterator ret = end;
	if(f(--end)<=0)
		return ret;
	while(begin<end){
		RAIterator mid = median(begin,end);
		int t = f(mid);
		if(t>0)
			end = mid;
		else
			begin = mid+1;
	}
	return begin;
}