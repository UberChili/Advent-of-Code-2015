#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
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
std::string contains_operation_instruction(std::vector<std::string> line) {
    std::vector<std::string> search_words = {"AND", "OR", "LSHIFT", "RSHIFT", "NOT"};

    for (auto& word : line) {
        auto it = std::find(search_words.begin(), search_words.end(), word);

        if (it != search_words.end()) {
            return word;
            // std::cout << "Instruction found: " << word << std::endl;;
        }
    }

    return "NA";
}

// Uses the function 'contains_operation_instruction' on each line (line must be splitted beforehand)
// Then, it updates the map according to the operation found in the line
void check_and_apply(std::map<std::string, unsigned short> &map, std::vector<std::string> line) {
    if (contains_operation_instruction(line) == "AND") {
        map.insert_or_assign(line.back(), map[line[0]] & map[line[2]]);
    }
    else if (contains_operation_instruction(line) == "OR") {
        map.insert_or_assign(line.back(), map[line[0]] | map[line[2]]);
    }
    else if (contains_operation_instruction(line) == "LSHIFT") {
        map.insert_or_assign(line.back(), map[line[0]] << std::stoi(line[2]));
    }
    else if (contains_operation_instruction(line) == "RSHIFT") {
        map.insert_or_assign(line.back(), map[line[0]] >> std::stoi(line[2]));
    }
    else if (contains_operation_instruction(line) == "NOT") {
        map.insert_or_assign(line.back(), ~map[line[1]]);
    }
    else {
        try {
            unsigned short num = std::stoi(line[0]);
            map.insert_or_assign(line.back(), num);
        } catch (const std::invalid_argument& e) {
            map.insert_or_assign(line.back(), map[line[0]]);
        }
    }

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
            check_and_apply(identifiers, splitted_line);
        }

        for (const auto& [key, value] : identifiers) {
            // Printing it out just for testing
            std::cout << '[' << key << "] = " << value << std::endl;
        }

        // The following was just to understand bitwise operations, because I was a little unsure
        // (I started testing with ints, learning why that was incorrect and why we should use unsigned shorts instead)
        // Keeping this just for reference
        // unsigned short x = 123;
        // unsigned short y = 456;
        // unsigned short d = x & y;
        // unsigned short e = x | y;
        // unsigned short f = x << 2;
        // unsigned short g = y >> 2;
        // unsigned short h = ~x;
        // unsigned short i = ~y;
        // std::cout << "d: " << d << "e: " << e << "f: " << f << "g: " << g << "h: " << h << "i: " << i << "x: " << x << "y: " << y << std::endl;

        std::cout << "[a] = " << identifiers["a"] << std::endl;
        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
