/* 
Implementation for BSH.h
Ty VanEssen 20-10-2020
*/
#include <iostream>
#include "Queue.h"
#include "BST.h"
#include <vector>
#include <algorithm>
using namespace std;

BST::BST(){
    root = new BSTNode{"", nullptr, nullptr, nullptr}; //root is a nullNode
    totalWords = 0;
    totalUnique = 0;
}

node* BST::rbInsert(std::string word){
    return rbInsert(word, 1);
}
node* BST::rbInsert(std::string word, int count){
    BSTNode *workingNode = bstAdd(word, count); //regular bst insert
    if (workingNode == nullptr){
        return nullptr;
    }
    node *toRet = workingNode->data;
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
    return toRet;
}
node* BST::bstInsert(string word){
    return bstAdd(word, 1)->data;
}
node* BST::bstInsert(string word, int count){
    return bstAdd(word, count)->data;
}

/*
    Returns a pointer to the value added or nullPtr if the value was already found and only needed updating
*/
BSTNode* BST::bstAdd(string word, int count){ //iteratively
    totalWords++;
    BSTNode *result = searchBST(word); // returns the node we need. 
    //returns null if the list is empty
    BSTNode *toReturn = nullptr;
    if (result->data && result->data->word == word){
        result->data->count += count;
        //dont update to ret since it's at its no change value by default
    } else {
        //no need to set root since (after the constructor runs) it should already be this empty node
        result->data = new node{word, count};
        result->color = "red";
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
    while (tmp->data != nullptr) {
        if (word < tmp->data->word) {
            tmp = tmp->leftChild;
        } else if (word > tmp->data->word) {
            tmp = tmp->rightChild;
        } else {
            return tmp;
        }
    }
    return tmp;
}

void BST::printInOrderBST() {
    cout << "root=" << root->data->word << "[" << root->data->count << "] left: " << (root->leftChild->data? root->leftChild->data->word : "null") << ", right: " << (root->rightChild->data? root->rightChild->data->word : "null") << endl;

    printIOBST(root);
    cout << endl;
}   

void BST::printIOBST(BSTNode * node) {
    if (node->leftChild != nullptr) {
        printIOBST(node->leftChild);
    }
    if (node->data != nullptr){
        cout << node->data->word << "[" << node->data->count << "], " << flush;
    }
    if (node->rightChild != nullptr) {
        printIOBST(node->rightChild);
    }
}

void BST::printWord(string word){
    BSTNode *foundWord = searchBST(word);
    if (foundWord->data->word != word) {
        cout << "[ ! ] Node: " << word << " not found, this would be the parent:\n";
        foundWord = foundWord->parent;
    }
    cout << "\tWord: " << foundWord->data->word << endl;
    cout << "\tCount: " << foundWord->data->count << endl;
    cout << "\tParent: " << (foundWord->parent?foundWord->parent->data->word:"NoParent") << endl;
    cout << "\tLeft Child: " << (foundWord->leftChild->data != nullptr ?foundWord->leftChild->data->word:"NullNode") << endl;
    cout << "\tRight Child: " << (foundWord->rightChild->data != nullptr?foundWord->rightChild->data->word:"NullNode") << endl;
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
    if (tmp->data == nullptr){ //so we don't allow shifting of end nodes
        cout << "ERROR: tried to shift end node:" << endl;
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
    if (tmp->data == nullptr){ //so we don't allow shifting of end nodes
        cout << "ERROR: tried to shift end node:" << endl;
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
    if (!searchBST(first)->data || !searchBST(last)->data){
        cout << "One of the provided words is not in the bst \n";
    } else {
        //do it recursively
        printAplhaRangeHelper(root, first, last);
    }
}
void BST::printAplhaRangeHelper(BSTNode *node, string first, string last) {
    if (node != nullptr && node->data != nullptr) {
        // if the current node is in range, recurse
        if (node->data->word >= first && node->data->word <= last) {
            printAplhaRangeHelper(node->leftChild, first, last);
            cout << node->data->word << ", ";
            printAplhaRangeHelper(node->rightChild, first, last);
        } else if (node->data->word < first) {  // if the node is small go right
            printAplhaRangeHelper(node->rightChild, first, last);
        } else if (node->data->word > last) {
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

// To test speed of retrival
void BST::touchNode(std::string word){
    searchBST(word);
}

void BST::prettyPrint(){
    Queue Q;
    Q.enQueue(root);
    // vector<string> v;
    cout << "[ ! ] How to read-> word:depthColorCount[LeftChild<|>RightChild^Parent]" << endl;
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

        // build the output string
        string outString = "";
        //cout << tmp->data->word << ":" << myDeep << (tmp->color == "red"? "R":"B") << tmp->data->count << "[" << tmp->leftChild->data->word << "<|>" << tmp->rightChild->data->word << "^" << (tmp->parent?tmp->parent->data->word:"NULL") << "]";
        outString += (tmp->data?tmp->data->word:"NullNode");
        outString += ":" + to_string(myDeep) + (tmp->color == "red"? "R":"B");
        outString += to_string(tmp->data?tmp->data->count:0);
        outString += "[";
        outString += (tmp->leftChild->data? tmp->leftChild->data->word:"-");
        outString += "<|>";
        outString += (tmp->rightChild->data?tmp->rightChild->data->word:"-");
        outString += "^";
        outString += (tmp->parent?tmp->parent->data->word:"-");
        outString += "]";

        //finish building output string
        cout << outString;


        
        if (tmp->leftChild->data != nullptr){
            Q.enQueue(tmp->leftChild);
        }
        if (tmp->rightChild->data != nullptr){
            Q.enQueue(tmp->rightChild);
        }
    }
    cout << endl;
}

//emptys scannerStack and sets up for new run
void BST::scannerReset(){
    while (!scanner.empty()){
        scanner.pop();
    }
    BSTNode *tmp = root;
    while (tmp->data != nullptr){
        scanner.push(tmp);
        tmp = tmp->leftChild;
    }
}
node* BST::scannerNext(){ //On pre goes down left, Mid does self, post goes right
    if (scanner.empty()){
        return nullptr;
    }

    // when we remove a value, add it's right then left's
    node *toRet = scanner.top()->data;
    

    //right value
    BSTNode *toAdd = scanner.top()->rightChild;
    scanner.pop();
    while (toAdd->data != nullptr){
        scanner.push(toAdd);
        toAdd = toAdd->leftChild;
    }

    return toRet;
}

// Outputs an array of pointers to the topX items in said tree.
node** BST::mostFrequent(int topX){
    node **topWords = new node*[topX];
    for (int i = 0; i < topX; i++){
        topWords[i] = nullptr;
    }

    scannerReset();
    node *data = scannerNext();
    while(data != nullptr){
        for (int i = 0; i<topX; i++){
            if (topWords[i] == nullptr){ //if it is empty. We found the spot
                topWords[i] = data;
                break;
            } else if (data->count > topWords[i]->count){
                for (int shifter = topX-1; shifter > i; shifter--){
                    topWords[shifter] = topWords[shifter - 1];
                }
                topWords[i] = data;
                break;
            }
        }
        data = scannerNext();
    }

    return topWords;
}