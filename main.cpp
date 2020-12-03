#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <chrono>

#include "BST.h"
using namespace std;

int main(int argc, char* argv[]){
    
    ifstream inFile(argv[1]);

    if (!inFile.is_open()){
        cout << "[ ! ] File is not open" << endl;
        return 0;
    }

    
    BST *rbBST = new BST();
    BST *bBST = new BST();
    vector<string> words;

    string tmp;
    while(getline(inFile, tmp)){
        stringstream ss(tmp);
        tmp = "";
        ss >> tmp;
        words.push_back(tmp);
    }

    std::chrono::_V2::system_clock::time_point startTime, stopTime;
    chrono::duration_cast<chrono::microseconds>(stopTime - startTime).count();

    startTime = chrono::high_resolution_clock::now();
    for (string word : words){
        bBST->bstAdd(word);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MicroSeconds for basic: " << chrono::duration_cast<chrono::microseconds>(stopTime - startTime).count() << endl;

    delete bBST;

    startTime = chrono::high_resolution_clock::now();
    for (string word : words){
        rbBST->insert(word);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MicroSeconds for rb: " << chrono::duration_cast<chrono::microseconds>(stopTime - startTime).count() << endl;

    // myBST.printInOrderBST();
    // cout << "----------\n";
    // myBST.printWord("a");
    // cout << "----------\n";
    // myBST.printWord("aa");
    // cout << "----------\n";
    // myBST.printWord("aaa");
    // cout << "----------\n";
    // myBST.printWord("aah");
    // cout << "----------\n";
    // myBST.printInOrderBST();
}