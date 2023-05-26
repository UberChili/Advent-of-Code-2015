#include <algorithm>
#include <iostream>
#include <fstream>
#include <format>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::istringstream;


// Instructions object to store the information about a wire
struct instructions_obj {
    bool has_value {false};
    std::vector<std::string> args;
    std::string operation;
    unsigned short value;
    std::string wire;
};


// Checks if a string is a valid number by traversing all individual characters and calling std::isdigit() on them
// if all characters are digits, then it is a valid number
bool isnumber(const std::string& str) {
    if (str.empty())
        return false;

    for (char c : str) {
        if (!std::isdigit(c))
            return false;
    }

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


// Checks the (vec of strs) parsed_line, builds the corresponding instructions_obj and adds it to the map
void add_to_map(std::unordered_map<std::string, instructions_obj>& map, std::vector<std::string> parsed_line) {
    std::string operation = contains_operation_instruction(parsed_line);
    std::vector<std::string> args;
    unsigned short value;
    bool has_value = false;
    std::string wire = parsed_line.back();

    if (operation == "->") {
        if (isnumber(parsed_line[0])) {
            value = static_cast<unsigned short>(std::stoul(parsed_line[0]));
            has_value = true;
        }
        else {
            value = 0;
            args.push_back(parsed_line[0]);
        }
    }
    else if (operation == "NOT") {
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


// Recursive function that calculates signals.
// Searchs for a key in a map, if it exists, checks the operation of the wire and applies said operation to its arguments
unsigned short get_signal(std::unordered_map<std::string, instructions_obj>& map, std::string key) {
    std::string op;
    std::vector<std::string> args;

    if (auto search = map.find(key); search != map.end()) {
        if (search->second.has_value == true) {
            return search->second.value;
        }
        else {
            args = search->second.args;
            op = search->second.operation;

            if (op == "->") {
                search->second.has_value = true;
                search->second.value = get_signal(map, args[0]);
                return search->second.value;
            }

            else if (op == "AND") {
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
            }

            else if (op == "OR") {
                search->second.has_value = true;
                search->second.value = get_signal(map, args[0]) bitor get_signal(map, args[1]);
                return search->second.value;
            }

            else if (op == "LSHIFT") {
                unsigned short left = get_signal(map, args[0]);
                unsigned short right;

                if (isnumber(args[1])) {
                    right = static_cast<unsigned short>(std::stoul(args[1]));
                }
                search->second.has_value = true;
                search->second.value = left << right;
                return search->second.value;
            }

            else if (op == "RSHIFT") {
                unsigned short left = get_signal(map, args[0]);
                unsigned short right;

                if (isnumber(args[1])) {
                    right = static_cast<unsigned short>(std::stoul(args[1]));
                }
                search->second.has_value = true;
                search->second.value = left >> right;
                return search->second.value;
            }

            else if (op == "NOT") {
                search->second.has_value = true;
                search->second.value = ~get_signal(map, args[0]) bitand 0xffff;
                return search->second.value;
            }
            return 0;
        }
    }
    else {
        std::cout << "Not found\n";
        return 0;
    }
}


//  Pretty much just a little debugging, or 'pretty printing' function. Has no use in the actual functionality of the program
void get_value_from_map(std::unordered_map<std::string, instructions_obj>& map, std::string key) {
    if (map.contains(key)) {
        std::cout << std::format("{}: {}\t Value: {}\n Operation: {}\n Args: ", key, map.at(key).has_value, map.at(key).value, map.at(key).operation);
        for (const auto& arg : map.at(key).args) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << std::format("{} Not found in map\n", key);
        return;
    }
}


int main(int argc, char *argv[]){
    if (argc != 3) {
        std::cout << "Usage: ./day07 [input] [key]\n";
        return 1;
    }

    std::string key = argv[2];

    std::ifstream input;
    input.open(argv[1]);

    if (input.is_open()) {
        std::string line;
        std::vector<std::string> splitted_line;
        std::unordered_map<std::string, instructions_obj> wires;

        while (std::getline(input, line)) {
            // std::cout << line << " ";

            splitted_line = split(line);
            add_to_map(wires, splitted_line);
        }

        // get_value_from_map(wires, key);
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
