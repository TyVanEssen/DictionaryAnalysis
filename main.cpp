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
    int lines = 50;
    string tmp;
    while(getline(inFile, tmp) && lines >= 0){
        lines--;
        stringstream ss(tmp);
        tmp = "";
        ss >> tmp;
        myBST.addWordNode(tmp);
    }

    myBST.printInOrderBST();
    //myBST.printWord("1");
    myBST.leftRotate("1");
    myBST.leftRotate("2");
    myBST.leftRotate("4");
    myBST.printInOrderBST();
    cout << "----------\n";
    myBST.printWord("1");
    cout << "----------\n";
    myBST.printWord("2");
    cout << "----------\n";
    myBST.printWord("3");
    cout << "----------\n";
    myBST.printWord("4");
    cout << "----------\n";
    myBST.printWord("5");
    cout << "----------\n";
    myBST.printInOrderBST();
}