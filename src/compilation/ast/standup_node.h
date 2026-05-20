#pragma once

#include <string>
#include <vector>

#include "statement_node.h"
#include "source_location.h"

struct StandupNode {
    std::string title;
    std::vector<std::unique_ptr<StatementNode>> statements;
    SourceSpan location;
};