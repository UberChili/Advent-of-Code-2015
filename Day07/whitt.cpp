// Written by Whitt from #programming at lainchan.org IRC channel

#include <algorithm>
#include <iostream>
#include <fstream>
//#include <format>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::istringstream;

enum OP_CODE {
    APPLY,
    AND,
    OR,
    LSHIFT,
    RSHIFT,
    NOT,
};

struct instructions_obj {
    bool has_value {false};
    std::vector<std::string> args;
    OP_CODE operation;
    unsigned short value;
    std::string wire;
};


bool isnumber(const std::string& str) {
    if (str.empty())
        return false;

    for (char c : str) {
        // Check if the character is not a digit
        if (!std::isdigit(c))
            return false;
    }

    // If all characters are digits, the string is a number
    return true;
}


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
OP_CODE contains_operation_instruction(std::vector<std::string> line) {
    std::vector<std::string> search_words = {"AND", "OR", "LSHIFT", "RSHIFT", "NOT"};

    for (auto& word : line) {
        auto it = std::find(search_words.begin(), search_words.end(), word);

        if (it != search_words.end()) {
            if (word == "AND")
                return AND;
            if (word == "OR")
                return OR;
            if (word == "RSHIFT")
                return RSHIFT;
            if (word == "LSHIFT")
                return LSHIFT;
            if (word == "NOT")
                return NOT;
            // std::cout << "Instruction found: " << word << std::endl;;
        }
    }

    return APPLY;
}


void add_to_map(std::unordered_map<std::string, instructions_obj>& map, std::vector<std::string> parsed_line) {
    OP_CODE operation = contains_operation_instruction(parsed_line);
    std::vector<std::string> args;
    unsigned short value;
    bool has_value = false;
    std::string wire = parsed_line.back();

    if (operation == APPLY) {
        if (isnumber(parsed_line[0])) {
            value = static_cast<unsigned short>(std::stoul(parsed_line[0]));
            has_value = true;
        }
        else {
            value = 0;
            args.push_back(parsed_line[0]);
        }
    }
    else if (operation == NOT) {
        args.push_back(parsed_line[1]);
        value = 0;
    }
    else {
        args.push_back(parsed_line[0]);
        args.push_back(parsed_line[2]);
        value = 0;
    }
    map[wire] = {has_value, args, operation, value, wire};
}

unsigned short get_signal(std::unordered_map<std::string, instructions_obj>& map, std::string key) {
    OP_CODE op;

    unsigned short left;
    unsigned short right;

    std::vector<std::string> args;
    std::cout << "Getting signal '" << key << "'" << std::endl;
    if (auto search = map.find(key); search != map.end()) {
        // get_value_from_map(map, key);
        // if (search->second.has_value == true && search->second.operation == "->") {
        if (search->second.has_value == true) {
            return search->second.value;
        }
        else {
            args = search->second.args;
            op = search->second.operation;

            switch (op) {
            case APPLY:
                search->second.has_value = true;
                search->second.value = get_signal(map, args[0]);
                return search->second.value;
                break;
            case AND:
                if (isnumber(args[0])) {
                    search->second.has_value = true;
                    search->second.value = static_cast<unsigned short>(std::stoul(args[0])) bitand get_signal(map, args[1]);
                    return search->second.value;
                }

                else {
                    search->second.has_value = true;
                    search->second.value = get_signal(map, args[0]) bitand get_signal(map, args[1]);
                    return search->second.value;
                }
                break;
            case OR:
                search->second.has_value = true;
                search->second.value = get_signal(map, args[0]) bitor get_signal(map, args[1]);
                return search->second.value;
                break;
            case LSHIFT:
                left = get_signal(map, args[0]);

                if (isnumber(args[1])) {
                    right = static_cast<unsigned short>(std::stoul(args[1]));
                }
                search->second.has_value = true;
                search->second.value = left << right;
                return search->second.value;
                break;
            case RSHIFT:
                if (isnumber(args[1])) {
                    right = static_cast<unsigned short>(std::stoul(args[1]));
                }
                search->second.has_value = true;
                search->second.value = left >> right;
                return search->second.value;
                break;
            case NOT:
                search->second.has_value = true;
                search->second.value = ~get_signal(map, args[0]) bitand 0xffff;
                return search->second.value;
                break;
            default:
                return 0;
            }
            return 0;
        }
    }
    else {
        std::cout << key << " Not found\n";
        return 0;
    }
}

void get_value_from_map(std::unordered_map<std::string, instructions_obj>& map, std::string key) {
    if (map.contains(key)) {
        for (const auto& arg : map.at(key).args) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << key << " Not found in map" << std::endl;
        return;
    }
}


int main(int argc, char *argv[]){
    if (argc != 3) {
        std::cout << "Usage: ./day06 [input] [key]\n";
        return 1;
    }

    std::string key = argv[2];

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

        // for (const auto& [key, value] : wires) {
        //     std::cout << key << ": Args: ";
        //     // std::cout << key << ": " << "Op: " << value.operation << " " << "Args: " << " Value: " << value.value;
        //     for (const auto& i : value.args) {
        //         std:: cout << i << " ";
        //     }
        //     std::cout << "Op: " << value.operation << " Has value: " << value.has_value << " Value: " << value.value << std::endl;
        // }
        std::cout << "End." << std::endl;
        get_value_from_map(wires, key);
        std::cout << "Value of " << key << ": "<< get_signal(wires, key) << std::endl;

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
