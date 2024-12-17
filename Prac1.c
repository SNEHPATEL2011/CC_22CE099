#include <stdio.h>
#include <string.h>

int isValidString(const char *str) {
    int count = 0;
    while (str[count] == 'a') {
        count++;
    }
    if (str[count] == 'b' && str[count + 1] == 'b' && str[count + 2] == '\0') {
        return 1;
    }
    return 0;
}

int main() {
    char input[100];
    printf("Enter a string: ");
    scanf("%s", input);
    if (isValidString(input)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }
    return 0;
}
