#include "LetterCount.h"
#include <fstream>
#include <cctype>  // Needed for isalpha()
using namespace std;

LetterCount::LetterCount(const string& file) : file(file) {}

int LetterCount::letters() {
    ifstream inFile(file);
    if (!inFile) return -1;

    char ch;
    int letterCount = 0;
    while (inFile.get(ch)) {
        if (isalpha(ch)) letterCount++;
    }
    return letterCount;
}

