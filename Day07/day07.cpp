#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::istringstream;

struct instructions_obj {
  // std::vector<std::string> command_and_args;
  std::vector<std::string> args;
  std::string operation;
  unsigned short value;
  std::string wire;
};


// bool isnumber(std::vector<std::string> line) {
bool isnumber(const std::string& str) {
    // Check if the string is empty
    if (str.empty())
        return false;

    // Iterate over each character in the string
    for (char c : str) {
        // Check if the character is not a digit
        if (!std::isdigit(c))
            return false;
    }

    // If all characters are digits, the string is a number
    return true;
}
// bool isnumber(std::string string) {
//     try {
//         unsigned short num = static_cast<unsigned short>(std::stoul(string));
//         return true;
//     }
//     catch (const std::out_of_range& e) {
//         return false;
//     }
//     catch (const std::invalid_argument& e) {
//         return false;
//     }
// }


// splits a string by whitespaces and returns a vector of strings
std::vector<std::string> split(std::string line) {
    std::vector<std::string> tokens;
    istringstream iss(line);
    std::string token;


    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}


// Checks if the line (a vector of strings) contains an operation instruction
std::string contains_operation_instruction(std::vector<std::string> line) {
    std::vector<std::string> search_words = {"AND", "OR", "LSHIFT", "RSHIFT", "NOT"};

    for (auto& word : line) {
        auto it = std::find(search_words.begin(), search_words.end(), word);

        if (it != search_words.end()) {
            return word;
            // std::cout << "Instruction found: " << word << std::endl;;
        }
    }

    return "->";
}

void add_to_map(std::unordered_map<std::string, instructions_obj>& map, std::vector<std::string> parsed_line) {
    std::string operation = contains_operation_instruction(parsed_line);
    std::vector<std::string> args;
    unsigned short value;
    std::string wire = parsed_line.back();

    if (operation == "->") {
        if (isnumber(parsed_line[0])) {
            value = static_cast<unsigned short>(std::stoul(parsed_line[0]));
        }
    }
    else if (operation == "NOT") {
        args.push_back(parsed_line[1]);
    }
    else {
        args.push_back(parsed_line[0]);
        args.push_back(parsed_line[2]);
    }

    map[wire] = {args, operation, value, wire};
}


unsigned short get_signal(std::unordered_map<std::string, instructions_obj>& map, std::string key) {
    std::vector<std::string> args;

    if (map[key].value) {
        return map[key].value;
    }
    else {
        args = map[key].args;

        if (map[key].operation == "AND") {
            if (isnumber(args[0]))
                return static_cast<unsigned short>(std::stoul(args[0])) bitand get_signal(map, args[1]);
            else
                return get_signal(map, args[0]) bitand get_signal(map, args[1]);
        }

        else if (map[key].operation == "OR") {
            return get_signal(map, args[0]) bitor get_signal(map, args[1]);
        }

        else if (map[key].operation == "LSHIFT") {
            unsigned short left = get_signal(map, args[0]);
            unsigned short right;

            if (isnumber(args[1])) {
                right = static_cast<unsigned short>(std::stoul(args[1]));
            }
            return left << right;
        }

        else if (map[key].operation == "RSHIFT") {
            unsigned short left = get_signal(map, args[0]);
            unsigned short right;

            if (isnumber(args[1])) {
                right = static_cast<unsigned short>(std::stoul(args[1]));
            }
            return left >> right;
        }

        else if (map[key].operation == "NOT") {
            return ~get_signal(map, args[0]);
        }
    }

    return 0;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day06 [input] \n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

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


        for (const auto& [key, value] : wires) {
            std::cout << key << ": Args: ";
            // std::cout << key << ": " << "Op: " << value.operation << " " << "Args: " << " Value: " << value.value;
            for (const auto& i : value.args) {
                std:: cout << i << " ";
            }
            std::cout << "Op: " << value.operation << " Value: " << value.value << std::endl;
        }
        std::cout << "Value of given key: " << get_signal(wires, "a") << std::endl;

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

        unsigned short x = 123;
        unsigned short y = 456;
        unsigned short d = x bitand y;
        unsigned short e = x bitor y;
        unsigned short f = x << 2;
        unsigned short g = y >> 2;
        unsigned short h = compl x;
        unsigned short i = compl y;
        std::cout << "d: " << d << "e: " << e << "f: " << f << "g: " << g << "h: " << h << "i: " << i << "x: " << x << "y: " << y << std::endl;

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
