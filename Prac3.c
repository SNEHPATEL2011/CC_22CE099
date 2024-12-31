#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

// Keywords in C
const char *keywords[] = {
    "int", "float", "char", "double", "return", "void", "if", "else", "while", "for", "break", "continue", "string", "struct", NULL
};

// Operators in C
const char operators[] = "+-*/=%<>!&|^=.";

// Punctuation symbols in C
const char punctuation[] = "(),;{}[]";

// Check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(keywords[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

// Check if a character is an operator
int isOperator(char ch) {
    return strchr(operators, ch) != NULL;
}

// Check if a character is a punctuation symbol
int isPunctuation(char ch) {
    return strchr(punctuation, ch) != NULL;
}

// Function to remove comments from the source code
void removeComments(char *line) {
    char temp[MAX];
    int i = 0, j = 0;
    int inSingleLineComment = 0;
    int inMultiLineComment = 0;

    while (line[i] != '\0') {
        // Detect and remove single-line comments
        if (!inMultiLineComment && !inSingleLineComment && line[i] == '/' && line[i+1] == '/') {
            inSingleLineComment = 1;
            i += 2; // Skip "//"
            continue;
        }
        // Detect and remove multi-line comments
        if (!inSingleLineComment && !inMultiLineComment && line[i] == '/' && line[i+1] == '*') {
            inMultiLineComment = 1;
            i += 2; // Skip "/*"
            continue;
        }
        if (inSingleLineComment && line[i] == '\n') {
            inSingleLineComment = 0; // End of single-line comment
        }
        if (inMultiLineComment && line[i] == '*' && line[i+1] == '/') {
            inMultiLineComment = 0; // End of multi-line comment
            i += 2; // Skip "*/"
            continue;
        }
        if (!inSingleLineComment && !inMultiLineComment) {
            temp[j++] = line[i];
        }
        i++;
    }

    temp[j] = '\0';
    strcpy(line, temp);
}

// Tokenize input string and count total tokens
void tokenize(const char *line) {
    char buffer[MAX];
    int i = 0, j = 0;
    int tokenCount = 0;  // Variable to count total tokens

    while (line[i] != '\0') {
        if (isspace(line[i])) {
            i++; // Skip whitespaces
            continue;
        }

        // Check for keywords, identifiers, or constants
        if (isalpha(line[i]) || line[i] == '_') {
            while (isalnum(line[i]) || line[i] == '_') {
                buffer[j++] = line[i++];
            }
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer)) {
                printf("Keyword: %s\n", buffer);
            } else {
                printf("Identifier: %s\n", buffer);
            }
            tokenCount++;  // Increment token count
        }
        // Check for numbers (constants)
        else if (isdigit(line[i])) {
            while (isdigit(line[i])) {
                buffer[j++] = line[i++];
            }

            if (line[i] == '.') {
                // If we encounter a decimal point, we handle it as part of the constant
                buffer[j++] = line[i++]; // Store '.'
                while (isdigit(line[i])) {
                    buffer[j++] = line[i++];
                }
                buffer[j] = '\0';
                printf("Constant: %s\n", buffer);
                tokenCount++;  // Increment token count
                j = 0;
            } else {
                buffer[j] = '\0';
                printf("Constant: %s\n", buffer);
                tokenCount++;  // Increment token count
                j = 0;
            }
        }
        // Check for string literals
        else if (line[i] == '"' || line[i] == '\'') {
            char quote = line[i++];
            while (line[i] != quote && line[i] != '\0') {
                buffer[j++] = line[i++];
            }
            if (line[i] == quote) {
                i++; // Skip closing quote
                buffer[j] = '\0';
                printf("String: '%s'\n", buffer);
            } else {
                printf("Error: Unterminated string\n");
            }
            tokenCount++;  // Increment token count
            j = 0;
        }
        // Check for operators (including multiple character operators like '++', '--', '==')
        else if (isOperator(line[i])) {
            if (line[i] == '.' && isalpha(line[i+1])) {
                // Handle dot for struct member access: split into 's' and 'id'
                printf("Identifier: %s\n", buffer);  // Print the first part (e.g., 's')
                printf("Operator: .\n");  // Print the dot
                i++; // Skip the dot
                j = 0; // Reset buffer for the second identifier
                continue;
            } else if (line[i] == '+' && line[i+1] == '+') {
                printf("Operator: ++\n");
                i += 2; // Skip '++'
            } else if (line[i] == '-' && line[i+1] == '-') {
                printf("Operator: --\n");
                i += 2; // Skip '--'
            } else if (line[i] == '=' && line[i+1] == '=') {
                printf("Operator: ==\n");
                i += 2; // Skip '=='
            } else {
                printf("Operator: %c\n", line[i]);
                i++; // Skip single operator
            }
            tokenCount++;  // Increment token count
        }
        // Check for punctuation
        else if (isPunctuation(line[i])) {
            printf("Punctuation: %c\n", line[i]);
            i++;
            tokenCount++;  // Increment token count
        }
        // Anything else is an error
        else {
            printf("Error: Invalid character '%c'\n", line[i]);
            i++;
        }
    }

    printf("\nTotal tokens: %d\n", tokenCount);  // Print total tokens
}

int main() {
    char sourceCode[MAX];
    sourceCode[0] = '\0'; // Initialize empty source code string

    printf("Enter your C code (type 'END' to finish input):\n");
    
    while (1) {
        char input[MAX];
        if (fgets(input, MAX, stdin) == NULL) {
            break;
        }

        // Check if the input is "END" to stop reading
        if (strcmp(input, "END\n") == 0) {
            break;
        }

        strcat(sourceCode, input);
    }

    // Remove comments from the source code
    removeComments(sourceCode);

    printf("\n--- TOKENS ---\n");
    tokenize(sourceCode);

    return 0;
}
