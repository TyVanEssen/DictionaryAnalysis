#ifndef BST_H
#define BST_H

#include <iostream>
#include <stack>

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


class BST {
public:
    BST();
    node* rbInsert(std::string word);
    node* bstInsert(std::string word);
    
    void findAlphaRange(std::string word1, std::string word2);
    
    int countBSTNodes();
    int countTotalWords();
    int getDepth(std::string word);

    void printInOrderBST();
    void printWord(std::string word);

    void touchNode(std::string word);
    void prettyPrint();

    void scannerReset();
    node* scannerNext();

protected:
    
private:
    BSTNode* bstAdd(std::string word);
    void leftRotate(BSTNode *node);
    void rightRotate(BSTNode *node);
    void printIOBST(BSTNode * node);
    void printAplhaRangeHelper(BSTNode *node, std::string first, std::string last);
    int getDepth(BSTNode *node);
    
    BSTNode* searchBST(std::string word); //use this function to find pointer to node in BST

    std::stack<BSTNode*> scanner;
    BSTNode* root;
    int totalWords;
    int totalUnique;
};

#endif // BST_H
