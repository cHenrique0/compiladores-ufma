#include "./TokenType.h"
#include <stdlib.h>
#include <stdio.h>
#include "./utils.c"

void GLC(tokenType *tokens)
{

    for (size_t i = 0; i < SIZEOF(&tokens); i++)
    {
        if (tokens[i].type == INVALID_TOKEN)
            printf("ERROR: Invalid token: '%s'\n", tokens[i].token);
        else if (tokens[i].type == READ)
        {
            if (tokens[i].row != tokens[i + 1].row)
            {
                printf("%s -> ERROR\n", tokens[i].token);
            }
            else if (tokens[i + 1].type == VAR)
                printf("%s -> MATCH\n", tokens[i].token);
            else
            {
                printf("ERROR: %s %s\n", tokens[i].token, tokens[i + 1].token);
                printf("LINE: %d\n", tokens[i].row);
                printf("Expected VAR after '%s'\n", tokens[i].token);
            }
        }
    }
}