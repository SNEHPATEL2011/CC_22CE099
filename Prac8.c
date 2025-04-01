#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10
#define MAX_INPUT 100

typedef struct {
    char nonTerminal;
    char productions[MAX_RULES][MAX_SYMBOLS];
    int productionCount;
} GrammarRule;

GrammarRule grammar[MAX_RULES];
int ruleCount = 0;

void addRule(char nonTerminal, char *production) {
    for (int i = 0; i < ruleCount; i++) {
        if (grammar[i].nonTerminal == nonTerminal) {
            strcpy(grammar[i].productions[grammar[i].productionCount], production);
            grammar[i].productionCount++;
            return;
        }
    }
    grammar[ruleCount].nonTerminal = nonTerminal;
    strcpy(grammar[ruleCount].productions[0], production);
    grammar[ruleCount].productionCount = 1;
    ruleCount++;
}

int isNonTerminal(char c) {
    return isupper(c);
}

int validateString(char *input) {
    char stack[MAX_INPUT];
    int top = -1;
    stack[++top] = '$';
    stack[++top] = 'S';

    int i = 0;
    while (top >= 0) {
        char topSymbol = stack[top--];

        if (topSymbol == '$' && input[i] == '\0') {
            return 1;
        }

        if (isNonTerminal(topSymbol)) {
            int found = 0;
            for (int j = 0; j < ruleCount; j++) {
                if (grammar[j].nonTerminal == topSymbol) {
                    for (int k = grammar[j].productionCount - 1; k >= 0; k--) {
                        int len = strlen(grammar[j].productions[k]);
                        for (int l = len - 1; l >= 0; l--) {
                            stack[++top] = grammar[j].productions[k][l];
                        }
                    }
                    found = 1;
                    break;
                }
            }
            if (!found) return 0;
        } else if (topSymbol == input[i]) {
            i++;
        } else {
            return 0;
        }
    }

    return input[i] == '\0';
}

int main() {
    addRule('S', "aB");
    addRule('S', "bA");
    addRule('S', "c");
    addRule('A', "a");
    addRule('A', "b");
    addRule('B', "b");
    addRule('B', "c");

    char testCases[][MAX_INPUT] = {"abc", "ac", "c", "a", "b", "bc"};
    int testCaseCount = 6;

    for (int i = 0; i < testCaseCount; i++) {
        if (validateString(testCases[i])) {
            printf("Valid string: %s\n", testCases[i]);
        } else {
            printf("Invalid string: %s\n", testCases[i]);
        }
    }

    return 0;
}