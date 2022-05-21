#include <stdio.h>
#include <ctype.h>

// Gobal declarations
char expr[20];
int i = 0;

// Function Prototyping
int E(void);
int E_Prime(void);
int T(void);
int T_Prime(void);
int F(void);
int id(char c);

int main(void)
{
    // Reading input
    printf("Enter an arithmetic expression : ");
    gets(expr);

    // Recursive descent parser logic
    if (E())
    {
        if (expr[i + 1] == '\0')
            puts("Accepted..!!!");
        else
            puts("Rejected..!!!");
    }
    else
        puts("Rejected..!!!");

    return 0;
}

// Production : E -> TE'
int E(void)
{
    if (T())
    {
        if (E_Prime())
            return 1;
        else
            return 0;
    }
    return 0;
}

// Production : E' -> +TE' | ε
int E_Prime(void)
{
    if (expr[i] == '+')
    {
        ++i;
        if (T())
        {
            if (E_Prime())
                return 1;

            else
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

// Production : T -> FT'
int T(void)
{
    if (F())
    {
        if (T_Prime())
        {
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

// Production : *FT' | ε
int T_Prime(void)
{
    if (expr[i] == '*')
    {
        ++i;
        if (F())
        {
            if (T_Prime())
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

// Production : (E) | id
int F(void)
{
    if (expr[i] == '(')
    {
        ++i;
        if (E())
        {
            if (expr[i] == ')')
                return 1;
            else
                return 0;
        }
    }
    else if (id(expr[i]))
    {
        return 1;
    }
    return 0;
}

// id refers to identifier
int id(char c)
{
    if (c == '_' || isalpha(c))
    {
        c = expr[++i];
        while (c == '_' || isalnum(c))
        {
            c = expr[++i];
        }
        return 1;
    }
    return 0;
}