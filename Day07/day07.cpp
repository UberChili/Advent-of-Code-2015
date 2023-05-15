#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>


struct instructions_obj {
    std::vector<std::string> command_and_args;
    std::string dest_wire;
};


unsigned short isnumber(std::vector<std::string> line) {
    try {
        unsigned short num = static_cast<unsigned short>(std::stoul(line[0]));
        return num;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
}


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


unsigned short get_signal(std::unordered_map<std::string, instructions_obj>& map, std::string key) {
    // check if value of key is number
    // return if so
    unsigned short signal;


    return 0;
}


void add_to_map(std::unordered_map<std::string, instructions_obj>& map, std::vector<std::string> line) {
    auto split_it = std::find(line.begin(), line.end(), "->");
    std::vector<std::string> instruction(line.begin(), split_it);
    map[line.back()] = instructions_obj{instruction, line.back()};
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
        // std::unordered_map<std::string, std::vector<std::string>> wires;
        std::unordered_map<std::string, instructions_obj> wires;

        while (std::getline(input, line)) {
            // std::cout << line << " ";

            splitted_line = split(line);
            add_to_map(wires, splitted_line);
        }

        // for (const auto& [key, value] : wires) {
        //     std::cout << key << ": ";
        //     for (const auto& i : value.command_and_args) {
        //         std:: cout << i << " ";
        //     }
        //     std::cout << std::endl;
        // }

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
