/*
 * @Author: zanilia
 * @Date: 2021-11-04 23:17:17
 * @LastEditTime: 2021-12-02 19:42:27
 * @Descripttion: 
 */
#include <iostream>
#include <unordered_map>
class UnionSet{
    int* rank;
    int* fa;
public:
    UnionSet():rank(new int[20]),fa(new int [20]){
        for(int i=0;i<20;++i){
            rank[i] = 1;
            fa[i] = i;
        }
    }
    UnionSet(int n):rank(new int[n]),fa(new int [n]){
        for(int i=0;i<n;++i){
            rank[i] = 1;
            fa[i] = i;
        }
    }
    int find(int x){
        if(fa[x]!=x)
            fa[x] = find(fa[x]);
        return fa[x];
    }
    bool join(int x,int y){
        int fx = find(x),fy= find(y);
        if(fx==fy)
            return false;
        if(rank[fx]<rank[fy]){
            int tem = fy;
            fy = fx;
            fx = tem;
        }
        rank[fx] += rank[fy];
        fa[fy] = fx;
        return true;
    }
};
class UnionFind{
    std::unordered_map <int, int> parent;
    UnionFind(){}
    int find(int x){
        auto i1 = parent.find(x);
        if(i1!=parent.end()){
            if(i1->second!=x)
                i1->second = find(i1->second);
            return i1->second;
        }
        parent.emplace(x,x);
        return x;
    }
    bool join(int x,int y){
        int fx = find(x),fy = find(y);
        if(fx==fy)
            return false;
        parent.emplace(fx,fy);
        return true;
    }
};