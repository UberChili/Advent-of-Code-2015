#include <iostream>
#include <fstream>


bool contains_pair(std::string text) {
    for (int c = 0; c < text.length() - 1; c++) {
       std::string pair = text.substr(c, 2);
       size_t pos = text.find(pair, c + 1);
       if (pos != std::string::npos && pos != c + 1) {
           return true;
       }
    }
    return false;
}


bool contains_repeated_with_between(std::string text) {
    for (int i = 0; i < text.length() - 1; i++) {
        if (text[i] == text[i + 2]) {
           return true;
        }
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
            if (contains_repeated_with_between(line) && contains_pair(line)) {
                counter++;
            }
        }
        std::cout << "Valid lines: " << counter << std::endl;

        input.close();
    }
    else {
        std::cout << "Failed to open file " << argv[1] << std::endl;
    }

    return 0;
}
