#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include "./TokenType.h"

#define SIZEOF(a) sizeof(a) / sizeof(*a)

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

// Read the file to analyze
void readFile(char *fileInput)
{
    FILE *file = fopen(fileInput, "r");
    char ch;
    int countLines = 0;
    char line[100];
    char *token;
    tokenType tokens[10];

    if (file == NULL)
    {
        printf("ERROR: File not found.\n");
    }
    else
    {
        int i = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            token = strtok(line, " ");

            while (token != NULL)
            {
                token[strcspn(token, "\n")] = '\0';
                const int type = getTokenType(token);
                if (type != INVALID_TOKEN)
                {
                    tokens[i].token = strdup(token);
                    tokens[i].type = type;
                }
                token = strtok(NULL, " ");
                i++;
            }

            countLines++;
        }
    }

    fclose(file);

    printf("\n> Number of lines: %d\n", countLines);
    for (size_t i = 0; i < SIZEOF(tokens); i++)
    {
        printf("%s->%d\n", tokens[i].token, tokens[i].type);

        if (&tokens[i].type == END_OF_FILE)
            break;
    }
}

int main(int argc, char const *argv[])
{
    // Reading the file
    readFile("./teste.txt");

    return 0;
}
