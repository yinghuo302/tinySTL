/*
 * @Author: zanilia
 * @Date: 2022-03-28 20:45:01
 * @LastEditTime: 2022-03-29 16:21:16
 * @Descripttion: 
 */
#include <unordered_map>
#include <cstdlib>
#include "../unordered_map.hpp"
#include <assert.h>
int main(){
    UnorderedMap<int,int> my;
    std::unordered_map<int,int> stl; 
    for(int i=0;i<30000;++i){
        int tem1 = rand();
        int tem2 = rand();
		my.emplace(tem1,tem2);
        stl.emplace(tem1,tem2);
    }
    for(auto &mp:stl){
		auto i = my.find(mp.first);
		assert(i!=my.end());
		assert(i->second==mp.second);
	}
    return 0;
}