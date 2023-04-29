#include <iostream>
#include <fstream>
#include <sstream>
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

std::string get_instructions(std::string line) {
    std::vector<std::string> tokens = split(line);

    if (tokens.at(0) == "toggle") {
        return "toggle";
    }
    else if (tokens.at(0) == "turn") {
        if (tokens.at(1) == "on") return "on";
        else if (tokens.at(1) == "off") return "off";
    }
    return "error";
}

std::pair<int, int> get_pair(std::string text) {
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;

    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }
    return {std::stoi(tokens.at(0)), std::stoi(tokens.at(1))};
}

std::pair<int, int> get_from(std::string line) {
    std::vector<std::string> tokens = split(line);
    std::pair<int, int> from;

    if (tokens.size() == 4) {
        from = get_pair(tokens.at(1));
    }
    else if (tokens.size() == 5) {
        from = get_pair(tokens.at(2));
    }
    return from;
}

std::pair<int, int> get_to(std::string line) {
    std::vector<std::string> tokens = split(line);
    std::pair<int, int> to;
    to = get_pair(tokens.back());

    // if (tokens.size() == 4) {
    //     to = get_pair(tokens.at(1));
    // }
    // else if (tokens.size() == 5) {
    //     to = get_pair(tokens.at(2));
    // }
    return to;
}

std::vector<std::vector<bool>> toggle(std::vector<std::vector<bool>> lights, std::pair<int, int> from, std::pair<int, int> to) {
    for (int col = from.first; col <= to.first; col++) {
        for (int row = from.second; row <= to.second; row++) {
            if (lights[col][row] == true) {
                lights[col][row] = false;
            }
            else if (lights[col][row] == false){
                lights[col][row] = true;
            }
        }
    }
    return lights;
}

std::vector<std::vector<bool>> turn_on(std::vector<std::vector<bool>> lights, std::pair<int, int> from, std::pair<int, int> to) {
    for (int col = from.first; col <= to.first; col++) {
        for (int row = from.second; row <= to.second; row++) {
            lights[col][row] = true;
        }
    }
    return lights;
}

std::vector<std::vector<bool>> turn_off(std::vector<std::vector<bool>> lights, std::pair<int, int> from, std::pair<int, int> to) {
    for (int col = from.first; col <= to.first; col++) {
        for (int row = from.second; row <= to.second; row++) {
            lights[col][row] = false;
        }
    }
    return lights;
}

void print_lights(std::vector<std::vector<bool>> lights) {
    std::ofstream file("output.txt");

    if (file.is_open()) {
        for (int col = 0; col < lights.size() - 1; col++) {
            for (int row = 0; row < lights.size() - 1; row++) {
                if (lights[col][row] == true) {
                    file << "*";
                }
                else {
                    file << " ";
                }
            }
            std::cout << std::endl;
        }
        file.close();
        std::cout << "File created and written to successfully\n";
    }
    else {
        std::cout << "Error opening file output.txt" << std::endl;
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
        std::vector<std::vector<bool>> lights(1000, std::vector<bool>(1000, false));

        // for (int col = 0; col < lights.size() - 1; col++) {
        //     for (int row = 0; row < lights.size() - 1; row++) {
        //         // std::cout << "lights[" << col << "][" << row << "] = " << lights[col][row] << std::endl;
        //     }
        // }

        std::pair<int, int> from;
        std::pair<int, int> to;
        while (std::getline(input, line)) {
            // from = get_from(line);
            // to = get_to(line);
            // std::cout << line << " from = "
            //           << "{" << from.first << ", " << from.second
            //           << "}" << " to = "
            //           << "{" << to.first << ", " << to.second
            //           << "}" << std::endl;

            //
            // std::cout << "Instruction: " << get_instructions(line) << std::endl;
            if (get_instructions(line) == "toggle") {
                lights = toggle(lights, get_from(line), get_to(line));
            }
            else if (get_instructions(line) == "on") {
                lights = turn_on(lights, get_from(line), get_to(line));
            }
            else if (get_instructions(line) == "off") {
                lights = turn_off(lights, get_from(line), get_to(line));
            }
        }
        double counter = 0;
        for (int col = 0; col < lights.size(); col++) {
            for (int row = 0; row < lights.size(); row++) {
                if (lights[col][row] == true) counter++;
            }
        }
        std::cout << "Lights on: " << counter << std::endl;


        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
