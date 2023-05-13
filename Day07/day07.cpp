#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unordered_map>
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

void fill_map(std::unordered_map<std::string, std::vector<std::string>>& map, std::vector<std::string> line) {

    if (contains_operation_instruction(line) == "AND") {
       auto split_it = std::find(line.begin(), line.end(), "->");
       std::vector<std::string> instruction(line.begin(), split_it);

       map[line.back()] = instruction;
    }
    else if (contains_operation_instruction(line) == "OR") {
       auto split_it = std::find(line.begin(), line.end(), "->");
       std::vector<std::string> instruction(line.begin(), split_it);

       map[line.back()] = instruction;
    }
    else if (contains_operation_instruction(line) == "LSHIFT") {
       auto split_it = std::find(line.begin(), line.end(), "->");
       std::vector<std::string> instruction(line.begin(), split_it);

       map[line.back()] = instruction;
    }
    else if (contains_operation_instruction(line) == "RSHIFT") {
       auto split_it = std::find(line.begin(), line.end(), "->");
       std::vector<std::string> instruction(line.begin(), split_it);

       map[line.back()] = instruction;
    }
    else if (contains_operation_instruction(line) == "NOT") {
       auto split_it = std::find(line.begin(), line.end(), "->");
       std::vector<std::string> instruction(line.begin(), split_it);

       map[line.back()] = instruction;
    }
    else {
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
        std::unordered_map<std::string, std::vector<std::string>> wires;

        while (std::getline(input, line)) {
            // std::cout << line << " ";

            splitted_line = split(line);
        }

        // for (const auto& [key, value] : wires) {
        //     // Printing it out just for testing
        //     std::cout << '[' << key << "] = " << value << std::endl;
        // }

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

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
