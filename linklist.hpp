/*
 * @Author: zanilia
 * @Date: 2021-07-21 00:08:40
 * @LastEditTime: 2021-07-21 22:59:18
 * @Descripttion: 
*/
#include <iostream>
template<class DataType>
class LinkList{
    class Node{
    public:
        DataType data;
        Node* next;
        Node():next(NULL){}
        Node(const DataType &_data):data(_data),next(NULL){}
        Node(const DataType &_data,Node* _next):data(_data),next(NULL){}
    };
    class iterator{
    private:
        Node* p;
    public:
        iterator& operator++(){
            if(p)
                p = p->next;
            return *this;
        }
        DataType& operator*(){
            return p->data;
        }
        Node& operator->(){
            return *p;
        }
    };
private:
    Node* head;
    Node* tail;
    unsigned int len;
public:
    void insert(iterator &i,DataType& _data){
        
    }
    void push_front(DataType _data){
        if(head)
            head = new Node(_data,head);
        else
            head = tail = new Node(_data);
        ++len;
    }
    void pop_front(){
        if(!head)
            return ;
        Node* tem = head.next;
        if(head==tail)
            tail = NULL;
        delete(head);
        head = tem;
        --len;
    }
    void push_back(const DataType& _data){
        if(tail){
            tail->next = new Node(_data);
            tail = tail->next;
        }
        else
            head = tail = new Node(_data);
        ++len;
    }
    void pop_back(){
        if(!tail)
            return ;
        if(head==tail){
            delete(tail);
            head = tail = NULL;
        }
        Node* tem = head;
        while(tem->next)
            tem = tem->next;
        tail = tem;
        delete(tem->next);
        --len;
    }
    bool empty(){
        return len;
    }
    unsigned int size(){
        return len;
    }
    DataType& front(){

    }
    DataType& back(){

    }
    void reverse(){

    }
    void sort(){

    }
    void clear(){
        
    }
};