#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

// Where most of the work takes place. Simply counts the recurrences of characters and updates a counter, pretty straightforward
std::string calculate(std::string string) {
    std::string result = "";

    for (int i = 0, n = (int) string.length(); i < n; i++) {
        int count = 1;
        char curr = string[i];
        while(i < n && curr == string[i + 1]) {
            count++;
            i++;
        }
        result.push_back(static_cast<char>(count) + '0');
        result.push_back(curr);
    }

    return result;
}


// Need to change the times the loop will repeat, depending on Part 1 or Part 2 of the puzzle
int main(int argc, char *argv[]){
    if (argc != 2) {
        std::cout << "Usage: ./day10 [input]\n";
        return 1;
    }
    std::string input = argv[1];

    for(int i = 0; i < 50; i++) {
        input = calculate(input);
    }
    std::cout << input.length() << std::endl;

    return 0;
}
