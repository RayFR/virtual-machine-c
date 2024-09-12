#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Required for malloc

typedef struct Item // STRUCT WITH TWO VALUES (INT AND POINTER STRUCT)
{
    int value;
    struct Item *next;
} Item;

Item *create_item(int value) // CREATES A NEW STRUCT ITEM
{
    Item *item = (Item *)malloc(sizeof(Item));

    if (item == NULL)
    {
        printf("MEMORY ALLOCATION FAILED\n");
        exit(1);
    }

    item->value = value;
    item->next = NULL;

    return item;
}

void link(Item *newItem, Item *root) // LINKS NEW ITEM TO END OF LINKED LIST -- TAKES THE NEWITEM AND THE ROOT ITEM AS PARAMETERS
{
    Item *currentItem = root;
    while (currentItem->next != NULL)
    {
        currentItem = currentItem->next;
    }
    currentItem->next = newItem;
}

typedef enum // ENUM SETS THE INSRUCTION SET
{
    PSH, // ENUM INIT ON BASE 0
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

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
    switch (instr)
    {
    case HLT: // Halt the program
        live = false;
        break;

    case PSH: // Push the next value onto the stack
    {
        // Increment pc to get the next value from the program
        int value = program[++pc];
        Item *item = create_item(value);
        link(item, root);
        break;
    }

    case ADD: // Add the last two values
    {
        printf("ADD instruction executed.\n");
        break;
    }

    case POP: // Pop the last item from the stack
    {
        printf("POP instruction executed.\n");
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
        eval(instr, root);   // evaluate the current instruction
        pc++;                // move to the next instruction
    }

    // MEMORY CLEANUP LOOPS THROUGH LINKED LIST AND FREES THE ALLOCATED MEMORY UNTIL THE LIST IS COMPLETELY SEARCHED THROUGH
    Item *current = root; // CURRENT INIT
    while (current != NULL)
    {
        Item *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
