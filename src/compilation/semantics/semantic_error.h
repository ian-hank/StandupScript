#pragma once

#include <string>

#include "source_location.h"

enum class SemanticErrorCode {
    InvalidDate,
};

struct SemanticError {
    SemanticErrorCode semanticCode;
    std::string message;
    SourceSpan location;
};