#include <stdio.h>
#include <string.h>

const char *input;

int S();
int L();
int LPrime();

int match(char expected) {
    if (*input == expected) {
        input++;
        return 1;
    }
    return 0;
}

int S() {
    if (match('a')) return 1;
    if (match('(')) {
        if (L() && match(')')) return 1;
    }
    return 0;
}

int L() {
    if (S()) return LPrime();
    return 0;
}

int LPrime() {
    if (match(',')) {
        if (S()) return LPrime();
        return 0;
    }
    return 1;
}

int main() {
    char expression[100];
    printf("Enter a string: ");
    scanf("%s", expression);
    input = expression;

    if (S() && *input == '\0')
        printf("Valid string\n");
    else
        printf("Invalid string\n");

    return 0;
}