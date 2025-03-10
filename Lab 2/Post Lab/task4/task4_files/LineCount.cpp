#include "LineCount.h"
#include <fstream>
using namespace std;

LineCount::LineCount(const string& file) : file(file) {}

int LineCount::countLines() {
    ifstream inFile(file);
    if (!inFile) return -1;

    string line;
    int lineCount = 0;
    while (getline(inFile, line)) {
        lineCount++;
    }
    return lineCount;
}
