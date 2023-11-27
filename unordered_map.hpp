/*
 * @Author: zanilia
 * @Date: 2021-11-12 10:52:55
 * @LastEditTime: 2022-03-29 16:39:38
 * @Descripttion: 
 */
#include "function.hpp"
#include "pair.hpp"
template<class Key,class Value,class hash = Hash<Key>,class equal = Equal<Key> >
class UnorderedMap{
    struct HashNode{
        Pair<Key,Value> hash_pair;
        HashNode* next;
        HashNode() = default;
        HashNode(const Key& _key,const Value& _val):hash_pair(_key,_val),next(NULL){}
        HashNode(const Key& _key,const Value& _val,HashNode* _next):hash_pair(_key,_val),next(_next){}
    };
    HashNode** _bucket;
    unsigned int _size;
    unsigned int _capacity;
    static inline HashNode* find(HashNode* head,const Key& _key){
        while(head){
            if(equal()(head->hash_pair.first,_key))
                return head;
            head = head->next;
        }
        return NULL;
    }
public:
    class iterator;
    friend class iterator;
    UnorderedMap(){
        _size = 0;_capacity = 32;
		_bucket = new HashNode*[_capacity];
		for(int i=0;i<32;++i)
			_bucket[i] = NULL;
    }
    UnorderedMap(int capacity){
        _size = 0;
		_capacity = capacity;
		_bucket = new HashNode*[_capacity];
		for(int i=0;i<_capacity;++i)
			_bucket[i] = NULL;
    }
    iterator find(const Key& _key){
        return iterator(find(_bucket[hash()(_key)%_capacity],_key),this);
    }
    bool emplace(const Key& _key,const Value& _val){
        if(_size/_capacity > 0.7)
            resize(_capacity<<1);
        unsigned pos = hash()(_key)%_capacity;
        HashNode* head = _bucket[pos];
        if(find(head,_key))
            return false;
        ++_size;
        _bucket[pos] = new HashNode(_key,_val,head);
        return true;
    }
    void resize(int new_cap){
        if(new_cap>_capacity){
            HashNode** tem_bucket = new HashNode* [new_cap];
            for(int i=0;i<new_cap;++i)
                tem_bucket[i] = NULL;
            for(int i=0;i<_capacity;++i){
                HashNode* head = _bucket[i];
                while(head){
                    int pos = hash()(head->hash_pair.first)%new_cap;
                    HashNode* tem_node = tem_bucket[pos];
                    tem_bucket[pos] = head;
                    head = head->next;
                    tem_bucket[pos]->next = tem_node;
                }
            }
            delete [] _bucket;
            _bucket = tem_bucket;
            _capacity = new_cap;
        }
    }
    iterator begin(){
        HashNode** cur = _bucket;
        while(!(*cur))
            ++cur;
        if(cur==_bucket+_capacity)
            return iterator(NULL,this);
        else
            return iterator(*cur,this);
    }
    iterator end(){
        return iterator(NULL,this);
    }
    class iterator{
        HashNode* cur;
        UnorderedMap* map;
    public:
        iterator() = delete;
        iterator(HashNode* _cur,UnorderedMap* _map):cur(_cur),map(_map){}
        iterator(const iterator&) = default;
        typedef Pair<Key,Value> value_type;
        value_type& operator*(){
            return cur->hash_pair;
        }
        value_type* operator->(){
            return &(cur->hash_pair);
        }
        iterator& operator++(){
            if(cur->next)
                cur = cur->next;
            else{
                HashNode** bucket = map->_bucket + hash()(cur->hash_pair->first)%(map->_capacity)+1;
                HashNode** end = map->_capacity + map->_bucket;
                while(!(*bucket)&&bucket!=end)
                    ++bucket;
                if(bucket==end)
                    cur = NULL;
                else
                    cur = (*bucket);
            }
        }
        bool operator==(const iterator& other){
            return other.cur ==cur&&other.map == map;
        }
        bool operator!=(const iterator& other){
            return other.cur != cur || other.map != map;
        }
        bool operator!(){
            return !cur;
        }
    };
};