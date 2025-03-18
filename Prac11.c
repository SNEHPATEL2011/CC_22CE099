#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef struct {
    char op[5];
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

Quadruple quads[MAX_LEN];
int quadIndex = 0;
int tempCount = 1;

char *newTemp() {
    static char temp[10];
    sprintf(temp, "t%d", tempCount++);
    return strdup(temp);
}

void addQuad(char *op, char *arg1, char *arg2, char *result) {
    strcpy(quads[quadIndex].op, op);
    strcpy(quads[quadIndex].arg1, arg1);
    strcpy(quads[quadIndex].arg2, arg2);
    strcpy(quads[quadIndex].result, result);
    quadIndex++;
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void processOperator(char op, char *val1, char *val2) {
    char *temp = newTemp();
    char opStr[2] = {op, '\0'};
    addQuad(opStr, val1, val2, temp);
    strcpy(val1, temp);
}

void generateQuadruples(char *expression) {
    char values[MAX_LEN][10];
    char ops[MAX_LEN];
    int valTop = -1, opTop = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        if (isspace(expression[i])) continue;
        
        if (isdigit(expression[i])) {
            char number[10] = {0};
            int j = 0;
            while (isdigit(expression[i])) number[j++] = expression[i++];
            i--;
            strcpy(values[++valTop], number);
        } 
        else if (expression[i] == '(') {
            ops[++opTop] = expression[i];
        } 
        else if (expression[i] == ')') {
            while (opTop >= 0 && ops[opTop] != '(') {
                char val2[10], val1[10];
                strcpy(val2, values[valTop--]);
                strcpy(val1, values[valTop--]);
                processOperator(ops[opTop--], val1, val2);
                strcpy(values[++valTop], val1);
            }
            opTop--; 
        } 
        else {
            while (opTop >= 0 && precedence(ops[opTop]) >= precedence(expression[i])) {
                char val2[10], val1[10];
                strcpy(val2, values[valTop--]);
                strcpy(val1, values[valTop--]);
                processOperator(ops[opTop--], val1, val2);
                strcpy(values[++valTop], val1);
            }
            ops[++opTop] = expression[i];
        }
    }

    while (opTop >= 0) {
        char val2[10], val1[10];
        strcpy(val2, values[valTop--]);
        strcpy(val1, values[valTop--]);
        processOperator(ops[opTop--], val1, val2);
        strcpy(values[++valTop], val1);
    }
}

void printQuadruples(char *expression) {
    printf("\nSample input output\n");
    printf("+--------------------------------------------+\n");
    printf("| Input: %-36s |\n", expression);
    printf("+------------+------------+------------+------------+\n");
    printf("| %-10s | %-10s | %-10s | %-10s |\n", "Operator", "Operand1", "Operand2", "Result");
    printf("+------------+------------+------------+------------+\n");
    for (int i = 0; i < quadIndex; i++) {
        printf("| %-10s | %-10s | %-10s | %-10s |\n", quads[i].op, quads[i].arg1, quads[i].arg2, quads[i].result);
    }
    printf("+------------+------------+------------+------------+\n");
}

int main() {
    char expression[MAX_LEN];
    printf("Enter an arithmetic expression: ");
    fgets(expression, MAX_LEN, stdin);
    expression[strcspn(expression, "\n")] = 0;

    generateQuadruples(expression);
    printQuadruples(expression);
    return 0;
}