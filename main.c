#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct exersise{
    int num1;
    int num2;
    char operator;
} EXERCISE;


// Function to get non-space symbol from inputBuf
char getC(const char *inputBuf, int *i)
{
    char c;
    do { c = inputBuf[(*i)++]; } while (c == ' ');
    return c;
}

// Function that parse and solve equations from inputBuf.
int solver(const char *inputBuf)
{
    EXERCISE ex;
    ex.num1 = 0;
    ex.num2 = 0;
    int i = 0;
    int res = 0;
    char c;


    c = getC(inputBuf, &i);
    if (isdigit(c)) {
        do {
            ex.num1 = ex.num1 * 10 + (c - '0');
            c = getC(inputBuf, &i);
        } while (isdigit(c));
    }

    if (c == '+' || c == '-' || c == '*' || c == '/') {
        ex.operator = c;
        c = getC(inputBuf, &i);
    } else {
        printf("\nError: There is no operation '%c', there is only '+', '-', '*', '/' .", c);
        return 1;
    }

    if (isdigit(c)) {
        do {
            ex.num2 = ex.num2 * 10 + (c - '0');
            c = getC(inputBuf, &i);
        } while (isdigit(c));
    }

    switch (ex.operator) {
        case '+': res = ex.num1 + ex.num2; break;
        case '-': res = ex.num1 - ex.num2; break;
        case '*': res = ex.num1 * ex.num2; break;
        case '/': res = ex.num1 / ex.num2; break;
    }

    printf("First number: %d;\nSecond number: %d;\nOperation: %c;\nResult: %d;", ex.num1, ex.num2, ex.operator, res);
    return 0;
}

int main(void)
{
    char *inputBuf = malloc(sizeof(char) * 64);
    puts("Enter your equation:");
    fgets(inputBuf, 63, stdin);
    inputBuf[strcspn(inputBuf, "\n")] = '\0';

    solver(inputBuf);

    free(inputBuf);
    return 0;
}