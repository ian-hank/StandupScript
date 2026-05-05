#pragma once

#include <string>

#include "tokens.h"

namespace TokenUtils {
    std::string tokenTypeToString(const TokenType&);
    void printTokens(const std::vector<Token>&);
}
