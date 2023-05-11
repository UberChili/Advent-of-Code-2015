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

void AND(std::map<std::string, unsigned short>& map, std:: vector<std::string>& instruction) {
    unsigned short left;
    unsigned short right;

    try {
        left = static_cast<unsigned short>(std::stoul(instruction[0]));
        if (map.contains(instruction[2])) {
            right = map[instruction[2]];
        }
        else {
            map[instruction.back()] = left;
            return;
        }
    } catch (const std::invalid_argument& e) {
        if (map.contains(instruction[0])) {
            left = map[instruction[0]];
        }
        else {
            if (map.contains(instruction[2])) {
                left = map[instruction[2]];
            }
        }

        if (map.contains(instruction[2])) {
            right = map[instruction[2]];
        }
    }
    map[instruction.back()] = left & right;
}

void OR(std::map<std::string, unsigned short>& map, std:: vector<std::string>& instruction) {
    unsigned short left;
    unsigned short right;

    if (map.contains(instruction[0])) {
        left = map[instruction[0]];
    }
    if (map.contains(instruction[2])) {
        right = map[instruction[2]];
    }
    else if (!map.contains(instruction[0])) {
        left = right;
    }
    else if (!map.contains(instruction[2])) {
        right = left;
    }

    map[instruction.back()] = left | right;
}

void LSHIFT(std::map<std::string, unsigned short>& map, std:: vector<std::string>& instruction) {
    unsigned short left;
    unsigned short right = static_cast<unsigned short>(std::stoul(instruction[2]));

    if (map.contains(instruction[0])) {
        left = map[instruction[0]];
    }
    else {
        left = 1;
    }
    map[instruction.back()] = left << right;

    // map.insert_or_assign(instruction.back(), map[instruction[0]] | map[instruction[2]]);
}

void RSHIFT(std::map<std::string, unsigned short>& map, std:: vector<std::string>& instruction) {
    unsigned short left;
    unsigned short right = static_cast<unsigned short>(std::stoul(instruction[2]));

    if (map.contains(instruction[0])) {
        left = map[instruction[0]];
    }
    else {
        left = 1;
    }
    map[instruction.back()] = left >> right;
}

void NOT(std::map<std::string, unsigned short>& map, std:: vector<std::string>& instruction) {
    unsigned short right;

    if (map.contains(instruction[1])) {
        right = map[instruction[1]];
    }
    map[instruction.back()] = ~map[instruction[1]];
}

void ASSIGN(std::map<std::string, unsigned short>& map, std:: vector<std::string>& instruction) {
    unsigned short left;

    try {
        left = static_cast<unsigned short>(std::stoul(instruction[0]));
        map[instruction.back()] = left;
    } catch (const std::invalid_argument& e) {
        if (map.contains(instruction[0])) {
            map[instruction.back()] = map[instruction[0]];
        }
    }
}

// Uses the function 'contains_operation_instruction' on each line (line must be splitted beforehand)
// Then, it updates the map according to the operation found in the line
void check_and_apply(std::map<std::string, unsigned short>& map, std::vector<std::string> line) {
    if (contains_operation_instruction(line) == "AND") {
        AND(map, line);
        // map.insert_or_assign(line.back(), map[line[0]] & map[line[2]]);
    }
    else if (contains_operation_instruction(line) == "OR") {
        OR(map, line);
        // map.insert_or_assign(line.back(), map[line[0]] | map[line[2]]);
    }
    else if (contains_operation_instruction(line) == "LSHIFT") {
        LSHIFT(map, line);
        // map[line.back()] = map[line[0]] << static_cast<unsigned short>(std::stoul(line[2]));
        // map.insert_or_assign(line.back(), map[line[0]] << static_cast<unsigned short>(std::stoul(line[2])));
    }
    else if (contains_operation_instruction(line) == "RSHIFT") {
        RSHIFT(map, line);
        // map[line.back()] = map[line[0]] >> static_cast<unsigned short>(std::stoul(line[2]));
        // map.insert_or_assign(line.back(), map[line[0]] >> static_cast<unsigned short>(std::stoul(line[2])));
    }
    else if (contains_operation_instruction(line) == "NOT") {
        NOT(map, line);
        // map[line.back()] = ~map[line[1]];
        // map.insert_or_assign(line.back(), ~map[line[1]]);
    }
    else {
        ASSIGN(map, line);
        // try {
        //     unsigned short num = static_cast<unsigned short>(std::stoul(line[0]));
        //     map[line.back()] = num;
        //     // map.insert_or_assign(line.back(), num);
        // } catch (const std::invalid_argument& e) {
        //     map[line.back()] = map[line[0]];
        //     // map.insert_or_assign(line.back(), map[line[0]]);
        // }
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
        std::cout << "[b] = " << identifiers["b"] << std::endl;
        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
