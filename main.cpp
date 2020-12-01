#include <iostream>
#include <fstream>
#include "BST.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[]){
    ifstream inFile(argv[1]);

    if (!inFile.is_open()){
        cout << "[ ! ] File is not open" << endl;
        return 0;
    }

    
    BST myBST;
    int lines = 1000;
    string tmp;
    while(getline(inFile, tmp)){// && lines >= 0){
        lines--;
        stringstream ss(tmp);
        tmp = "";
        ss >> tmp;
        myBST.addWordNode(tmp);
    }

    myBST.printInOrderBST();
}