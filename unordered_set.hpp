#include "function.hpp"
template<class Key,class hash = Hash<Key>,class equal = Equal<Key> >
class UnorderedSet{
    static const unsigned int prime_list[] = {53,97,193,389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,786433,1572869,3145739,6291469,12582917,25165843,50331653,100663319,201326611,402653189,805306457,1610612741,3221225473ul, 4294967291ul};
    struct HashNode{
        Key key;
        HashNode* next;
        HashNode() = default;
        HashNode(const Key& _key):key(_key),next(NULL){}
        HashNode(const Key& _key,HashNode* _next):key(_key),next(_next){}
    };
    HashNode** _bucket;
    unsigned int _size;
    unsigned int _capacity;
    static inline find(HashNode* head,const Key& _key){
        while(head){
            if(equal()(head->key,_key))
                return head;
            head = head->next;
        }
        return NULL;
    }
public:
    class Iterator;
    friend class Iterator;
    UnorderedSet(){
        _size = 0; _capacity = 32; 
        _bucket = new HashNode*[_capacity];
        for(int i=0;i<_capacity;++i)
            _bucket[i] = NULL;
    }
    UnorderedSet(int capacity){
        _size = 0; _capacity = capacity; 
        _bucket = new HashNode*[_capacity];
        for(int i=0;i<_capacity;++i)
            _bucket[i] = NULL;
    }
    bool find(const Key& _key){
        return find(_bucket[hash()(_key)%_capacity],_key);
    }
    bool emplace(const Key& _key){
        if(_size/_capacity > 0.7)
            resize(_size<<1);
        unsigned pos = hash()(_key)%_capacity;
        HashNode* head = _bucket[pos];
        if(find(head,_key))
            return false;
        _bucket[pos] = new HashNode(_key,head);
        ++_size;
        return true;
    }
    unsigned size(){
        return _size;
    }
    bool empty(){
        return !_size;
    }
    void resize(int new_cap){
        if(new_cap>_capacity){
            HashNode** tem_bucket = new HashNode* [new_cap];
            for(int i=0;i<_capacity;++i){
                HashNode* head = _bucket[i];
                while(head){
                    int pos = hash()(head->key);
                    HashNode* tem_node = _bucket[pos];
                    _bucket[pos] = head;
                    head = head->next;
                    _bucket[pos]->next = tem_node;
                }
            }
            delete [] _bucket;
            _bucket = tem_bucket;
            _capacity = new_cap;
        }
    }
    Iterator begin(){
        HashNode** cur = _bucket;
        while(!(*cur))
            ++cur;
        if(cur==_bucket+_capacity)
            return iterator(NULL,this);
        else
            return iterator(*cur,this);
    }
    Iterator end(){
        return iterator(NULL,this);
    }
    class iterator{
        HashNode* cur;
        UnorderedSet* set;
        iterator() = delete;
        iterator(HashNode* _cur,UnorderedSet* _set):cur(_cur),set(_set){}
        iterator(const iterator&) = default;
        typedef Key value_type;
        value_type& operator*(){
            return cur->key;
        }
        value_type* operator->(){
            return &(cur->key);
        }
        iterator& operator++(){
            if(cur->next)
                cur = cur->next;
            else{
                HashNode** bucket = set->_bucket + hash()(cur->key)%(set->_capacity) + 1;
                HashNode** end = set->_capacity + set->_bucket;
                while(!(*bucket)&&bucket!=end)
                    ++bucket;
                if(bucket==end)
                    cur = NULL;
                else
                    cur = (*bucket);
            }
        }
        bool operator==(const iterator& other){
            return other.cur ==cur&&other.set == set;
        }
        bool operator!=(const iterator& other){
            return other.cur != cur || other.set != set;
        }
    };
};