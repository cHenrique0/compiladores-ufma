#include <stdio.h>
#include <string.h>

#define ACCEPT 1
#define REJECT 0
#define Q1 1
#define Q2 2
#define Q3 3
#define Q4 4
#define Q5 5

int main(int argc, char const *argv[])
{
    char fita[] = "/* Comentario *";
    char lex[strlen(fita)];
    int i = 0;
    int isAccepted = ACCEPT;
    int state = Q1;
    while (state != Q5 && i < strlen(fita) && isAccepted)
    {
        switch (state)
        {
        case Q1:
            printf("Q1 - %c\n", fita[i]);
            lex[i] = fita[i];
            switch (fita[i])
            {
            case '/':
                i++;
                state = Q2;
                break;
            default:
                isAccepted = REJECT;
                break;
            }
            break;
        case Q2:
            printf("Q2 - %c\n", fita[i]);
            lex[i] = fita[i];
            switch (fita[i])
            {
            case '*':
                i++;
                state = Q3;
                break;
            default:
                isAccepted = REJECT;
                break;
            }
            break;
        case Q3:
            printf("Q3 - %c\n", fita[i]);
            lex[i] = fita[i];
            switch (fita[i])
            {
            case '*':
                i++;
                state = Q4;
                break;
            default:
                i++;
                break;
            }
            break;
        case Q4:
            printf("Q4 - %c\n", fita[i]);
            lex[i] = fita[i];
            switch (fita[i])
            {
            case '*':
                i++;
                break;
            case '/':
                state = Q5;
                break;
            default:
                i++;
                state = Q4;
                break;
            }
            break;
        }
    }

    if (state == Q5 && isAccepted == ACCEPT)
    {
        printf("\n%s\n", lex);
        printf("> ACCEPTED\n");
        return 0;
    }
    printf("\n%s\n", lex);
    printf("> REJECTED\n");
    return 0;
}