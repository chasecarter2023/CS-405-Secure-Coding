#define _CRT_SECURE_NO_WARNINGS   // optional if you stick with strncpy()
#include <iostream>
#include <string>
#include <cstring>     // for strncpy_s

int main() {
    std::cout << "Buffer Overflow Example\n";

    const std::string account_number = "CharlieBrown42";
    char user_input[20];

    std::cout << "Enter a value: ";
    std::string temp;
    std::getline(std::cin, temp);

    if (temp.size() >= sizeof(user_input)) {
        std::cout << "Error: input too long (max "
            << (sizeof(user_input) - 1) << " characters).\n";
        return 1;
    }

    // Safe copy using the "secure" CRT
    errno_t err = strncpy_s(
        user_input,
        sizeof(user_input),
        temp.c_str(),
        _TRUNCATE
    );
    if (err != 0) {
        std::cerr << "Unexpected copy error!\n";
        return 1;
    }

    std::cout << "You entered: " << user_input << "\n"
        << "Account Number = " << account_number << "\n";
    return 0;
}
