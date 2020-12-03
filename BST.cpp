/* 
Implementation for BSH.h
Ty VanEssen 20-10-2020
*/
#include <iostream>
#include "BST.h"
using namespace std;

BST::BST(){
    root = new BSTNode{"", nullptr, nullptr, nullptr}; //root is a nullNode
    totalWords = 0;
}

/*
    Returns a pointer to the value added or nullPtr if the value was already found and only needed updating
*/
BSTNode* BST::bstAdd(string word){ //iteratively
    totalWords++;
    BSTNode *result = searchBST(word); // returns the node we need. 
    //returns null if the list is empty
    BSTNode *toReturn = nullptr;
    cout << "Adding node: " << word << endl;
    if (result->word == word){
        result->count += 1;
        //dont update to ret since it's at its no change value by default
    } else {
        //no need to set root since (after the constructor runs) it should already be this empty node

        result->word = word;
        result->count += 1;
        //make new nullnodes
        BSTNode *leftNullNode = new BSTNode{"", result, nullptr, nullptr};
        BSTNode *rightNullNode = new BSTNode{"", result, nullptr, nullptr};

        result -> leftChild = leftNullNode;
        result -> rightChild = rightNullNode;

        toReturn = result;
    }

    return toReturn;
}

/*
    returns a pointer to where the node should go
*/
BSTNode* BST::searchBST(std::string word) {
    BSTNode *tmp = root;
    while (tmp->word != "") {
        if (word < tmp->word) {
            tmp = tmp->leftChild;
        } else if (word > tmp->word) {
            tmp = tmp->rightChild;
        } else {
            return tmp;
        }
    }
    return tmp;
}

void BST::printInOrderBST() {
    cout << "root=" << root->word << "[" << root->count << "] left: " << (root->leftChild? root->leftChild->word : "null") << ", right: " << (root->rightChild? root->rightChild->word : "null") << endl;

    printIOBST(root);
    cout << endl;
}   

void BST::printIOBST(BSTNode * node) {
    if (node->leftChild != nullptr) {
        printIOBST(node->leftChild);
    }
    if (node->word != ""){
        cout << node->word << "[" << node->count << "], " << flush;
    }
    if (node->rightChild != nullptr) {
        printIOBST(node->rightChild);
    }
}

void BST::printWord(string word){
    BSTNode *foundWord = searchBST(word);
    if (foundWord->word != word) {
        cout << "[ ! ] Node not found, this would be the parent:\n";
    }
    cout << "\tWord: " << foundWord->word << endl;
    cout << "\tCount: " << foundWord->count << endl;
    cout << "\tParent: " << (foundWord->parent?foundWord->parent->word:"NoParent") << endl;
    cout << "\tLeft Child: " << (foundWord->leftChild->word != "" ?foundWord->leftChild->word:"NullNode") << endl;
    cout << "\tRight Child: " << (foundWord->rightChild->word != ""?foundWord->rightChild->word:"NullNode") << endl;
    cout << "\tColor: " << foundWord->color << endl;
}

int BST::countBSTNodes(){
    int num = 0;
    countBSTNodes(root);
    return num;
}

void BST::countBSTNodes(BSTNode *node){
    if (node == nullptr) {
        return;
    } else {
        countBSTNodes(node->leftChild);
        countBSTNodes(node->rightChild);
    }
}
 
int BST::countTotalWords(){
    return totalWords;
}

void BST::leftRotate(BSTNode *node){
    //pull up
    BSTNode *tmp = node->rightChild;
    if (tmp->word == ""){ //so we don't allow shifting of end nodes
        cout << "ERROR: tried to shift end node: " << node->word << endl;
        return;
    }
    node->rightChild = tmp->rightChild;

    if (tmp->leftChild->word != ""){
        tmp->leftChild->parent = node;
    }
    tmp->parent = node->parent;
    if(!node->parent){
        root = tmp;
    } else if (node == node->parent->leftChild){
        node->parent->leftChild = tmp;
    } else {
        node->parent->rightChild = tmp;
    }
    node->rightChild = tmp->leftChild;
    tmp->leftChild = node;
    node->parent = tmp;
}

void BST::leftRotate(string word){
    leftRotate(searchBST(word));
}
void BST::rightRotate(string word){
    rightRotate(searchBST(word));
}

void BST::rightRotate(BSTNode *node){
    //pull up
    BSTNode *tmp = node->leftChild;
    if (tmp->word == ""){ //so we don't allow shifting of end nodes
        cout << "ERROR: tried to shift end node: " << node->word << endl;
        return;
    }
    node->leftChild = tmp->leftChild;

    if (tmp->rightChild->word != ""){
        tmp->rightChild->parent = node;
    }
    tmp->parent = node->parent;
    if(!node->parent){
        root = tmp;
    } else if (node == node->parent->rightChild){
        node->parent->rightChild = tmp;
    } else {
        node->parent->leftChild = tmp;
    }
    node->leftChild = tmp->rightChild;
    tmp->rightChild = node;
    node->parent = tmp;
}
/*
void BST::insert(std::string word){

}
*/