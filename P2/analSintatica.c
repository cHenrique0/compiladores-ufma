#include "./TokenType.h"
#include <stdlib.h>
#include <stdio.h>
#include "./utils.c"

tokenType nextTokenType;
tokenType actualTokenType;
tokenType lastTokenType;

// <assing> → identificador := <exp aritmética>
// x := 10
// := 10
// := x 
// x := 
int verifyAssign(){
    if(actualTokenType.type == ASSIGN)
    {
        // := 5
        // := 
        if(actualTokenType.row != nextTokenType.row || actualTokenType.row != lastTokenType.row)
        {
            printf("Error na linha: %d, valor invalido %s esperado um VAR ou NUM\n", actualTokenType.row, actualTokenType.token);
            return -1;
        }
        // := (x | 10)
        else if(nextTokenType.type == VAR || nextTokenType.type == NUM)
        {
            return 1;
        }
        
        printf("Error na linha: %d, valor invalido %s esperado um VAR ou NUM\n", actualTokenType.row, actualTokenType.token);
        return -1;
    }
    // x := 
    else if(nextTokenType.type == ASSIGN)
    {
        if(actualTokenType.type != VAR){
            printf("Error na linha: %d, valor invalido %s esperado um VAR\n", actualTokenType.row, actualTokenType.token);
            return -1;
        }

        return 1;
    }

    return 0;
}

// <arithmetic exp> → <operating> {<arithmetic op> <operating>}
// (identificador | num) | (+|*) (identificador | num)
// x
// 5
// (x | 5) (+ | *)
int verifyExpArr()
{
    // (x | 5) (+ | *)
    // (x | 5)
    if(actualTokenType.type == VAR || actualTokenType.type == NUM)
    {
        // (x | 5) (+ | *)
        if(actualTokenType.row != nextTokenType.row && actualTokenType.row != lastTokenType.row)
        {
            printf("Error na linha: %d, valor invalido %s esperado :=\n", actualTokenType.row, actualTokenType.token);
            return -1;
        }
        else if(actualTokenType.row == nextTokenType.row)
        {
            if(nextTokenType.type == ADD || nextTokenType.type == MUL)
            {
                return 1;
            }
            else{
                printf("Error na linha: %d, valor invalido %s esperado uma nova linha ou +,*\n", actualTokenType.row, actualTokenType.token);
                return -1;
            }
        }

        return 1;
    }

    return 0;
}

int verifyOpArr()
{
    // (+ | *) (num | var)
    if(actualTokenType.type == MUL || actualTokenType.type == ADD)
    {
        if(actualTokenType.row != nextTokenType.row || actualTokenType.row != lastTokenType.row)
        {
            // (+ | *) 
            printf("Error na linha: %d, valor invalido %s esperado VAR OU NUM\n", actualTokenType.row, actualTokenType.token);
            return -1;
        }
        else if(nextTokenType.type == NUM || nextTokenType.type == VAR)
        {
            return 1;
        }

        printf("Error na linha: %d, valor invalido %s esperado ou VAR OU NUM\n", actualTokenType.row, actualTokenType.token);
        return -1;
    }
        
    return 0;
}

int verifyRead(){
    // read x 
    if(actualTokenType.type == READ) 
    {
        if (nextTokenType.type == VAR && actualTokenType.row == nextTokenType.row)
        {
            return 1;
        }

        printf("Error na linha: %d, valor invalido %s esperado um VAR\n", actualTokenType.row, actualTokenType.token);
        return -1;
    }

    return 0;
}

int verifyWrite(){
    // write x 
    if(actualTokenType.type == WRITE) 
    {
        if (nextTokenType.type == VAR && actualTokenType.row == nextTokenType.row)
        {
            return 1;
        }

        printf("Error na linha: %d, valor invalido %s esperado um VAR\n", actualTokenType.row, actualTokenType.token);
        return -1;
    }

    return 0;
}

void GLC(tokenType *tokens, size_t length)
{
    for (int i = 0; i < length; i++)
    {
        if(actualTokenType.token == NULL) break;

        actualTokenType = tokens[i];
        nextTokenType;
        lastTokenType;

        nextTokenType.row = -1;
        nextTokenType.type = EMPTY;
        nextTokenType.token = NULL;

        lastTokenType.row = -1;
        lastTokenType.type = EMPTY;
        lastTokenType.token = NULL;
        
        nextTokenType = tokens[i + 1];

        if(i != 0){
            lastTokenType = tokens[i - 1];
        }

        if (actualTokenType.type == INVALID_TOKEN)
        {
            printf("\nERROR: Invalid token: '%s'\n", actualTokenType.token);
            printf("LINE: %d\n", actualTokenType.row);
        }
        // <read> → read identifier

        else if (verifyRead()!=0){
        }
        else if (verifyWrite()!=0){
        }
        else if(verifyAssign()!=0){
        }
        else if(verifyExpArr()!=0){
        }
        else if(verifyOpArr()!=0){
        }else{
            printf("Error na linha: %d, valor inesperado\n", actualTokenType.row, actualTokenType.token);
        }
       
    }
}