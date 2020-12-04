#ifndef BST_H
#define BST_H

#include <iostream>

struct BSTNode{
    std::string word;
    std::string color;
    int count;
    BSTNode* parent;
    BSTNode* leftChild;
    BSTNode* rightChild;
    
    BSTNode(std::string in_word, BSTNode *p, BSTNode *lc, BSTNode *rc)
    {
        word = in_word;
        count = 0;
        parent = p;
        leftChild = lc;
        rightChild = rc;
        color = "black";
    };
};


class BST
{
    
public:
    BST();
    void insert(std::string word);
    BSTNode* bstAdd(std::string word);
    
    void findAlphaRange(std::string word1, std::string word2);
    
    int countBSTNodes();
    int countTotalWords();
    int getDepth(std::string word);

    void printInOrderBST();
    void printWord(std::string word);

    void touchNode(std::string word);
    void prettyPrint();
protected:
    
private:
    void leftRotate(BSTNode *node);
    void rightRotate(BSTNode *node);
    void printIOBST(BSTNode * node);
    void printAplhaRangeHelper(BSTNode *node, std::string first, std::string last);
    int getDepth(BSTNode *node);
    
    BSTNode* searchBST(std::string word); //use this function to find pointer to node in BST
    BSTNode* root;
    int totalWords;
    int totalUnique;
};

#endif // BST_H
