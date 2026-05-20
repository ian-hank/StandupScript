#pragma once

#include <string>

enum class SemanticErrorCode {
    InvalidDate,
};

struct SemanticError {
    SemanticErrorCode semanticCode;
    std::string message;
    int line;
    int column;
};