/*
 * @Author: zanilia
 * @Date: 2021-11-05 23:09:31
 * @LastEditTime: 2022-01-02 22:21:18
 * @Descripttion: 
 */
#include "../heap.hpp"
#include <cstdlib>
#include <assert.h>
#include <iostream>
int main(){
    Heap<int> h;
    for(int i=0;i<80000;++i)
        h.push(rand());
    int prev = 0,curr = h.pop();
    for(int i=1;i<80000;++i){
        prev = curr;
        curr = h.pop();
        assert(prev>=curr);
    }
    return 0;
}