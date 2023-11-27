/*
 * @Author: zanilia
 * @Date: 2021-12-14 10:42:55
 * @LastEditTime: 2022-03-29 11:11:34
 * @Descripttion: 
 */
#include "../sort.hpp"
#include <cstdlib>
#include <assert.h>
#include "../function.hpp"
int main(){
    // Vector<int> v;
    int v[10000];
    for(int i=0;i<8000;++i){
        int size = rand()%10000;
        for(int i=0;i<size;++i)
            v[i] = rand();
        Less<int> cmp;
        InsertSort(v,v+size,cmp);
        for(int i=1;i<size;++i)
            assert(v[i-1]<=v[i]);
    }
    return 0;
}