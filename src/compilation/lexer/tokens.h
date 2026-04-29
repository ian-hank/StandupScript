#pragma once

#include <string>

struct Token {
    std::optional<std::string> value;
    int line;
    int column;
};