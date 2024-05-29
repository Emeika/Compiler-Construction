#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void tokenize_expression(char *expression)
{
    printf("Program finds following tokens in the expression:\n");
    printf("Expression received: %s\n", expression);

    int operand_count = 0;

    while (*expression != '$')
    {
        if (*expression >= 'a' && *expression <= 'z')
        {
            operand_count++;
            printf("int literal found: %c\n", *expression);
            if (operand_count > 5)
            {
                printf("More than five operands found.\n");
                exit(1);
            }
        }
        else if (*expression == '+' || *expression == '-' || *expression == '*' || *expression == '/')
        {
            printf("Arithmetic operator: %c\n", *expression);
        }
        else
        {
            printf("Invalid token encountered. Program terminated prematurely.\n");
            exit(1);
        }

        expression++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <expression>\n", argv[0]);
        return 1;
    }

    char *expression = argv[1];

    if (expression[strlen(expression) - 1] != '$' || strlen(expression) > 10)
    {
        printf("Invalid string. must end with $ and maximum 5 operands\n");
        return 1;
    }

    tokenize_expression(expression);

    return 0;
}