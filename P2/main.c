#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./TokenType.h"
#include "./utils.c"
#include "./analLex.c"

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

int main(int argc, char const *argv[])
{

    // Reading the file
    FILE *file = fopen("./teste.txt", "r");
    char ch;
    int countLines = 0;
    char line[100];
    char *token;
    tokenType tokens[15];

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
                tokens[i].token = strdup(token);
                tokens[i].type = getTokenType(token);
                tokens[i].row = countLines;
                token = strtok(NULL, " ");
                i++;
            }
        }
    }

    GLC(tokens, SIZEOF(tokens));

    return 0;
}

// Read the file to analyze


