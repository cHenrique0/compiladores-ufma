#include <stdio.h>
#include <string.h>

#define ACCEPT 1
#define REJECT 0
char fita[100] = "/* Comentario **/";

int q0(char symbol);
int q1(char symbol);
int q2(char symbol);
int q3(char symbol);
int q4();

int main(int argc, char const *argv[])
{
    /* printf("Digite o comentário:");
    scanf("%s", &fita);
    printf("%s\n", fita); */

    if (q0(0))
    {
        printf("\n> ACCEPTED\n");
        return 0;
    }
    printf("\n> REJECTED\n");

    return 0;
}

int q0(char symbol)
{
    printf("q0 - %c\n", fita[symbol]);
    switch (fita[symbol++])
    {
    case '/':
        return q1(symbol);
        break;

    default:
        return REJECT;
        break;
    }
}

int q1(char symbol)
{
    printf("q1 - %c\n", fita[symbol]);
    switch (fita[symbol++])
    {
    case '*':
        return q2(symbol);
        break;

    default:
        return REJECT;
        break;
    }
}

int q2(char symbol)
{
    printf("q2 - %c\n", fita[symbol]);
    switch (fita[symbol++])
    {
    case '*':
        return q3(symbol);
        break;

    default:
        return q2(symbol);
        break;
    }

    // return REJECT;
}

int q3(char symbol)
{
    printf("q3 - %c\n", fita[symbol]);
    switch (fita[symbol++])
    {
    case '*':
        return q3(symbol);
        break;

    case '/':
        return q4(symbol);
        break;

    default:
        break;
    }
}

int q4()
{
    return ACCEPT;
}