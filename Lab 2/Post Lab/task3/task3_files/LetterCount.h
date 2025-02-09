#ifndef LETTERCOUNT_H
#define LETTERCOUNT_H

#include <string>

class LetterCount {
private:
    std::string file;
public:
    LetterCount(const std::string& file);
    int letters();
};

#endif

