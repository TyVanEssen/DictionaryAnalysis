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

void BST::addWordNode(string word){ //iteratively
    totalWords++;
    BSTNode *result = searchBST(word); // its either the parent of something to add or it is the right one.
    //returns null if the list is empty

    if (result == nullptr) {
        root = new BSTNode{word, nullptr, nullptr, nullptr};
        root->count+=1;
    } else if (result->word == word){
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
}

BSTNode* BST::searchBST(std::string word) {
    BSTNode *tmp = root;
    BSTNode *parent = nullptr;
    while (tmp != nullptr) {

        parent = tmp;
        if (word < tmp->word) {
            tmp = tmp->leftChild;
        } else if (word > tmp->word) {
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
    BSTNode *foundWord = searchBST(word);
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