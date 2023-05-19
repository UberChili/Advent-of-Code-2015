#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <stdexcept>
#include <vector>


struct instructions_obj {
    // std::vector<std::string> command_and_args;
    std::vector<std::string> args;
    std::string operation;
    unsigned short value;
    std::string wire;
};


// bool isnumber(std::vector<std::string> line) {
bool isnumber(std::string string) {
    try {
        unsigned short num = static_cast<unsigned short>(std::stoul(string));
        return true;
    }
    catch (const std::out_of_range& e) {
        return false;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
}


// splits a string by whitespaces and returns a vector of strings
std::vector<std::string> split(std::string line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
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

    return "NA";
}


unsigned short get_signal(std::unordered_map<std::string, instructions_obj>& map, std::string key) {
    // Just using this "auxiliary" vector to make it easier to write this portion of the code
    std::vector<std::string> args = map[key].args;

    if (map[key].value != 0) {
        return map[key].value;
    }
    // if (map[key].operation == "->") {
    //     std::cout << map[key].args[0] << " -> " << key << std::endl;

    //     if (isnumber(map[key].args[0])) {
    //         return static_cast<unsigned short>(std::stoul(map[key].args[0]));
    //     }
    //     else {
    //         return get_signal(map, args[0]);
    //     }
    // }

    else if (map[key].operation == "AND") {
        unsigned short arg;
        std::cout << args[0] << " AND " << args[1] << std::endl;
        if (isnumber(args[0])) {
            arg = static_cast<unsigned short>(std::stoul(args[0]));
            return arg & get_signal(map, args[1]);
        }
        else {
            return get_signal(map, args[0]) & get_signal(map, args[1]);
        }
    }
    else if (map[key].operation == "OR") {
        std::cout << map[key].operation << " " << map[key].args[0] << " " << map[key].args[1] << std::endl;
        return get_signal(map, args[0]) | get_signal(map, args[1]);
    }
    else if (map[key].operation == "LSHIFT") {
        std::cout << args[0] << " LSHIFT " << args[1] << std::endl;
        unsigned short arg = static_cast<unsigned short>(std::stoul(args[1]));
        return get_signal(map, args[0]) << arg;
    }
    else if (map[key].operation == "RSHIFT") {
        std::cout << args[0] << " RSHIFT " << args[1] << std::endl;
        unsigned short arg = static_cast<unsigned short>(std::stoul(args[1]));
        return (get_signal(map, args[0]) >> arg);
    }
    else if (map[key].operation == "NOT") {
        std::cout << "NOT " << args[0];
        return ~get_signal(map, args[0]);
    }

    return 0;
}


void add_to_map(std::unordered_map<std::string, instructions_obj>& map, std::vector<std::string> line) {
    auto split_it = std::find(line.begin(), line.end(), "->");
    std::vector<std::string> instruction(line.begin(), split_it);

    if (contains_operation_instruction(instruction) == "AND") {
        std::string operation = "AND";
        std::erase(instruction, "AND");
        std::string wire = line.back();
        map[wire] = instructions_obj{instruction, operation, 0, wire};
    }
    else if (contains_operation_instruction(instruction) == "OR") {
        std::string operation = "OR";
        std::erase(instruction, "OR");
        std::string wire = line.back();
        map[wire] = instructions_obj{instruction, operation, 0, wire};
    }
    else if (contains_operation_instruction(instruction) == "LSHIFT") {
        std::string operation = "LSHIFT";
        std::erase(instruction, "LSHIFT");
        std::string wire = line.back();
        map[wire] = instructions_obj{instruction, operation, 0, wire};
    }
    else if (contains_operation_instruction(instruction) == "RSHIFT") {
        std::string operation = "RSHIFT";
        std::erase(instruction, "RSHIFT");
        std::string wire = line.back();
        map[wire] = instructions_obj{instruction, operation, 0, wire};
    }
    else if (contains_operation_instruction(instruction) == "NOT") {
        std::string operation = "NOT";
        std::erase(instruction, "NOT");
        std::string wire = line.back();
        map[wire] = instructions_obj{instruction, operation, 0, wire};
    }
    else {
        std::string operation = "->";
        std::erase(instruction, "->");
        std::string wire = line.back();
        if (isnumber(line[0])) {
            unsigned short value = static_cast<unsigned short>(std::stoul(line[0]));
            map[wire] = instructions_obj{instruction, operation, value, wire};
        }
        else {
            map[wire] = instructions_obj{instruction, operation, 0, wire};
        }
    }
    // backup
    // auto split_it = std::find(line.begin(), line.end(), "->");
    // std::vector<std::string> instruction(line.begin(), split_it);
    // map[line.back()] = instructions_obj{instruction, line.back()};
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
        //     std::cout << key << ": " << "Op: " << value.operation << " " << "Args: ";
        //     for (const auto& i : value.args) {
        //         std:: cout << i << " ";
        //     }
        //     std::cout << std::endl;
        // }

        std::cout << "Wire a: " << get_signal(wires, "a") << std::endl;

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
