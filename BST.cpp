/* 
Implementation for BSH.h
Ty VanEssen 20-10-2020
*/
#include <iostream>
#include "BST.h"
using namespace std;

BST::BST(){
    root = nullptr;
    totalWords = 0;
}

int BST::addWordNode(string word){ //iteratively
    int operations = 0;
    totalWords++;
    BSTNode *result = searchBST(word, operations); // its either the parent of something to add or it is the right one.
    //returns null if the list is empty

    if (result == nullptr) {
        root = new BSTNode{word, nullptr, nullptr, nullptr};
        root->count+=1;
    } else if (result->word == word){
        operations += 1;
        result->count += 1;
    } else {
        BSTNode *newNode = new BSTNode{word, result, nullptr, nullptr};
        newNode->count += 1;
        if (word < result->word) {
            result->leftChild = newNode;
        } else {
            result->rightChild = newNode;
        }
    }

    return operations;
}

BSTNode* BST::searchBST(std::string word, int &opCounter) {
    BSTNode *tmp = root;
    BSTNode *parent = nullptr;

    opCounter += 1;
    while (tmp != nullptr) {

        parent = tmp;
        if (word < tmp->word) {
            opCounter += 1;
            tmp = tmp->leftChild;
        } else if (word > tmp->word) {
            opCounter += 2;
            tmp = tmp->rightChild;
        } else {
            return tmp;
        }
    }
    return parent;
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
    cout << node->word << "[" << node->count << "], " << flush;
    if (node->rightChild != nullptr) {
        printIOBST(node->rightChild);
    }
}

void BST::printWord(string word){
    int opers = 0;
    BSTNode *foundWord = searchBST(word, opers);
    if (foundWord->word != word) {
        cout << "[ ! ] Node not found, this would be the parent:\n";
    }
    cout << "\tWord: " << foundWord->word << endl;
    cout << "\tCount: " << foundWord->count << endl;
    cout << "\tParent: " << (foundWord->parent?foundWord->parent->word:"NoParent") << endl;
    cout << "\tLeft Child: " << (foundWord->leftChild?foundWord->leftChild->word:"NoChild") << endl;
    cout << "\tRight Child: " << (foundWord->rightChild?foundWord->rightChild->word:"NoChild") << endl;
}

int BST::countBSTNodes(){
    int num = 0;
    countBSTNodes(root, &num);
    return num;
}

void BST::countBSTNodes(BSTNode *node, int *count){
    if (node == nullptr) {
        return;
    } else {
        countBSTNodes(node->leftChild, count);
        (*count)++;
        countBSTNodes(node->rightChild, count);
    }
}

void BST::findAlphaRange(string word1, string word2){ //..<---- ASK HOW TO DO THIS REASONABLY???
    //fix any ordering
    string first, last;
    if (word1 < word2) {
        first = word1;
        last = word2;
    } else {
        first = word2;
        last = word1;
    }
    int counter = 0;
    
    if (searchBST(first, counter)->word != first || searchBST(last, counter)->word != last){
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
 
int BST::countTotalWords(){
    return totalWords;
}
// int main(){
//     BST myBST;
//     myBST.addWordNode("Hi");
//     myBST.addWordNode("Hi");
//     myBST.addWordNode("Bye");
//     myBST.addWordNode("A");
//     myBST.addWordNode("B");
//     myBST.addWordNode("C");
//     myBST.addWordNode("X");
//     myBST.addWordNode("Y");
//     myBST.addWordNode("Z");

//     myBST.printInOrderBST();

    // while (true) {
    //     string in;
    //     cout << "What node would you like to inspect?: ";
    //     cin >> in;
    //     myBST.printWord(in);
    // }

//     myBST.findAlphaRange("B", "X");
    
// }