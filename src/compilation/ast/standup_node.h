#pragma once

#include <string>
#include <vector>

#include "statement_node.h"

struct StandupNode {
    std::string title;
    std::vector<std::unique_ptr<StatementNode>> statements;
};