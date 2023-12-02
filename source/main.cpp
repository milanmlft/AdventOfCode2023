#include <fstream>
#include <iostream>
#include <string>

using std::string;

void printProcessedFile(std::string fileName) {
    std::ifstream infile(fileName);

    string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
}

int main() {
    try {
        printProcessedFile("data/day1-input.txt");
    } catch (std::exception &e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        std::cout << "We no longer have access to the file handle." << std::endl;
    }

    return 0;
}
