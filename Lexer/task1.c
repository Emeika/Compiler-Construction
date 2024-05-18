#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    char *expression = argv[1];

    if (expression[strlen(expression) - 1] != '$' || strlen(expression) > 11)
    {
        printf("Invalid string. must end with $ and maximum 5 operands\n");
        return 1;
    }

    printf("Program finds following tokens in the expression:\n");
    printf("Expression received: %s\n", expression);

    while (*expression != '$')
    {
        switch (*expression)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            printf("Arithmetic operator: %c\n", *expression);
            break;
        default:
            break;
        }
        if (*expression >= 'a' && *expression <= 'z')
        {
            printf("int literal found: %c\n", *expression);
        }

        expression++;
    }
}