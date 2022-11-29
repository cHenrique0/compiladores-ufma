#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./TokenType.h"
#include "./utils.c"
#include "./analSintatica.c"

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
    int lineLenght = 100;
    char line[lineLenght];
    char *token;
    int tokenLenght = 100;
    tokenType tokens[tokenLenght];

    for (int i = 0; i < tokenLenght; i++)
    {
        tokens[i].row = -1;
        tokens[i].type = EMPTY;
        tokens[i].token = NULL;
    }

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
            char tokenTemp[] = "";
            int countTokenTemp = 0;
            char *palavra = malloc(sizeof(char) * 100);
            int shouldBeSave = 1;

            for (int j = 0; j < lineLenght; j++)
            {
                if(line[j] == '\000') {
                    shouldBeSave = 0;
                    break;
                }
                
                if(line[j] != ' ' && line[j] != '\n')
                {
                    palavra[countTokenTemp] = line[j];
                    countTokenTemp++;

                    shouldBeSave = 0;

                    if(line[j+1] == '\000')
                    {
                        shouldBeSave = 1;
                    }
                }
                else if(line[j] == ' ' || line[j] == '\n')
                {
                    shouldBeSave = 1;
                }

                if( palavra[0] == '\000') shouldBeSave = 0;

                if(shouldBeSave){
                    palavra[countTokenTemp] = '\0';
                    tokens[i].type = getTokenType(palavra);
                    tokens[i].token = strdup(palavra);
                    tokens[i].row = countLines;
                    countTokenTemp = 0;
                    palavra[0] = '\0';
                    shouldBeSave = 0;
                    i++;
                }
            }
        }
    }

    GLC(tokens, SIZEOF(tokens));

    return 0;
}

// Read the file to analyze


