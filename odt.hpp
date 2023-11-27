/*
 * @Author: zanilia
 * @Date: 2022-09-06 19:06:12
 * @LastEditTime: 2022-09-08 11:09:01
 * @Descripttion: 
 */
#include <map>
using namespace std;
class ODT{
	struct Node{
		int right;
		int val;
		Node(int right,int val):right(right),val(val){}
	};
	static constexpr int INF = 1e9+1;
	map<int,Node> ranges;
	typedef map<int,Node>::iterator iter;
	ODT(){
		ranges.emplace(-INF,Node(INF,0));
	}
	// 将[l,r]分割成[l,x)和[x,r]并返回后者的迭代器
	iter split(int x){
		auto it = ranges.lower_bound(x);
		if(it!=ranges.end()&&it->first==x) 
			return it;
		it--;
		int l = it->first,right = it->second.right;
		auto node = it->second;
		ranges.erase(it);
		node.right = x-1;
		ranges.emplace(l,node);
		node.right = right;
		return ranges.emplace(x,node).first;
	}
	// 将[l,r]值更新为val
	void update(int l,int r,int val){
		auto itr = split(r+1),itl = split(l);
		ranges.erase(itl,itr);
		ranges.emplace(l,Node(r,val));
	}
};