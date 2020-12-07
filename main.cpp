#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
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


    cout << "building dataset ... ";
    cout.flush();

    vector<string> words;
    string tmp;
    std::regex re(R"((\W|\s)+)");
    while(getline(inFile, tmp) && (lines != 0)){
        //aight we just gonna use regex resource: https://stackoverflow.com/questions/7621727/split-a-string-into-words-by-multiple-delimiters
        //tested with https://regex101.com/

        std::sregex_token_iterator first{tmp.begin(), tmp.end(), re, -1}, last;
        std::vector<std::string> tokens{first, last};
        for (auto t : tokens) {
            if (t.length() > 0) {
                string s = toLower(&t);
                words.push_back(s);
            }
        }
        lines--;
    }
    cout << "Done, Datasize: " << words.size() << endl;
    std::chrono::_V2::system_clock::time_point startTime, stopTime;


    BST *rbBST = new BST();
    startTime = chrono::high_resolution_clock::now();
    for (string tmp : words){
        rbBST->rbInsert(tmp);
    }
    stopTime = chrono::high_resolution_clock::now();
    cout << "MiliSeconds to build rb: " << chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count() << endl;

    string menu =
        "\n[ - ] These are your options:\n"
        "\t-1: Exit\n"
        "\t1: Speed Comparison between unOptimized & Optimized Data Structures (Will take some time)\n"
        "\t2: Most Common Words\n"
        "\t3: Most Common Letter\n"
        "\t4: Find Words Between\n"
        "\t5: Total Words\n"
        "\t6: Unique Words\n"
        "\t7: Print it Detailed\n"
        "\t8: Print it Basic\n"
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
        case -1: //Exit\n"
        {
            return(0);
            break;
        }
        case 1: //Speed Comparison between unOptimized & Optimized Data Structures (Will take some time)\n"
        {
            BST *bBST = new BST();
            
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

            cout << "If your values are too small, please use a larger dataset" << endl;
            break;
        }
        case 2: //Most Common Words\n" //TODO
        {
            int trackedWords  = -1;
            while (trackedWords <= 0){
                cout << "[ ? ] How many top words?: ";
                cin >> trackedWords;
                if (trackedWords <= 0) {
                    cout << "[ ! ] Please enter a positive number" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            trackedWords = (trackedWords <= rbBST->countBSTNodes()? trackedWords: rbBST->countBSTNodes());
            node ** topWords = rbBST->mostFrequent(trackedWords);

            for (int i = 0; i < trackedWords; i++){
                cout << "\t" << i+1 << ") " << topWords[i]->word << ":" << topWords[i]->count << endl;
            }
            break;
        }
        case 3: //Most Common Letter\n" //TODO
        {
            //iterate over everything then 
            //create the new structure
            BST *letters = new BST();
            rbBST->scannerReset();
            node* data = rbBST->scannerNext();
            while (data != nullptr){
                for (int let = 0; let < data->word.length(); let++){
                    letters->rbInsert(string(1,data->word[let]), data->count);
                }
                data = rbBST->scannerNext();
            }

            //find the top X
            int trackedLetters = -1;
            while (trackedLetters <= 0){
            cout << "[ ? ] How many top letters?: ";
                cin >> trackedLetters;
                if (trackedLetters <= 0) {
                    cout << "[ ! ] Please enter a positive number" << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            trackedLetters = (trackedLetters <= rbBST->countBSTNodes()? trackedLetters: rbBST->countBSTNodes());
            node** topLetters = letters->mostFrequent(trackedLetters);

            for (int i = 0; i < trackedLetters; i++){
                cout << "\t" << i+1 << ") " << topLetters[i]->word << ":" << topLetters[i]->count << endl;
            }
            break;
        }
        case 4: //Find Words Between\n"
        {
            string first, second;
            cout << "[ ? ] Between what two words?:\n[ ? ] Word 1: ";
            cin >> first;
            cout << "[ ? ] Word 2: ";
            cin >> second;
            toLower(&first);
            toLower(&second);
            rbBST->findAlphaRange(first, second);
            break;
        }
        case 5: //Total Words\n"
        {
            cout << "[ - ] There are " << rbBST->countTotalWords() << " sequences recognized as words in the file." << endl;
            break;
        }
        case 6: //Unique Words\n"
        {
            cout << "[ - ] There are " << rbBST->countBSTNodes() << " unique sequences recognized as words in the file." << endl;
            break;
        }
        case 7: //Print it Detailed\n"
        {
            rbBST->prettyPrint();
            break;
        }
        case 8: //Print it Basic\n"
        {
            rbBST->printInOrderBST();
            break;
        }
        case 9: //Get Depth of Node\n"
        {
            string nodeName;
            cout << "[ ? ] What node?: ";
            cin >> nodeName;
            toLower(&nodeName);
            cout << nodeName << " is at a depth of: " << rbBST->getDepth(nodeName) << endl;
            break;
        }
        case 10: //Print Node\n"
        {
            string nodeName;
            cout << "[ ? ] What node?: ";
            cin >> nodeName;
            toLower(&nodeName);
            rbBST->printWord(nodeName);
            break;
        }
        default:
            break;
        }
        
        if (cin.fail() || (option != -1 && (option > 10 || option < 1))){
            cout << "[ ! ] Please Enter a number in the range" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
    }
}
/*
    rbBST->scannerReset();
    node *data = rbBST->scannerNext();
    while(data != nullptr){
        cout << data->word << "[" << data->count << "]" << endl;
        data = rbBST->scannerNext();
    }
*/

