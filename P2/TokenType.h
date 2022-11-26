#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType
{
    // Specials
    UNEXPECTED_EOF = -2,
    INVALID_TOKEN = -1,
    END_OF_FILE = 0,

    // Symbols
    SEMICOLON,     // ;
    ASSIGN,        // :=
    BRACKET_OPEN,  // (
    BRACKET_CLOSE, // )

    // Logic operators
    EQUAL, // =
    LOWER, // <

    // Arithmetic operators
    ADD, // +
    SUB, // -
    MUL, // *
    DIV, // /

    // Keywords
    IF,     // if
    THEN,   // then
    ELSE,   // else
    END,    // end
    REPEAT, // repeat
    UNTIL,  // until
    READ,   // read
    WRITE,  // write

    // Others
    NUM, // number
    VAR, // variable
};

typedef struct TokenTypeString
{
    enum TokenType type;
    char *token;
} tokenType;

/* char *getTokenType(enum TokenType type)
{
    switch (type)
    {
    // Specials
    case UNEXPECTED_EOF:
        return "UNEXPECTED_EOF";
    case INVALID_TOKEN:
        return "INVALID_TOKEN";
    case END_OF_FILE:
        return "END_OF_FILE";

    // Symbols
    case SEMICOLON:
        return "semicolon";
    case ASSIGN:
        return "assign";
    case BRACKET_OPEN:
        return "bracket_open";
    case BRACKET_CLOSE:
        return "bracket_close";

    // Logic operators
    case equal:
        return "EQUAL";
    case LOWER:
        return "lower";

    // Arithmetic operators
    case ADD:
        return "add";
    case SUB:
        return "sub";
    case MUL:
        return "mul";
    case DIV:
        return "div";

    // Keywords
    case IF:
        return "if";
    case THEN:
        return "then";
    case ELSE:
        return "else";
    case END:
        return "end";
    case REPEAT:
        return "repeat";
    case UNTIL:
        return "until";
    case read:
        return "READ";
    case WRITE:
        return "write";

    // Others
    case NUM:
        return "num";

    default:
        printf("Invalid token type\n");
    }
} */

int getTokenType(char *type)
{
    regex_t id, num;
    regcomp(&id, "^[a-zA-Z]", REG_EXTENDED | REG_NOSUB);
    regcomp(&num, "^[0-9]", REG_EXTENDED | REG_NOSUB);

    if (strcmp(type, "read") == 0)
        return READ;

    if (strcmp(type, ":=") == 0)
        return ASSIGN;

    if (strcmp(type, "+") == 0)
        return ADD;

    if ((regexec(&id, type, 0, NULL, 0)) == 0)
        return VAR;

    if ((regexec(&num, type, 0, NULL, 0)) == 0)
        return NUM;

    return INVALID_TOKEN;
}

#endif