#include "parser.h"
#include "parse_error.h"

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

ProgramNode Parser::parseProgram() {
    ProgramNode pNode;
    pNode.standup = parseStandup();

    consume(TokenType::eof, "Expected end of file after standup block.");
}

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
        "Exepcted '{' folowing standup title."
    );

    StandupNode sNode;
    sNode.title = titleToken.value.value_or("");

    while (!check(TokenType::right_curly_bracket) && !isAtEnd()) {
        sNode.statements.push_back(parseStatement());
    }
}

std::unique_ptr<StatementNode> Parser::parseStatement() {
    switch (current().tokenType) {
        case TokenType::kw_date: {
            return parseDateStatement();
        }

        case TokenType::kw_tag: {
            return parseTagStatement();
        }

        case TokenType::kw_attendee: {
            return parseAttendeeStatement();
        }

        case TokenType::kw_summary: {
            return parseSummaryStatement();
        }

        
    }

    throw ParseError("Expected at least one statement within standup block.", current().line, current().column);
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



const Token& Parser::current() {
    return tokens[position];
}

const Token& Parser::previous() {
    return tokens[position - 1];
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
    if (isAtEnd()) {
        return false;
    }

    return current().tokenType == tokenType;
}

bool Parser::match(TokenType tokenType) {
    if (!check(tokenType)) {
        return false;
    }

    advance();
    return true;
}
