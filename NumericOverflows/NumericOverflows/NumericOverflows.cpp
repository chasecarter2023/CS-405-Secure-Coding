#include <iostream>
#include <limits>
#include <typeinfo>
#include <string>
#include "NumericFunctions.h"


template <typename T>
void test_overflow()
{
   
    const unsigned long steps = 5;
    const T               increment = std::numeric_limits<T>::max() / steps;
    const T               start = 0;
    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    

    
    std::cout << "\tAdding Numbers Without Overflow ("
        << +start << ", " << +increment << ", " << steps << ") = ";
    try {
        T result = add_numbers<T>(start, increment, steps);
        std::cout << +result;
    }
    catch (const std::overflow_error&) {
        std::cout << "[ERROR: overflow detected]";
    }
    std::cout << std::endl;

   
    std::cout << "\tAdding Numbers With Overflow ("
        << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    try {
        T result = add_numbers<T>(start, increment, steps + 1);
        std::cout << +result;
    }
    catch (const std::overflow_error&) {
        std::cout << "[ERROR: overflow detected]";
    }
    std::cout << std::endl;
}


template <typename T>
void test_underflow()
{
  
    const unsigned long steps = 5;
    const T               decrement = std::numeric_limits<T>::max() / steps;
    const T               start = std::numeric_limits<T>::max();
    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
   

   
    std::cout << "\tSubtracting Numbers Without Overflow ("
        << +start << ", " << +decrement << ", " << steps << ") = ";
    try {
        T result = subtract_numbers<T>(start, decrement, steps);
        std::cout << +result;
    }
    catch (const std::underflow_error&) {
        std::cout << "[ERROR: underflow detected]";
    }
    std::cout << std::endl;

   
    std::cout << "\tSubtracting Numbers With Overflow ("
        << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    try {
        T result = subtract_numbers<T>(start, decrement, steps + 1);
        std::cout << +result;
    }
    catch (const std::underflow_error&) {
        std::cout << "[ERROR: underflow detected]";
    }
    std::cout << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl
        << star_line << std::endl
        << "*** Running Overflow Tests ***" << std::endl
        << star_line << std::endl;

    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl
        << star_line << std::endl
        << "*** Running Underflow Tests ***" << std::endl
        << star_line << std::endl;

    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

int main()
{
    const std::string star_line(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    do_overflow_tests(star_line);
    do_underflow_tests(star_line);

    std::cout << std::endl
        << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}
