#pragma once

#include <string>

#include "tokens.h"

namespace TokenUtils {
    std::string tokenTypeToString(TokenType);
    void printTokens(std::vector<Token>&);
}
