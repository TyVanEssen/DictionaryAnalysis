/* 
Implementation for BSH.h
Ty VanEssen 20-10-2020
*/
#include <iostream>
#include "BST.h"
#include "Queue.h"
#include <vector>
#include <algorithm>
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
    if (result->word == word){
        result->count += 1;
        //dont update to ret since it's at its no change value by default
    } else {
        //no need to set root since (after the constructor runs) it should already be this empty node
        result->word = word;
        result->color = "red";
        result->count += 1;
        //make new nullnodes
        BSTNode *leftNullNode = new BSTNode{"", result, nullptr, nullptr};
        BSTNode *rightNullNode = new BSTNode{"", result, nullptr, nullptr};

        result -> leftChild = leftNullNode;
        result -> rightChild = rightNullNode;

        toReturn = result;
        totalUnique += 1;
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
        cout << "[ ! ] Node: " << word << " not found, this would be the parent:\n";
        foundWord = foundWord->parent;
    }
    cout << "\tWord: " << foundWord->word << endl;
    cout << "\tCount: " << foundWord->count << endl;
    cout << "\tParent: " << (foundWord->parent?foundWord->parent->word:"NoParent") << endl;
    cout << "\tLeft Child: " << (foundWord->leftChild->word != "" ?foundWord->leftChild->word:"NullNode") << endl;
    cout << "\tRight Child: " << (foundWord->rightChild->word != ""?foundWord->rightChild->word:"NullNode") << endl;
    cout << "\tColor: " << foundWord->color << endl;
}

int BST::countBSTNodes(){
    return totalUnique;
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
    node->rightChild = tmp->leftChild;
    tmp->leftChild->parent = node;
    
    
    tmp->parent = node->parent;
    if(!node->parent){
        root = tmp;
    } else if (node == node->parent->leftChild){
        node->parent->leftChild = tmp;
    } else {
        node->parent->rightChild = tmp;
    }

    tmp->leftChild = node;
    node->parent = tmp;
}

void BST::rightRotate(BSTNode *node){
    //pull up
    BSTNode *tmp = node->leftChild;
    if (tmp->word == ""){ //so we don't allow shifting of end nodes
        cout << "ERROR: tried to shift end node: " << node->word << endl;
        return;
    }
    node->leftChild = tmp->rightChild;
    tmp->rightChild->parent = node;

    tmp->parent = node->parent;
    if(!node->parent){
        root = tmp;
    } else if (node == node->parent->rightChild){
        node->parent->rightChild = tmp;
    } else {
        node->parent->leftChild = tmp;
    }

    tmp->rightChild = node;
    node->parent = tmp;
}

void BST::insert(std::string word){
    BSTNode *workingNode = bstAdd(word); //regular bst insert
    if (workingNode == nullptr){
        return;
    }
    //cout << endl << "Node: " << word;
    while (workingNode != root && workingNode->parent->color == "red"){
        if (workingNode->parent == workingNode->parent->parent->leftChild){
            // cout << word << " - left" << endl;
            BSTNode *uncle = workingNode->parent->parent->rightChild;
            if (uncle->color == "red"){
                workingNode->parent->color = "black";
                uncle->color = "black";
                workingNode->parent->parent->color = "red";
                workingNode = workingNode->parent->parent;
            } else {
                if (workingNode == workingNode->parent->rightChild){ //if we are a right child.. Make us a left child and do again
                    workingNode = workingNode->parent;
                    leftRotate(workingNode);
                }
                workingNode->parent->color = "black";
                workingNode->parent->parent->color = "red";
                rightRotate(workingNode->parent->parent);
            }
        } else { //we are a right child
            // cout << word << " - right" << endl;
            BSTNode *uncle = workingNode->parent->parent->leftChild;
            if (uncle->color == "red"){
                workingNode->parent->color = "black";
                uncle->color = "black";
                workingNode->parent->parent->color = "red";
                workingNode = workingNode->parent->parent;
            } else {
                if (workingNode == workingNode->parent->leftChild){ //if we are a left child.. Make us a left child and do again
                    workingNode = workingNode->parent;
                    rightRotate(workingNode);
                }
                workingNode->parent->color = "black";
                workingNode->parent->parent->color = "red";
                leftRotate(workingNode->parent->parent);
            }
        }
    }
    root->color = "black";
}
void BST::findAlphaRange(string word1, string word2){
    //fix any ordering
    string first, last;
    if (word1 < word2) {
        first = word1;
        last = word2;
    } else {
        first = word2;
        last = word1;
    }
   
    if (searchBST(first)->word != first || searchBST(last)->word != last){
        cout << "One of the provided words is not in the bst \n";
    } else {
        //do it recursively
        printAplhaRangeHelper(root, first, last);
    }
    cout << endl;
}
void BST::printAplhaRangeHelper(BSTNode *node, string first, string last) {
    if (node != nullptr) {
        // if the current node is in range, recurse
        if (node->word >= first && node->word <= last) {
            printAplhaRangeHelper(node->leftChild, first, last);
            cout << node->word << ", ";
            printAplhaRangeHelper(node->rightChild, first, last);
        } else if (node->word < first) {  // if the node is small go right
            printAplhaRangeHelper(node->rightChild, first, last);
        } else if (node->word > last) {
            printAplhaRangeHelper(node->leftChild, first, last);
        }
    } 
}

int BST::getDepth(BSTNode *node){
    int deep = 0; //root's depth
    BSTNode *tmp = node;
    while (tmp->parent != nullptr){
        tmp = tmp->parent;
        deep += 1;
    }
    return deep;
}

int BST::getDepth(string word){
    return getDepth(searchBST(word));
}
/*
To test speed of retrivalf
*/
void BST::touchNode(std::string word){
    searchBST(word);
}

void BST::prettyPrint(){
    Queue Q;
    Q.enQueue(root);
    // vector<string> v;

    int prevDeep = 0;
    while (!Q.isEmpty()){
        BSTNode *tmp = Q.deQueue();
        int myDeep = getDepth(tmp);
        if ( myDeep > prevDeep) {
            cout << endl;
        } else {
            cout << (myDeep != 0? " , " :"");
        }
        prevDeep = myDeep;
        cout << tmp->word << ":" << myDeep << (tmp->color == "red"? "R":"B") << tmp->count << "[" << tmp->leftChild->word << "<|>" << tmp->rightChild->word << "^" << (tmp->parent?tmp->parent->word:"NULL") << "]";
        if (tmp->leftChild->word != ""){
            Q.enQueue(tmp->leftChild);
        }
        if (tmp->rightChild->word != ""){
            Q.enQueue(tmp->rightChild);
        }
        // if (std::count(v.begin(), v.end(), tmp->word)){
        //     cout << endl << endl;
        //     cout << "ENDING EARLY 2x " << tmp->word << endl;
        //     exit(1);
        // } else {
        //     v.push_back(tmp->word);
        // }
    }
    cout << endl;
}