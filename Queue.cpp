#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue(){
    head = tail = nullptr;
}
void Queue::enQueue(BSTNode *inNode){
    qNode *tmp = new qNode{inNode, nullptr};
    if (head == nullptr){
        head = tail = tmp;
    } else {
        tail->next = tmp;
        tail = tmp;
    }
}
BSTNode* Queue::deQueue(){
    BSTNode *toRet = head->node;
    qNode* tmp = head->next;
    delete head;
    head = tmp;
    
    return toRet;
}
void Queue::printQueue(){
    qNode *tmp = head;
    while(tmp != nullptr){
        cout << tmp->node->data->word;
        tmp = tmp->next;
    }
}

bool Queue::isEmpty(){
    return head == nullptr;
}