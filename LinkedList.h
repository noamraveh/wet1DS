//
//final
//
#ifndef DIESEL_LINKEDLIST_H
#define DIESEL_LINKEDLIST_H
#include <algorithm>
#include <cstdbool>

template <class T>
class ListNode{
public:
    T* data;
    ListNode* next;
    ListNode* prev;
    bool marked;
    explicit ListNode(T* data):data(data),next(nullptr),prev(nullptr),marked(false){}
    ListNode() = default;
    ~ListNode(){
        delete data;
    }

    void setMarked(){
        marked = true;
    }

    bool getMarked(){
        return marked;
    }
};

template <class T>
class LinkedList{
private:
    int num_of_nodes;
    ListNode<T>* first;
    ListNode<T>* last;

public:
    //c'tor
    LinkedList(): num_of_nodes(0),first(nullptr),last(nullptr){}
    //d'tor
    ~LinkedList(){
       while (first != nullptr){
           ListNode<T>* temp = first;
           first = first->next;
           delete temp;
       }
    }
    //getFirst
    ListNode<T>* getFirstNode(){
        return first;
    }
    //getNext
    ListNode<T>* getNextNode(ListNode<T>* node){
        return node->next;
    }
    //getPrev
    ListNode<T>* getPrevNode(ListNode<T>* node){
        return node->prev;
    }
    //getLast
    ListNode<T>* getLastNode(){
        return last;
    }
    //insert first
    ListNode<T>* InsertFirst(T* data){
        auto node = new ListNode<T>(data);
        if (isEmpty()){
            first = node;
            last = node;
            num_of_nodes++;
            return node;
        }
        else
            return nullptr;
    }
    //InsertNode
    ListNode<T>* InsertNode(ListNode<T>* curNode,T* data){
        auto node = new ListNode<T>(data);

        if (curNode != last) { //middle
            curNode->next->prev = node;
            node->next = curNode->next;
            curNode->next = node;
            node->prev = curNode;
        }
        else{ //insert last
            node->next = nullptr;
            curNode->next = node;
            node->prev = curNode;
            last = node;
        }
        num_of_nodes++;
        return node;
    }


    //removeNode: can only remove middle nodes or last node
    void removeNode (ListNode<T>* node){
        if (node == first){ //it is illegal to delete first node
            return;
        }
        else if (node == last){ //delete last node
            last = node->prev;
            node->prev->next = nullptr;
            delete node;
            num_of_nodes--;
            return;
        }
        else { // delete middle node
            node->next->prev = node->prev;
            node->prev->next = node->next;
            delete node;
            num_of_nodes--;
        }
    }
   //IsEmpty
   bool isEmpty(){
       return (!first);
    }
};
#endif //DIESEL_LINKEDLIST_H
