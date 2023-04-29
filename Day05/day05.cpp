#include <iostream>
#include <fstream>


bool has_three_vowels(std::string text) {
    int counter = 0;

    for (auto &letter : text) {

        if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u') {
            counter++;
            if (counter >= 3) return true;
        }
    }
    return false;
}


bool has_twice_inarow(std::string text) {
    for (int i = 1; i < text.length(); i++) {
        if (text[i] == text[i - 1]) return true;
    }
    return false;
}


bool contain_substring(std::string text) {
    if (text.find("ab") != std::string::npos) {
        return true;
    }
    else if (text.find("cd") != std::string::npos) {
        return true;
    }
    else if (text.find("pq") != std::string::npos) {
        return true;
    }
    else if (text.find("xy") != std::string::npos) {
        return true;
    }
    return false;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day05 [input] \n";
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);

    int counter = 0;
    if (input.is_open()) {
        // std::string line;
        // std::getline(input, line);

        std::string line;
        while (std::getline(input, line)) {
            // std::cout << line << std::endl;
            if (has_three_vowels(line) && has_twice_inarow(line)) {
                if (!contain_substring(line)){
                    counter += 1;
                }
                else {
                    continue;
                }
            }
            // if ((has_three_vowels(line)) && (has_twice_inarow(line))) {
            //     counter++;
            // }
        }
        std::cout << "Valid lines: " << counter << std::endl;


        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
