#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int id;
    struct Node *next;
    struct Node *prev;
    int isDup;
} Node;

typedef struct Stack {
    Node *top;
} Stack;
//====================================================================================================================
void push(Stack *stack, int id) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->id = id;
    new_node->isDup = 0;
    new_node->next = stack->top;
    new_node->prev = NULL;
    if (stack->top != NULL) {
        stack->top->prev = new_node;
    }
    stack->top = new_node;
}
//====================================================================================================================
int main() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->top = NULL;
    //vars
    int input, dist = 1, finalDist = 0, rooms = 0;
    //while take in rooms
    while (1) {
        scanf(" %d", &input);
        if (input == -1) {
            break;
        }
        push(stack, input);
    }
    
    //check if room is sleepable
    Node *current = stack->top;
    while (current != NULL) {
        Node *check = stack->top;
        while (check != NULL) {
            if (check != current && check->id == current->id) {
                current->isDup = 1;
                break;
            }
            check = check->next;
        }
        current = current->next;
    }
    //add room to rooms
    current = stack->top;
    while (current != NULL) {
        if (current->isDup == 0) {
            rooms++;
        }
        current = current->next;
    }

    current = stack->top;
    if (current != NULL) {
        dist = 1;
    }
    //find corridors
    while (current != NULL) {
        if (current->id == stack->top->id) {
            dist = 1;
            current = current->next;
        } else if (current->isDup == 1 && current->prev != NULL && current->next != NULL && current->prev->id != current->next->id) {
            dist++;
            current = current->next;
        } else if (current->isDup == 1 && current->prev != NULL && current->next != NULL && current->prev->id == current->next->id) {
            dist--;
            current = current->next;
        } else if (current->isDup == 0 && current->prev != NULL && current->next != NULL && current->prev->id == current->next->id) {
            finalDist += dist;
            current = current->next;
            dist--; 
        }else if (current->isDup == 0) {
            finalDist += dist;
            current = current->next;
        }
    }
    //print
    printf("%d %d\n", rooms, finalDist);

    // Free allocated memory
    current = stack->top;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);

    return 0;
}
//====================================================================================================================