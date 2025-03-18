#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int evaluate(char *expr) {
    int num1, num2;
    char op;
    sscanf(expr, "%d %c %d", &num1, &op, &num2);

    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num2 != 0 ? num1 / num2 : 0;
        default: return 0;
    }
}

int isNumber(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int main() {
    char expression[100], optimized[100] = "";
    char *token;

    printf("Enter the arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;

    token = strtok(expression, " ");
    char lastNum[20] = "";

    while (token != NULL) {
        if (isNumber(token)) {
            if (strlen(lastNum) > 0) {
                char tempExpr[20];
                sprintf(tempExpr, "%s %s %s", lastNum, optimized[strlen(optimized) - 1] == ' ' ? optimized + strlen(optimized) - 2 : "+", token);
                int result = evaluate(tempExpr);
                sprintf(lastNum, "%d", result);
                optimized[strlen(optimized) - 2] = '\0';
            } else {
                strcpy(lastNum, token);
            }
        } else if (strchr("+-*/", token[0])) {
            strcat(optimized, lastNum);
            strcat(optimized, " ");
            strcat(optimized, token);
            strcat(optimized, " ");
            lastNum[0] = '\0';
        } else {
            strcat(optimized, lastNum);
            strcat(optimized, " ");
            strcat(optimized, token);
            strcat(optimized, " ");
            lastNum[0] = '\0';
        }
        token = strtok(NULL, " ");
    }

    strcat(optimized, lastNum);
    printf("\n| %-20s | %-20s |\n", "Input", "Output");
    printf("|----------------------|----------------------|\n");
    printf("| %-20s | %-20s |\n", expression, optimized);

    return 0;
}