#ifndef CONSOLESTYLE_H
#define CONSOLESTYLE_H

#include <iostream>
#include <string>

namespace ConsoleStyle {
inline constexpr const char* reset = "\033[0m";
inline constexpr const char* bold = "\033[1m";
inline constexpr const char* blue = "\033[34m";
inline constexpr const char* cyan = "\033[36m";
inline constexpr const char* green = "\033[32m";
inline constexpr const char* yellow = "\033[33m";
inline constexpr const char* red = "\033[31m";

inline void success(const std::string& message) {
    std::cout << green << "[OK] " << message << reset << '\n';
}

inline void error(const std::string& message) {
    std::cout << red << "[Error] " << message << reset << '\n';
}

inline void warning(const std::string& message) {
    std::cout << yellow << "[Warning] " << message << reset << '\n';
}
}

#endif
