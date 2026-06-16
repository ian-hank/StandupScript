#pragma once

#include <string>

#include "source_location.h"

enum class SemanticWarningCode {
    Note_IsBlankOrWhitespace,
    Decision_IsBlankOrWhitespace,

};

struct SemanticWarning {
    SemanticWarningCode semanticCode;
    std::string message;
    SourceSpan location;
};

