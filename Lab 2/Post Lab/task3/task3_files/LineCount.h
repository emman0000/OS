#ifndef LINECOUNT_H
#define LINECOUNT_H

#include <string>  // Include string

class LineCount {
private:
    std::string file;
public:
    LineCount(const std::string& file);
    int countLines(); // Fix: Add countLines()
};

#endif

