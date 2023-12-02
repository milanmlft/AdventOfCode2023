#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

void printProcessedFile(string fileName) {
    std::ifstream infile(fileName);

    string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
}

vector<int> get_digits(string line) {
    vector<int> result;
    for (auto &c : line) {
        if (std::isdigit(c)) {
            result.push_back(int(c) - int('0'));
        }
    }
    return result;
}

int main() {
    vector<int> digits = get_digits("a1b2c3d4e5");
    for (auto &d : digits) {
        cout << d;
    }
    cout << endl;
    cout << int('1') - int('0') << endl;
    return 0;
}
