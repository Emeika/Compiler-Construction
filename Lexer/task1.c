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
    int operand_count = 1;

    if (expression[strlen(expression) - 1] != '$' || strlen(expression) > 10)
    {
        printf("Invalid string. must end with $ and maximum 5 operands\n");
        return 1;
    }

    printf("Program finds following tokens in the expression:\n");
    printf("Expression received: %s\n", expression);

    while (*expression != '$')
    {
        if ((*expression >= 'a' && *expression <= 'z') ||
            *expression == '+' || *expression == '-' ||
            *expression == '*' || *expression == '/')
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
            else
            {
                printf("Arithmetic operator: %c\n", *expression);
            }
        }
        else
        {
            printf("Invalid token encountered. Program terminated prematurely.\n");
            return 1;
        }

        expression++;
    }

    return 0;
}