#pragma once

#include <limits>
#include <stdexcept>    


template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long steps)
{
    T result = start;
    const T max = std::numeric_limits<T>::max();

    for (unsigned long i = 0; i < steps; ++i)
    {
        
        if (increment > 0 && result > max - increment)
            throw std::overflow_error("add_numbers overflow");
        result += increment;
    }

    return result;
}


template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long steps)
{
    T result = start;
    const T min = std::numeric_limits<T>::lowest();  

    for (unsigned long i = 0; i < steps; ++i)
    {
        
        if (decrement > 0 && result < min + decrement)
            throw std::underflow_error("subtract_numbers underflow");
        result -= decrement;
    }

    return result;
}