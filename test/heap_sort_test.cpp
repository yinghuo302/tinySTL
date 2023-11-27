/*
 * @Author: zanilia
 * @Date: 2021-11-05 23:14:52
 * @LastEditTime: 2022-03-28 23:51:37
 * @Descripttion: 
 */
#include "../sort.hpp"
#include <cstdlib>
#include <assert.h>
#include "../function.hpp"
int main(){
   int v[80000];
    for(int i=0;i<80000;++i){
        int size = rand()%80000;
        for(int i=0;i<size;++i)
            v[i] = rand();
        Less<int> cmp;
        heapSort(v,v+size,cmp);
        for(int i=1;i<size;++i)
            assert(v[i-1]<=v[i]);
    }
    return 0;
}