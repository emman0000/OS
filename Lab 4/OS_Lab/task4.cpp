#include <iostream>
#include <fstream>
using namespace std;

int main() {
  
    ifstream inputFile("input.txt");  
    if (!inputFile) {                 
        cout << "Unable to open input file!" << endl;
        return 1;
    }

    ofstream outputFile("output.txt");  
    if (!outputFile) {                 
        cout << "Unable to write in output file!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        outputFile << line << endl;
    }

  
    inputFile.close();
    outputFile.close();

    cout << "Content copied onto file successfully!" << endl;
    return 0;
}

