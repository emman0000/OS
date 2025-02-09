#include <iostream>
#include "LetterCount.h"
#include "WordCount.h"
#include "LineCount.h"
using namespace std;

int main() {
    string file = "funnywords.txt";

    LetterCount lc(file);
    WordCount wc(file);
    LineCount lnc(file);

    cout << "Letters: " << lc.letters() << endl;
    cout << "Words: " << wc.words() << endl;
    cout << "Lines: " << lnc.countLines() << endl;

    return 0;
}

