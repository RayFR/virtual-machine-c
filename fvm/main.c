#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> // Required for malloc
#include <math.h>
#include <time.h>

typedef struct Item
{
    int value;
    struct Item *next;

} Item;

Item *create_item(int value)
{
    Item *item = (Item *)malloc(sizeof(Item));

    if (item == NULL)
    {
        printf("MEMORY ALLOCATION FAILED");
        exit(1);
    }

    item->value = value;
    item->next = NULL;

    return item;
}

void link(Item *newItem, Item *root)
{
    Item *currentItem = root;
    while (currentItem->next != NULL)
    {
        currentItem = currentItem->next;
    }
    currentItem->next = newItem;
}

typedef enum // enum gives each value operator an INT equivalent
{
    PSH,
    ADD,
    POP,
    SET,
    HLT
} InstructionSet;

const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT};

int pc = 0; // program counter initialised as 0
bool live = true;

int fetch()
{
    return program[pc];
}

void eval(int instr, Item *root)
{
    switch (instr)
    {
    case HLT:
    {
        live = false;
        break;
    }
    case PSH:
    {
        Item *item = create_item(program[pc++]);
        link(item, root);
    }
    }
}

int main()
{
    int instr = program[pc]; // holds the int of the current program instruction

    Item *root = create_item(0);

    while (live)
    {
        int x = fetch();
        eval(instr, root);
        pc++;
    }

    return 0;
}
