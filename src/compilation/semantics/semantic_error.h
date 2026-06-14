#pragma once

#include <string>

#include "source_location.h"

enum class SemanticErrorCode {
    InvalidDate_YearRange,
    InvalidDate_MonthRange,
    InvalidDate_DayRange,

    AttendeeDeclared,
    AttendeeAliasDeclared,
    TagDeclared,

};

struct SemanticError {
    SemanticErrorCode semanticCode;
    std::string message;
    SourceSpan location;
};