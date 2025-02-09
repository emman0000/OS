#include "WordCount.h"
#include <fstream>
#include <sstream>
using namespace std;

WordCount::WordCount(const string& file) : file(file) {}

int WordCount::words() {
    ifstream inFile(file);
    if (!inFile) return -1;

    string word;
    int wordCount = 0;
    while (inFile >> word) {
        wordCount++;
    }
    return wordCount;
}

