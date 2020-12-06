#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <chrono>

#include "BST.h"
using namespace std;

int main(int argc, char* argv[]){
    
    if (argc != 2 && argc != 3) {
        cout << "[ ! ] ERROR: Incorrect number of arguments." << endl;
        cout << argc;
        return 0;
    }

    ifstream inFile(argv[1]);
    if (!inFile.is_open()){
        cout << "[ ! ] ERROR: File " << argv[1] << " is not open" << endl;
        return 0;
    }

    int lines;
    if (argc == 3) {
        lines = stoi(argv[2]);
    } else {
        lines = -1;
    }


    cout << "building datasets ... ";
    cout.flush();

    vector<string> words;
    string tmp;
    while(getline(inFile, tmp) && (lines != 0)){
        stringstream ss(tmp);
        tmp = "";
        ss >> tmp;
        while (tmp != "") {
            words.push_back(tmp);
            tmp = "";
            ss >> tmp;
        }
        lines--;
    }
    cout << "Done, Datasize: " << words.size() << endl;
    
    string menu =
        "[ ! ] These are your options:\n"
        "\t-1: Exit\n"
        "\t1: Speed Comparison between unOptimized & Optimized Data Structures (Will take some time)\n"
        "\t2: Most Common Words\n"
        "\t3: Most Common Letter\n"
        "\t4: Find Words Between\n"
        "\t5: Total Words\n"
        "\t6: Unique Words\n"
        "\t7: Print it Pretty\n"
        "\t8: Print it Ugly\n"
        "\t9: Get Depth of Node\n"
        "\t10: Print Node\n"        
    ;
    int option = 0;
    while (true) {
        cout << menu;
        cout << "[ ? ] Please select an option: ";
        cin >> option;
        
        switch (option)
        {
        case -1:
        {
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            break;
        }
        case 8:
        {
            break;
        }
        case 9:
        {
            break;
        }
        case 10:
        {
            break;
        }
        default:
            break;
        }
    }
}
/*

    BST *rbBST = new BST();
    BST *bBST = new BST();
    /*
    for (string tmp : words){
        rbBST->rbInsert(tmp);
    }

    rbBST->scannerReset();
    node *data = rbBST->scannerNext();
    while(data != nullptr){
        cout << data->word << "[" << data->count << "]" << endl;
        data = rbBST->scannerNext();
    }
    
    
    std::chrono::_V2::system_clock::time_point startTime, stopTime;

    startTime = chrono::high_resolution_clock::now();
    for (string tmp : words){
        rbBST->rbInsert(tmp);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MiliSeconds to build rb: " << chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count() << endl;
    
    startTime = chrono::high_resolution_clock::now();
    for (string tmp : words){
        bBST->bstInsert(tmp);
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
*/