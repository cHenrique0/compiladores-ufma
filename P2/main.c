#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./TokenType.h"
#include "./utils.c"
// #include "./analLex.c"

// Panic Mode
/*
For each line of code
    Get the token from the lexical analyzer
    If the token is the expected token
        MATCH
    Else
        If it is the first token after the last MATCH or if it is the first token in the row
            PANIC (print the error message)
        Else
            Sweep forward to sync token (Get the next token?)
*/

// Mock code lines
char codeLines[] = "read x\ny:=10\nz:=x+y";
tokenType tokens[15];

void readFile(char *fileInput);
void GLC(tokenType *tokens, size_t length);

int main(int argc, char const *argv[])
{

    // Reading the file
    readFile("./teste.txt");

    GLC(tokens, SIZEOF(tokens));

    return 0;
}

// Read the file to analyze
void readFile(char *fileInput)
{
    FILE *file = fopen(fileInput, "r");
    char ch;
    int countLines = 0;
    char line[100];
    char *token;

    if (file == NULL)
    {
        printf("ERROR: File not found.\n");
    }
    else
    {

        int i = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            countLines++;

            token = strtok(line, " ");

            while (token != NULL)
            {
                token[strcspn(token, "\n")] = '\0';
                TokenType type = getTokenType(token);
                tokens[i].token = strdup(token);
                tokens[i].type = type;
                tokens[i].row = countLines;
                token = strtok(NULL, " ");
                i++;
            }
        }
    }

    fclose(file);

    // printf("\n> Number of lines: %d\n", countLines);
    /* for (size_t i = 0; i < SIZEOF(tokens); i++)
    {
        printf("%s -> %d\n", tokens[i].token, tokens[i].type);

        if (&tokens[i].type == END_OF_FILE)
            break;
    } */
}

void GLC(tokenType *tokens, size_t length)
{
    for (int i = 1; i <= length; i++)
    {
        printf("%s -> %d\n", tokens[i - 1].token, tokens[i - 1].type);
        printf("%s -> %d\n", tokens[i].token, tokens[i].type);
        // if (tokens[i].type == NULL)
        //     break;
        if (tokens[i - 1].type == INVALID_TOKEN)
        {
            printf("\nERROR: Invalid token: '%s'\n", tokens[i - 1].token);
            printf("LINE: %d\n", tokens[i - 1].row);
        }
        // <read> → read identifier
        else if (tokens[i - 1].type == READ)
        {
            if (tokens[i - 1].row != tokens[i].row)
            {
                printf("\n%s -> ERROR\n", tokens[i - 1].token);
            }
            else if (tokens[i].type == VAR)
            {
                printf("\n%s -> MATCH\n", tokens[i - 1].token);
                printf("%s -> MATCH\n", tokens[i].token);
            }
            else
            {
                printf("\nERROR: Expected VAR after '%s'\n", tokens[i - 1].token);
                printf("LINE: %d\n", tokens[i - 1].row);
            }
        }
        // <write> → write identifier
        else if (tokens[i - 1].type == WRITE)
        {
            if (tokens[i - 1].row != tokens[i].row)
            {
                printf("\n%s -> ERROR\n", tokens[i - 1].token);
            }
            else if (tokens[i].type == VAR)
            {
                printf("\n%s -> MATCH\n", tokens[i - 1].token);
                printf("%s -> MATCH\n", tokens[i].token);
            }
            else
            {
                printf("\nERROR: Expected VAR after '%s'\n", tokens[i - 1].token);
                printf("LINE: %d\n", tokens[i - 1].row);
            }
        }
        // <assign> → identifier := <arithmetic exp>
        /* else if (tokens[i].type == ASSIGN)
        {
            if (tokens[i - 1].row != tokens[i].row)
            {
                printf("\n%s -> ERROR\n", tokens[i - 1].token);
            }
            else if (tokens[i].type == VAR || tokens[i].type == NUM)
            {
                if (tokens[i].row != tokens[i + 1].row)
                {
                    printf("\n%s -> ERROR\n", tokens[i - 1].token);
                }
                else if (tokens[i + 1].type == ASSIGN)
                {
                }
            }
        } */
        // <arithmetic exp> → <operating> {<arithmetic op> <operating>}
        else if (tokens[i - 1].type == NUM || tokens[i - 1].type == VAR)
        {
            if (tokens[i - 1].row != tokens[i].row)
            {
                printf("\n%s -> ERROR\n", tokens[i - 1].token);
            }
            else if (tokens[i].type == ADD || tokens[i].type == SUB || tokens[i].type == MUL || tokens[i].type == DIV)
            {
                if (tokens[i].row != tokens[i + 1].row)
                {
                    printf("\n%s -> ERROR\n", tokens[i].token);
                }
                else if (tokens[i + 1].type == NUM || tokens[i + 1].type == VAR)
                {
                    printf("\n%s -> MATCH\n", tokens[i - 1].token);
                    printf("%s -> MATCH\n", tokens[i].token);
                    printf("%s -> MATCH\n", tokens[i + 1].token);
                }
                else
                {
                    printf("\nERROR: Expected NUM or VAR after '%s'\n", tokens[i].token);
                    printf("LINE: %d\n", tokens[i].row);
                }
            }
            else
            {
                printf("\nERROR: Expected '+', '-', '*' or '/' after '%s'\n", tokens[i - 1].token);
                printf("LINE: %d\n", tokens[i - 1].row);
            }
        }
        // <operating> → identifier | num
        else if (tokens[i - 1].type == NUM || tokens[i - 1].type == VAR)
        {
            printf("\n%s -> MATCH\n", tokens[i - 1].token);
        }
        // <arithmetic op> → + | *
        else if (tokens[i - 1].type == ADD || tokens[i - 1].type == MUL)
        {
            if (tokens[i - 1].row != tokens[i].row)
            {
                printf("\n%s -> ERROR\n", tokens[i - 1].token);
            }
            else if (tokens[i].type == NUM || tokens[i].type == VAR)
            {
                printf("\n%s -> MATCH\n", tokens[i - 1].token);
                printf("%s -> MATCH\n", tokens[i].token);
            }
            else
            {
                printf("\nERROR: Expected NUM or VAR after '%s'\n", tokens[i - 1].token);
                printf("LINE: %d\n", tokens[i - 1].row);
            }
        }
    }
}
