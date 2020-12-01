#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
    ifstream inFile(argv[1]);

    if (!inFile.is_open()){
        cout << "[ ! ] File is not open" << endl;
        exit;
    }

    int lines = 0;
    string tmp;
    while(getline(inFile, tmp)){
        lines++;
    }
    cout << "Lines = " << lines << endl;
}