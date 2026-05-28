#pragma once

struct SourceLocation {
    int line;
    int column;
};

struct SourceSpan {
    SourceLocation start;
    SourceLocation end;
};