#include <iostream>

#ifndef UTIL_H
#define UTIL_H

struct node {
    std::string word;
    int count;
};

struct BSTNode{
    node *data;
    std::string color;
    
    BSTNode* parent;
    BSTNode* leftChild;
    BSTNode* rightChild;
    
    BSTNode(std::string in_word, BSTNode *p, BSTNode *lc, BSTNode *rc)
    {
        data = (in_word != ""? new node{in_word, 0}: nullptr);
        parent = p;
        leftChild = lc;
        rightChild = rc;
        color = "black";
    };
};

std::string toLower(std::string* input);


#endif