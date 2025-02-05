#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

bool isNumber(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && !(i == 0 && str[i] == '-')) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Error: Please provide at least one integer as an argument.\n";
        return 1;
    }

    int sum = 0, count = 0;

    for (int i = 1; i < argc; i++) {
        if (!isNumber(argv[i])) {
            cerr << "Error: Invalid input '" << argv[i] << "'. Only integers are allowed.\n";
            return 1;
        }

        int num = atoi(argv[i]);
        sum += num;
        count++;
    }

    double average = static_cast<double>(sum) / count;

    cout << "Sum: " << sum << "\n";
    cout << "Average: " << average << "\n";

    return 0;
}

