#pragma once

#include "standup_node.h"

struct ProgramNode {
    // assumes that there is only ever one standup block, if we decide to support
    // more than one `standup` per program node we need to move to vector
    StandupNode node;
};