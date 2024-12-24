#include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

typedef struct {
    int current_state;
    char symbol;
    int next_state;
} Transition;

Transition transitions[MAX_STATES * MAX_SYMBOLS];
int num_states, num_symbols, num_transitions = 0;
char symbols[MAX_SYMBOLS];
int accept_states[MAX_STATES];
int num_accept_states;
int start_state;

int get_next_state(int current_state, char symbol) {
    for (int i = 0; i < num_transitions; i++) {
        if (transitions[i].current_state == current_state && transitions[i].symbol == symbol) {
            return transitions[i].next_state;
        }
    }
    return -1;
}

int validate_string(const char* input_string) {
    int current_state = start_state;

    for (int i = 0; i < strlen(input_string); i++) {
        char symbol = input_string[i];
        int next_state = get_next_state(current_state, symbol);
        
        if (next_state == -1) {
            return 0;
        }
        current_state = next_state;
    }

    for (int i = 0; i < num_accept_states; i++) {
        if (current_state == accept_states[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    printf("Number of input symbols: ");
    scanf("%d", &num_symbols);
    
    printf("Input symbols (space separated): ");
    for (int i = 0; i < num_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter number of states: ");
    scanf("%d", &num_states);

    printf("Initial state: ");
    scanf("%d", &start_state);

    printf("Number of accepting states: ");
    scanf("%d", &num_accept_states);
    
    printf("Accepting states (space separated): ");
    for (int i = 0; i < num_accept_states; i++) {
        scanf("%d", &accept_states[i]);
    }

    printf("Enter transitions in format: current_state symbol next_state\n");
    printf("Type -1 to stop.\n");

    while (1) {
        int current, next;
        char symbol;
        
        scanf("%d", &current);
        if (current == -1) break;
        
        scanf(" %c %d", &symbol, &next);
        
        transitions[num_transitions].current_state = current;
        transitions[num_transitions].symbol = symbol;
        transitions[num_transitions].next_state = next;
        num_transitions++;
    }

    char input_string[100];
    while (1) {
        printf("Input string (or type 'exit' to stop): ");
        scanf("%s", input_string);
        
        if (strcmp(input_string, "exit") == 0) {
            break;
        }

        if (validate_string(input_string)) {
            printf("Valid String\n");
        } else {
            printf("Invalid String\n");
        }
    }
    
    return 0;
}
