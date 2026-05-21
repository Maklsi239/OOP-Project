#ifndef CONSOLESTYLE_H
#define CONSOLESTYLE_H

#include <iostream>
#include <string>

using namespace std;

namespace ConsoleStyle {
    inline constexpr const char* reset = "\033[0m";
    inline constexpr const char* bold = "\033[1m";
    inline constexpr const char* blue = "\033[34m";
    inline constexpr const char* cyan = "\033[36m";
    inline constexpr const char* green = "\033[32m";
    inline constexpr const char* yellow = "\033[33m";
    inline constexpr const char* red = "\033[31m";

    inline void success(const string& message) {
        cout << green << "[OK] " << message << reset << endl;
    }

    inline void error(const string& message) {
        cout << red << "[Error] " << message << reset << endl;
    }

    inline void warning(const string& message) {
        cout << yellow << "[Warning] " << message << reset << endl;
    }
}

#endif