#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>


std::vector<std::string> split(std::string line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;


    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

// Checks if the line contains an operation instruction, input must be the splitted string (a vector)
// Still need to decide what this thing will return; either a bool or a std::string aren't enough
// Or are they?
std::string contains_operation_instruction(std::vector<std::string> line) {
    std::vector<std::string> search_words = {"AND", "OR", "LSHIFT", "RSHIFT", "NOT"};

    for (int i = 0, n = search_words.size(); i < n; i++) {
        auto it = std::find(line.begin(), line.end(), search_words[i]);

        if (it != line.end()) {
            // std::cout << "Instruction found: " << search_words[i] << std::endl;
            return search_words[i];
        }
    }
    return "No operation instruction found\n";
}


void check_and_apply(std::map<std::string, unsigned short> map, std::vector<std::string> line) {

    map[line.back()] = 0;

    return;
}

int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day06 [input] \n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    int counter = 0;
    if (input.is_open()) {
        // std::string line;
        // std::getline(input, line);

        std::string line;
        std::vector<std::string> splitted_line;
        std::map<std::string, unsigned short> identifiers;
        while (std::getline(input, line)) {
            // std::cout << line << " ";

            splitted_line = split(line);
            if (contains_operation_instruction(split(line)) == "NOT") {
                std::cout << "Found: NOT\n";
            }
        }

        // unsigned short x = 123;
        // unsigned short y = 456;
        // unsigned short d = x & y;
        // unsigned short e = x | y;
        // unsigned short f = x << 2;
        // unsigned short g = y >> 2;
        // unsigned short h = ~x;
        // unsigned short i = ~y;

        // std::cout << "d: " << d << "e: " << e << "f: " << f << "g: " << g << "h: " << h << "i: " << i << "x: " << x << "y: " << y << std::endl;

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
