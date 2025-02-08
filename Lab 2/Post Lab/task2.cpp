#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

// CHECK AP
bool isAP(int arr[], int size, int& d) {
    d = (arr[size - 1] - arr[0]) / size;  // find difference if APP
    int count = 0; 

    for (int i = 1; i < size; i++) {
        if (arr[i] - arr[i - 1] == d) {
            count++;
        }
    }
    return count >= size - 2;  //missing number condition
}

// GP CHECK
bool isGP(int arr[], int size, int& r) {
    if (size < 2 || arr[0] == 0) return false; // GP Only if more than 2 values

    r = arr[1] / arr[0]; // common ratio

    int count = 0; // count
    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1] * r) {
            count++;
        }
    }

    return count >= size - 2; // missing
}


// Function to find missing number in AP
int findMissingInAP(int arr[], int size, int d) {
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[i - 1] + d) {
            return arr[i - 1] + d;  
        }
    }
    return -1;
}

int findMissingInGP(int arr[], int size, int r) {
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[i - 1] * r) {
            return arr[i - 1] * r; //missing value
        }
    }
    return -1;
}


int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Error: Provide at least three numbers for a valid series.\n";
        return 1;
    }

    int size = argc - 1;
    int arr[size];

    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]); //conversion
    }

    int missing = -1;
    int d, r;

    if (isAP(arr, size, d)) {
        missing = findMissingInAP(arr, size, d);
        cout << "Detected: Arithmetic Progression (AP)\n";
    } 
    else if (isGP(arr, size, r)) {
        missing = findMissingInGP(arr, size, r);
        cout << "Detected: Geometric Progression (GP)\n";
    } 
    else {
        cout << "Error: Sequence is neither AP nor GP.\n";
        return 1;
    }

    ofstream file("output.txt");
    if (missing != -1) {
        file << "Missing Number: " << missing << endl;
        cout << "Missing number written to output.txt\n";
    } else {
        file << "No missing number found.\n";
        cout << "No missing number found.\n";
    }
    file.close();

    return 0;
}
