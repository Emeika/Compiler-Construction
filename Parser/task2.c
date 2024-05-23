// E-> idE'
// E' -> +EE' | -EE' | *EE' | /EE' | ε

// E   -> TE'
// E'  -> +TE' | -TE' | ε
// T   -> FT'
// T'  -> *FT' | /FT' | ε
// F   -> id

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getOperandValues(char *expression, int **operandValues, int *size);
int has_higher_precedence(char op1, char op2);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <expression>", argv[0]);
        return 1;
    }

    char *expression = argv[1];
    int *operandValues = NULL;
    int size = 0;
    int operandItr = 0;
    getOperandValues(expression, &operandValues, &size);

    char *s1_stack = malloc(10);
    char *s2_input = malloc(10);
    int *result_stack = malloc(10);
    memset(s1_stack, '\0', 10);
    memset(s2_input, '\0', 10);
    memset(result_stack, '\0', 10);

    int top1 = -1, top2 = -1, result_itr = -1;

    for (int i = strlen(expression) - 1; i >= 0; i--)
    {
        s2_input[++top2] = expression[i];
    }

    s1_stack[++top1] = '$';

    printf("%-20s%-20s%-10s\n", "Stack", "Input", "Action");
    printf("================================================\n");

    while (1)
    {
        for (int i = strlen(s1_stack) - 1; i >= 0; i--)
        {
            putchar(s1_stack[i]);
        }

        int space = 20 - (int)strlen(s1_stack);
        printf("%-*s", space, "");

        for (int i = strlen(s2_input) - 1; i >= 0; i--)
        {
            putchar(s2_input[i]);
        }
        space = 20 - (int)strlen(s2_input);
        printf("%-*s", space, "");

        if (s1_stack[top1] == '$' && s2_input[top2] == '$')
        {
            printf("Accepted\n");
            break;
        }

        // when false 0 then push to s1 stack else when true pop
        if (has_higher_precedence(s1_stack[top1], s2_input[top2]))
        {
            printf("Pop\n");

            if (s1_stack[top1] >= 'a' && s1_stack[top1] <= 'z')
            {
                result_stack[++result_itr] = operandValues[operandItr++];
            }
            else
            {
                switch (s1_stack[top1])
                {
                case '+':
                    result_stack[result_itr - 1] = result_stack[result_itr] + result_stack[result_itr - 1];
                    result_stack[result_itr] = '\0';
                    result_itr--;
                    break;
                case '-':
                    result_stack[result_itr - 1] = result_stack[result_itr] - result_stack[result_itr - 1];
                    result_stack[result_itr] = '\0';
                    result_itr--;
                    break;
                case '*':
                    result_stack[result_itr - 1] = result_stack[result_itr] * result_stack[result_itr - 1];
                    result_stack[result_itr] = '\0';
                    result_itr--;
                    break;
                case '/':
                    result_stack[result_itr - 1] = result_stack[result_itr] / result_stack[result_itr - 1];
                    result_stack[result_itr] = '\0';
                    result_itr--;
                    break;
                default:
                    break;
                }
            }

            s1_stack[top1] = '\0';
            top1--;
        }
        else if (has_higher_precedence(s1_stack[top1], s2_input[top2]) == 0)
        {
            printf("Push\n");
            s1_stack[++top1] = s2_input[top2];
            s2_input[top2] = '\0';
            top2--;
        }
    }

    // print calculation result
    printf("\nThe output of the given expression is: %d\n", *result_stack);

    free(operandValues);
    return 0;
}

void getOperandValues(char *expression, int **operandValues, int *size)
{
    printf("Enter integer values of the following identifiers:\n");

    while (*expression != '$')
    {
        if (*expression >= 'a' && *expression <= 'z')
        {
            printf("Value of %c: \n", *expression);
            int value;
            scanf("%d", &value);

            // increase dynamic array size by 1
            (*size)++;
            *operandValues = (int *)realloc(*operandValues, (*size) * sizeof(int));
            if (*operandValues == NULL)
            {
                printf("Memory allocation failed. Exiting...");
                exit(1);
            }

            // store the value in the dynamic array
            (*operandValues)[*size - 1] = value;
        }

        expression++;
    }
}

int get_precedence(char op)
{
    switch (op)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '$':
        return 0;
    default:
        if (op >= 'a' && op <= 'z')
        {
            return 3;
        }
        else
        {
            return -1;
        }
    }
}

int has_higher_precedence(char op1, char op2)
{
    int precedence_op1 = get_precedence(op1);
    int precedence_op2 = get_precedence(op2);

    if (precedence_op1 == -1 || precedence_op2 == -1)
    {
        printf("Invalid operator\n");
        return -1;
    }

    // left associativity
    if (precedence_op1 == precedence_op2)
    {
        return 1;
    }

    return precedence_op1 > precedence_op2;
}
