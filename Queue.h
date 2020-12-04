/*
This is a queue of pointers to BST nodes
It will be done using a LL implementation
*/
#include "BST.h"

#ifndef QUEUE_H
#define QUEUE_H

struct qNode
{
    BSTNode *node;
    qNode *next;
};
class Queue
{
private:
    qNode *head;
    qNode *tail;

public:
    Queue();
    void enQueue(BSTNode *inNode);
    BSTNode* deQueue();
    void printQueue();
    bool isEmpty();

};

#endif // QUEUE_H