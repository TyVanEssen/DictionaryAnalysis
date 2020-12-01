#ifndef BST_H
#define BST_H

#include <string>

struct BSTNode{
    std::string word;
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
    };
};


class BST
{
    
public:
    BST();
    void printWord(std::string word);
    void printInOrderBST();
    int countBSTNodes();
    void addWordNode(std::string word);
    int countTotalWords();
protected:
    
private:
    void printIOBST(BSTNode * node);
    void countBSTNodes(BSTNode *node);
    BSTNode* searchBST(std::string word); //use this function to find pointer to node in BST
    BSTNode* root;
    int totalWords;
};

#endif // BST_H
