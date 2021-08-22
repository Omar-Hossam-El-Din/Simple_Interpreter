#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef union
{
    float fData;
    char  cData;
} Item;
typedef struct
{
    Item bucket[100];

    int top;

} Stack;
Item top (Stack *s);
int isEmpty(Stack* s);
int isFull(Stack* s);
Stack* initialize();
void push(Stack* s,Item a);
Item pop (Stack* s);
#endif
