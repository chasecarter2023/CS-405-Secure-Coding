// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <stdexcept>   // for std::runtime_error, std::invalid_argument
#include <string>

// Custom exception type derived from std::exception
class CustomException : public std::exception {
    std::string message_;
public:
    explicit CustomException(const std::string& msg)
        : message_(msg) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

// Simulate deeper application logic that may fail.
// Throws a standard exception to represent an error.
bool do_even_more_custom_application_logic()
{
    throw std::runtime_error("Even-more logic failure");

    // (Unreachable if exception is thrown)
    std::cout << "Running Even More Custom Application Logic." << std::endl;
    return true;
}

// Wrap deeper logic in a try–catch for std::exception, then
// simulate a business-rule failure by throwing a custom exception.
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        // Handle and log any std::exception from deeper logic
        std::cout << "[Caught std::exception in custom logic] "
            << e.what() << std::endl;
    }

    // After catching standard errors, throw our own domain-specific exception
    throw CustomException("Custom logic encountered a business rule violation");

    // (Unreachable)
    std::cout << "Leaving Custom Application Logic." << std::endl;
}

// Divide two floats, but guard against division by zero with a standard exception.
float divide(float num, float den)
{
    if (den == 0.0f) {
        throw std::invalid_argument("Attempted division by zero");
    }
    return num / den;
}

// Call divide() and catch only its invalid_argument exception.
// Marked noexcept to guarantee no exceptions escape.
void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0.0f;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator
            << ") = " << result << std::endl;
    }
    catch (const std::invalid_argument& e) {
        // Handle divide-by-zero specifically
        std::cout << "[Division error] " << e.what() << std::endl;
    }
}

// The entry point: wrap all calls in ordered exception handlers.
// 1) CustomException
// 2) std::exception
// 3) catch-all (for anything unexpected)
int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& ce) {
        // Handle our custom business-rule errors first
        std::cout << "[CustomException caught in main] "
            << ce.what() << std::endl;
    }
    catch (const std::exception& se) {
        // Handle any other std::exception
        std::cout << "[std::exception caught in main] "
            << se.what() << std::endl;
    }
    catch (...) {
        // Last-resort catch-all (use sparingly—can hide bugs)
        std::cout << "[Unknown exception caught in main]" << std::endl;
    }

    return 0;
}
