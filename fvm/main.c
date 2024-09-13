#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Required for malloc

typedef struct Item // STRUCT WITH TWO VALUES (INT AND POINTER STRUCT)
{
    int value;
    struct Item *next;
} Item;

Item *create_item(int value)
{
    Item *newItem = (Item *)malloc(sizeof(Item));

    if (newItem == NULL)
    {
        printf("Memory allocation failed.");
    }

    newItem->value = value;
    newItem->next = NULL;

    return newItem;
}

void push(Item *root, int value)
{
    Item *newItem = create_item(value);
    Item *currentItem = root;

    while (currentItem->next != NULL)
    {
        currentItem = currentItem->next;
    }
    currentItem->next = newItem;
}

int pop(Item *root)
{
    if (root->next == NULL) // If there's only the root item or no items
    {
        printf("Cannot pop from an empty stack.\n");
        return -1; // Return an error value
    }

    Item *currentItem = root;
    Item *previousItem = NULL;

    // Traverse to the last item
    while (currentItem->next != NULL)
    {
        previousItem = currentItem;
        currentItem = currentItem->next;
    }

    int temp = currentItem->value;

    if (previousItem != NULL)
    {
        previousItem->next = NULL; // Set the second-to-last item's next to NULL
    }
    
    printf("Popped %d.", temp);

    free(currentItem); // Free the memory of the last item

    return temp;
}

void display(Item *root)
{
    Item *currentItem = root;
    int count = 0;
    while (currentItem->next != NULL)
    {
        count++;
        currentItem = currentItem->next;
        printf("\n%d: %d", count, currentItem->value);
    }
    printf("END");
}

typedef enum // ENUM SETS THE INSRUCTION SET
{
    PSH, // ENUM INIT ON BASE 0
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

typedef enum 
{
    A, B, C, D, E, F, PC, 
    NUM_OF_REGISTERS // last element will accuratelly count registers on base 0
} Registers;

const int program[] = { // MAIN PROGRAM
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT}; // HLT USED TO STOP THE PROGRAM

int pc = 0; // Program counter initialized as 0
bool live = true;

// Function to fetch the current instruction
int fetch()
{
    return program[pc];
}

void eval(int instr, Item *root) // EVALUATE FUNCTION HOLDS A SWITCH OF THE BASIC COMMAND FUNCTIONALITIES
{
    switch (instr) // braces around the switch cases allows for the cases to have a scope to assigne vars etc
    {
    case HLT: // Halt the program
        live = false;
        printf("HALTPROGRAM");
        break;

    case PSH: // Push the next value onto the stack
    {
        // Increment pc to get the next value from the program
        int value = program[++pc];
        push(root, value);
        printf("Pushed %d to the stack.", value);
        break;
    }

    case POP: // Pop the last item from the stack
    {
        pop(root);
        printf("POP instruction executed.\n");
        break;
    }

    case ADD:
    {
        int tempA = pop(root);
        int tempB = pop(root);
        int result = tempA + tempB;
        printf("Successfully added.");
        push(root, result);
        break;
    }

    default:
        printf("Unknown instruction: %d\n", instr);
        live = false;
        break;
    }
}

int main()
{
    Item *root = create_item(0);

    // main loop

    while (live)
    {
        int instr = fetch(); // fetch the current instruction
        eval(instr, root);   // evaluate the current instruction pc++;
        pc++;                // move to the next instruction
    }

    display(root);

    // MEMORY CLEANUP LOOPS THROUGH LINKED LIST AND FREES THE ALLOCATED MEMORY UNTIL THE LIST IS COMPLETELY SEARCHED THROUGH
    Item *current = root;
    while (current != NULL)
    {
        Item *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
