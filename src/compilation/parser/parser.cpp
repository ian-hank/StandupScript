#include "parser.h"
#include "parse_error.h"

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

// ********* PROGRAM NODE ********* //
ProgramNode Parser::parseProgram() {
    ProgramNode pNode;
    pNode.standup = parseStandup();

    consume(
        TokenType::eof,
        "Expected end of input (EOF) after the standup block."
    );

    return pNode;
}

// ********* STANDUP NODE ********* //
StandupNode Parser::parseStandup() {
    consume(
        TokenType::kw_standup, 
        "Expected 'standup' keyword to begin file."
    );

    const Token& titleToken = consume(
        TokenType::lit_string, 
        "Expected string literal after 'standup' keyword."
    );

    consume(
        TokenType::left_curly_bracket,
        "Expected '{' folowing standup title."
    );

    StandupNode sNode;
    sNode.title = titleToken.value.value_or("");
    sNode.statements.push_back(parseDateStatement());
    sNode.statements.push_back(parseTagStatement());
    parseAttendeeStatement();
    while (check(TokenType::kw_attendee)) {
        parseAttendeeStatement();
    }

    if (check(TokenType::kw_summary)) {
        parseSummaryStatement();
    }

    while (!check(TokenType::right_curly_bracket) && !isAtEnd()) {
        sNode.statements.push_back(parseStatement());
    }

    consume(
        TokenType::right_curly_bracket,
        "Expected '}' to end standup block."
    );

    return sNode;
}

// ********* STATEMENT NODES ********* //
std::unique_ptr<StatementNode> Parser::parseStatement() {
    switch (current().tokenType) {
        case TokenType::kw_section: {
            return parseSectionStatement();
        }

        case TokenType::kw_note: {
            return parseNoteStatement();
        }

        case TokenType::kw_decision: {
            return parseDecisionStatement();
        }

        case TokenType::kw_todo: {
            return parseTodoStatement();
        }

        case TokenType::kw_blocker: {
            return parseBlockerStatement();
        }

        case TokenType::kw_risk: {
            return parseRiskStatement();
        }

        case TokenType::kw_link: {
            return parseLinkStatement();
        }

        default: throw ParseError("Expected at least one statement within block.", current().line, current().column);
    }
}

std::unique_ptr<DateStatementNode> Parser::parseDateStatement() {
    consume(
        TokenType::kw_date,
        "Expected 'date' keyword to begin date statement."
    );

    const Token& dateToken = consume(
        TokenType::lit_date,
        "Expected date literal after 'date' in format YYYY-MM-DD."
    );

    std::unique_ptr<DateStatementNode> dNode = std::make_unique<DateStatementNode>();
    dNode->value = dateToken.value.value_or("");
    return dNode;
}

std::unique_ptr<TagStatementNode> Parser::parseTagStatement() {
    consume(
        TokenType::kw_tag,
        "Expected 'tag' keyword to being tag statement."
    );

    const Token& tagToken = consume(
        TokenType::identifier,
        "Expected identifier after 'tag' keyword."
    );

    std::unique_ptr<TagStatementNode> tNode = std::make_unique<TagStatementNode>();
    tNode->value = tagToken.value.value_or("");
    return tNode;
}

std::unique_ptr<SectionStatementNode> Parser::parseSectionStatement() {
    consume(
        TokenType::kw_section,
        "Expected 'section' keyword to begin section statement."
    );

    const Token& sectionToken = consume(
        TokenType::lit_string,
        "Expected string literal after 'section' keyword."
    );

    consume(
        TokenType::left_curly_bracket,
        "Expected '{' folowing section title."
    );

    std::unique_ptr<SectionStatementNode> sNode = std::make_unique<SectionStatementNode>();
    sNode->title = sectionToken.value.value_or("");
    while(!check(TokenType::right_curly_bracket) && !isAtEnd()) {
        sNode->statements.push_back(parseStatement());
    }

    consume(
        TokenType::right_curly_bracket,
        "Expected '}' to close the section statement."
    );

    return sNode;
}

std::unique_ptr<AttendeeStatementNode> Parser::parseAttendeeStatement() {
    consume(
        TokenType::kw_attendee,
        "Expected 'attendee' keyword to begin attendee statment."
    );

    const Token& attendeeToken = consume(
        TokenType::identifier,
        "Expected identifer after 'attendee' keyword (the name of the attendee)"
    );
    std::unique_ptr<AttendeeStatementNode> aNode = std::make_unique<AttendeeStatementNode>();
    aNode->name = attendeeToken.value.value_or("");

    if (!check(TokenType::kw_as)) {
        return aNode;
    }

    consume(
        TokenType::kw_as,
        "Expected 'as' keyword after attendee identifier."
    );

    const Token& aliasToken = consume(
        TokenType::identifier,
        "Expected identifier after 'as' keyword (alias name)."
    );
    aNode->alias = aliasToken.value.value_or("");

    return aNode;
}

std::unique_ptr<SummaryStatementNode> Parser::parseSummaryStatement() {
    consume(
        TokenType::kw_summary,
        "Expected 'summary' keyword to begin summary statment."
    );

    const Token& summaryToken = consume(
        TokenType::lit_string,
        "Expected identifier after 'summary' keyword."
    );

    std::unique_ptr<SummaryStatementNode> sNode = std::make_unique<SummaryStatementNode>();
    sNode->value = summaryToken.value.value_or("");
    return sNode;
}

std::unique_ptr<NoteStatementNode> Parser::parseNoteStatement() {
    consume(
        TokenType::kw_note,
        "Expected 'note' keyword to begin note statement."
    );

    const Token& noteToken = consume(
        TokenType::lit_string,
        "Expected \"string literal\" after the 'note' keyword."
    );

    std::unique_ptr<NoteStatementNode> nNode = std::make_unique<NoteStatementNode>();
    nNode->value = noteToken.value.value_or("");

    return nNode;
}

std::unique_ptr<DecisionStatementNode> Parser::parseDecisionStatement() {
    consume(
        TokenType::kw_decision,
        "Expected 'decision' keyword to begin decision statement."
    );

    const Token& decisionToken = consume(
        TokenType::lit_string,
        "Expected a \"string literal\" after the 'decision' keyword."
    );

    std::unique_ptr<DecisionStatementNode> dNode = std::make_unique<DecisionStatementNode>();
    dNode->value = decisionToken.value.value_or("");

    return dNode;
}

std::unique_ptr<TodoStatementNode> Parser::parseTodoStatement() {
    consume(
        TokenType::kw_todo,
        "Expected 'todo' keyword to begin todo statement."
    );

    std::unique_ptr<TodoStatementNode> tNode = std::make_unique<TodoStatementNode>();
    while (check(TokenType::identifier)) {
        const Token& attendeeToken = consume(
            TokenType::identifier,
            "Expected identifier for attendee (or alias)."
        );
        tNode->attendees.push_back(attendeeToken.value.value_or(""));
    } // no attendee signals to make a todo applicable for all attendees

    if (match(TokenType::kw_by)) {
        const Token& dateToken = consume(
            TokenType::lit_date,
            "Expected a date literal after the 'by' keyword."
        );
        tNode->date = dateToken.value.value_or("");
    }

    if (match(TokenType::kw_priority)) {
        tNode->priority = parsePriority();
    }

    const Token& noteToken = consume(
        TokenType::lit_string,
        "Expected a \"string literal\" to end a note statement."
    );
    tNode->note = noteToken.value.value_or("");

    return tNode;
}

std::unique_ptr<BlockerStatementNode> Parser::parseBlockerStatement() {
    consume(
        TokenType::kw_blocker,
        "Expected 'blocker' keyword to begin blocker statement."
    );

    std::unique_ptr<BlockerStatementNode> bNode = std::make_unique<BlockerStatementNode>();
    while (check(TokenType::identifier)) {
        const Token& attendeeToken = consume(
            TokenType::identifier,
            "Expected identifier for attendee (or alias)."
        );
        bNode->attendees.push_back(attendeeToken.value.value_or(""));
    } // no attendee signals to make a blocker applicable for all attendees

    const Token& noteToken = consume(
        TokenType::lit_string,
        "Expected \"string literal\" to end a blocker statement."
    );
    bNode->note = noteToken.value.value_or("");

    return bNode;
}

std::unique_ptr<RiskStatementNode> Parser::parseRiskStatement() {
    consume(
        TokenType::kw_risk,
        "Expected 'risk' keyword to begin risk statement."
    );

    std::unique_ptr<RiskStatementNode> rNode = std::make_unique<RiskStatementNode>();
    if (match(TokenType::kw_priority)) {
        rNode->priority = parsePriority();
    }

    const Token& noteToken = consume(
        TokenType::lit_string,
        "Expected \"string literal\" to end a risk statement."
    );
    rNode->note = noteToken.value.value_or("");

    return rNode;
}

std::unique_ptr<LinkStatementNode> Parser::parseLinkStatement() {
    consume(
        TokenType::kw_link,
        "Expected 'link' keyword to begin link statement."
    );

    std::unique_ptr<LinkStatementNode> lNode = std::make_unique<LinkStatementNode>();
    const Token& linkToken = consume(
        TokenType::lit_string,
        "Expected a \"string literal\" after the 'link' keyword."
    );
    lNode->link = linkToken.value.value_or("");

    if (check(TokenType::lit_string)) {
        const Token& noteToken = consume(
            TokenType::lit_string,
            "Expected a \"string literal\" after link string literal."
        );
        lNode->note = noteToken.value.value_or("");
    }
    
    return lNode;
}

// ********* PARSING HELPERS ********* //
std::string Parser::parsePriority() {
    if (match(TokenType::kw_priority_low)) {
        return "low";
    } else if (match(TokenType::kw_priority_medium)) {
        return "medium";
    } else if (match(TokenType::kw_priority_high)) {
        return "high";   
    } else {
        throw ParseError(
            "Expected priority level 'low', 'medium', or 'high' after the 'priority' keyword.", 
            current().line, 
            current().column
        );
    }
}

// ********* CURSOR MOVEMENT ********* //
const Token& Parser::current() {
    return tokens[position];
}

const Token& Parser::previous() {
    return position == 0 
        ? tokens.back()
        : tokens[position - 1];
}

const Token& Parser::advance() {
    if (!isAtEnd()) {
        position++;
    }

    return previous();
}

const Token& Parser::consume(TokenType tokenType, const std::string& message) {
    if (check(tokenType)) {
        return advance();
    }

    throw ParseError(message, current().line, current().column);
}

bool Parser::isAtEnd() {
    return current().tokenType == TokenType::eof;
}

bool Parser::check(TokenType tokenType) {
    return current().tokenType == tokenType;
}

bool Parser::match(TokenType tokenType) {
    if (!check(tokenType)) {
        return false;
    }

    advance();
    return true;
}
