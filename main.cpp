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
    cout << "building datasets" << endl;
    
    BST *rbBST = new BST();
    BST *bBST = new BST();
    vector<string> words;
    int lines = 206;
    string tmp;
    while(getline(inFile, tmp)){// && lines > 0){
        lines--;
        stringstream ss(tmp);
        tmp = "";
        ss >> tmp;
        while (tmp != "") {
            words.push_back(tmp);
            tmp = "";
            ss >> tmp;
        }
        
    }
    std::chrono::_V2::system_clock::time_point startTime, stopTime;
    cout << "Datasize: " << words.size() << endl;

    startTime = chrono::high_resolution_clock::now();
    for (string tmp : words){
        rbBST->insert(tmp);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MiliSeconds to build rb: " << chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count() << endl;
    
    startTime = chrono::high_resolution_clock::now();
    for (string tmp : words){
        bBST->bstAdd(tmp);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MiliSeconds to build bb: " << chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count() << endl;
    
    // rbBST->prettyPrint();
    cout << "done building datasets" << endl;    


    
    startTime = chrono::high_resolution_clock::now();
    for (string word : words){
        rbBST->touchNode(word);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MiliSeconds to access every rb: " << chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count() << endl;

    startTime = chrono::high_resolution_clock::now();
    for (string word : words){
        bBST->touchNode(word);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MiliSeconds to access every bb: " << chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count() << endl;
}