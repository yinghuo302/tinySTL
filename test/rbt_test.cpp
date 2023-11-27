/*
 * @Author: zanilia
 * @Date: 2022-03-29 20:57:17
 * @LastEditTime: 2022-08-21 11:03:41
 * @Descripttion: 
 */
#include "../rbtree.hpp"
#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <assert.h>
typedef RBTreeNode<int,int> Node;
int checkRBT(Node* root){
	if(!root){
		return 0;
	}	
	int n = checkRBT(root->left);
	assert(n==checkRBT(root->right));
	if(root->color == RB_BLACK)
		++n;
	return n;
}
int main(){
	RBTree<int,int> tree;
	int nums[10000];
	std::unordered_map<int,int> mp;
	for(int i=0;i<10000;++i){
		int a = rand(),b = i;
		if(mp.count(a)){
			continue;
		}else 
		nums[i] = a;
		tree.insert(a,b);
	}
	int val;
	for(auto &m:mp){
		assert(tree.find(m.first,val));
		assert(val==m.second);
	}
	for(int i=0;i<10000;++i){
		if(i&1)
			tree.erase(nums[i]);
		else
			tree.erase(rand());
	}
	int n = 0;
	checkRBT(tree.getRoot());
	return 0;
}