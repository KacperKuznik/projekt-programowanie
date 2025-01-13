#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <regex>

class History
{
public:
    static std::string findFileName();
    static void addTextToFile(std::string text, std::string history_file_name);

    template <typename T>
    static std::string to_string(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};
