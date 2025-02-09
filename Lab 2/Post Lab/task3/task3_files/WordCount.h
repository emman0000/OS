#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#include <string>  // Include string

class WordCount {
private:
    std::string file;
public:
    WordCount(const std::string& file);
    int words();
};

#endif

