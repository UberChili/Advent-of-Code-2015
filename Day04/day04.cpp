#include <iostream>
#include <iomanip>
#include <openssl/md5.h>

int main() {
    std::string message = "Hello, world!"; // Define the message you want to hash

    unsigned char digest[MD5_DIGEST_LENGTH]; // Declare an array to hold the hash value
    MD5((unsigned char*) message.c_str(), message.length(), digest); // Compute the MD5 hash

    std::cout << "MD5 hash of the message: ";
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    std::cout << std::endl;

    return 0;
}
