#pragma once

#include <string>

struct AttendeeInfo {
    int id;
    std::string name;
    std::optional<std::string> alias;
    SourceSpan location;
};