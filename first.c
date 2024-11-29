
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void removeWhitespaces(char *exp)
{
    char *p = exp;
    char *q = exp;
    while (*q != '\0')
    {
        if (!isspace(*q))
        {
            *p++ = *q;
        }
        q++;
    }
    *p = '\0';
};

bool checkValidity(char *exp)
{
    char oprs[4] = {'+', '-', '*', '/'};
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (!(exp[i] >= '0' && exp[i] <= '9') && !(exp[i] == '+' || exp[i] == '*' || exp[i] == '-' || exp[i] == '/'))
        {
            return false;
        }
        if ((exp[i] == oprs[0] || exp[i] == oprs[1] || exp[i] == oprs[2] || exp[i] == oprs[3]) && (exp[i + 1] == oprs[0] || exp[i + 1] == oprs[1] || exp[i + 1] == oprs[2] || exp[i + 1] == oprs[3]))
        {
            return false;
        }
        if (exp[i] == '/' && exp[i + 1] == '0')
        {
            return false;
        }
    }
    return true;
}

int calculate(const char *exp)
{
    int stack[100];      
    int top = -1;        
    char sign = '+';     
    int num = 0;         
    int i = 0;           
    int len = strlen(exp); 

    for (i = 0; i < len; i++)
    {
        char c = exp[i];

        if (isdigit(c))
        {
            num = num * 10 + (c - '0');
        }

        // if the char is operator or end of string
        if (!isdigit(c) && c != ' ' || i == len - 1)
        {
            if (sign == '+')
            {
                stack[++top] = num;
            }
            else if (sign == '-')
            {
                stack[++top] = -num;
            }
            else if (sign == '*')
            {
                stack[top] = stack[top] * num;
            }
            else if (sign == '/')
            {
                stack[top] = stack[top] / num;
            }

            sign = c;
            num = 0;
        }
    }

    int result = 0;
    for (i = 0; i <= top; i++)
    {
        result += stack[i];
    }

    return result;
}

int main()
{
    char exp[100];
    printf("Enter the mathematical expression: ");
    fgets(exp, 100, stdin);
    removeWhitespaces(exp);
    if (checkValidity(exp))
    {
        int result = calculate(exp);
        printf("Result: %d\n", result);
    }
    else
    {
        printf("Invalid expression\n");
    };
    return 0;
}
