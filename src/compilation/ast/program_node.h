#pragma once

#include "standup_node.h"

struct ProgramNode {
    // assumes that there is only ever one standup block
    StandupNode standup;
};