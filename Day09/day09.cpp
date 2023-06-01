#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

using std::istringstream;


// Data structure to store locations and their neighbors
struct node {
    std::vector<node> neighbors;
    int distance;
};


int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day09 [input]\n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::string line;

        while (std::getline(input, line)) {

            std::cout << line << std::endl;
        }

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
