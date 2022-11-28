#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType
{
    // Specials
    EMPTY = -3,
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
    int row;
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
    // regex_t id, num;
    // regcomp(&id, "^[a-zA-Z]", REG_EXTENDED | REG_NOSUB);
    // regcomp(&num, "^[0-9]", REG_EXTENDED | REG_NOSUB);

    // Symbols
    if (strcmp(type, ";") == 0)
        return SEMICOLON;
    if (strcmp(type, ":=") == 0)
        return ASSIGN;
    if (strcmp(type, "(") == 0)
        return BRACKET_OPEN;
    if (strcmp(type, ")") == 0)
        return BRACKET_CLOSE;

    // Logic operators
    if (strcmp(type, "=") == 0)
        return EQUAL;
    if (strcmp(type, "<") == 0)
        return LOWER;

    // Arithmetic operators
    if (strcmp(type, "+") == 0)
        return ADD;
    if (strcmp(type, "-") == 0)
        return SUB;
    if (strcmp(type, "*") == 0)
        return MUL;
    if (strcmp(type, "/") == 0)
        return DIV;

    // Keywords
    if (strcmp(type, "if") == 0)
        return IF;
    if (strcmp(type, "then") == 0)
        return THEN;
    if (strcmp(type, "else") == 0)
        return ELSE;
    if (strcmp(type, "end") == 0)
        return END;
    if (strcmp(type, "read") == 0)
        return READ;
    if (strcmp(type, "repeat") == 0)
        return REPEAT;
    if (strcmp(type, "until") == 0)
        return UNTIL;
    if (strcmp(type, "write") == 0)
        return WRITE;

    // Others
    // if ((regexec(&id, type, 0, NULL, 0)) == 0)
    //     return VAR;
    // if ((regexec(&num, type, 0, NULL, 0)) == 0)
    //     return NUM;

    int isLetter = 1;
    int isNum = 1;
    for (int i = 0; type[i] != '\0'; i++) { //sem strlen que seria péssimo
        if (type[i] < 'a' || type[i] > 'z') { //lógica mais adequada
            isLetter = 0;
            break;
        }
    }

    if(isLetter == 1) return VAR;

    for (int i = 0; type[i] != '\0'; i++) { //sem strlen que seria péssimo
        if (type[i] < '0' || type[i] > '9') { //lógica mais adequada
            isNum = 0;
            break; //encerra o laço, não tem porque continuar, achou algo que não muda mais
        }
    }

    if(isNum == 1) return NUM;

    return INVALID_TOKEN;
}

#endif