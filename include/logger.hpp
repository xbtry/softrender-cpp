#ifndef LOGGER_H
#define LOGGER_H

// Helper class

#include <print>
#include <iostream>
#include <concepts>

namespace Logger {

    enum class Color {
        Red, Green, Yellow, Blue, Magenta, Cyan, White, Default
    };

    inline constexpr const char* color_code(Color c) {
        switch (c) {
            case Color::Red:     return "\033[31m";
            case Color::Green:   return "\033[32m";
            case Color::Yellow:  return "\033[33m";
            case Color::Blue:    return "\033[34m";
            case Color::Magenta: return "\033[35m";
            case Color::Cyan:    return "\033[36m";
            case Color::White:   return "\033[37m";
            case Color::Default: 
            default:             return "\033[0m";
        }
    }

    // Base case: no arguments left - reset color and print newline
    inline void print_impl() {
        std::print("{}\n", color_code(Color::Default));
    }

    // Recursive variadic function to handle mixed arguments
    template<typename T, typename... Ts>
    void print_impl(T&& first, Ts&&... rest) {
        if constexpr (std::same_as<std::decay_t<T>, Color>) {
            // If argument is a Color, print color code only (no newline)
            std::print("{}", color_code(first));
        } else {
            // Otherwise print argument normally
            std::print("{}", std::forward<T>(first));
        }
        print_impl(std::forward<Ts>(rest)...); // recurse
    }

    // User-facing print function
    template<typename... Args>
    void print(Args&&... args) {
        print_impl(std::forward<Args>(args)...);
    }
}

#endif
