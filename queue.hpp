/*
 * @Author: zanilia
 * @Date: 2021-07-21 22:55:13
 * @LastEditTime: 2021-07-22 00:09:24
 * @Descripttion: 
 */
#include <iostream>
template<class DataType>
class Queue{
public:
    struct LinkList{
    public:
        DataType data;
        LinkList* next;
        LinkList(const DataType& x,LinkList *next=NULL):data(x),next(next){}
        LinkList():next(NULL){}
    };
private:
    LinkList* head;
    LinkList* tail;
    LinkList uninitialized_object;
public:
    Queue():head(NULL),tail(NULL),uninitialized_object(){}
    void push(const DataType& i){
        if(!head){
            head=tail=new LinkList(i);
        }
        else{
            tail->next=new LinkList(i);
            tail=tail->next;
        }
    }
    void pop(int &i){
        if(head){
            i = head->data;
            LinkList *tem=head;
            head=head->next;
            delete(tem);
        }
    }
    const DataType& front(){
        if(head)
            return head->data;
        return uninitialized_object;
    }
    const DataType& back(){
        if(tail)
            return tail->data;
        return uninitialized_object;
    }
    bool empty(){
        return (bool)head;
    }
    ~Queue(){
        if(head)
            return ;
        LinkList* tem;
        while(head.next){
            tem = head.next;
            delete(head);
            head = tem;
        }
        delete(head);
        head = tail =NULL;
    }
};