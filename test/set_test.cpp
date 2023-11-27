/*
 * @Author: zanilia
 * @Date: 2021-12-16 10:38:20
 * @LastEditTime: 2022-03-29 16:40:51
 * @Descripttion: 
 */
#include <unordered_set>
#include <cstdlib>
#include "../unordered_set.hpp"
#include <assert.h>
int main(){
    UnorderedSet<int> my;
    std::unordered_set<int> stl; 
    for(int i=0;i<30000;++i){
        int tem = rand();
        my.emplace(tem);
        stl.emplace(tem);
    }
    for(int i=0;i<10000;++i){
        int tem = rand();
        bool has_tem_1 = my.find(tem);
        bool has_tem_2 = stl.find(tem)==stl.end();
        assert(has_tem_1==has_tem_2);
    }
    return 0;
}