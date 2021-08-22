#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Item top (Stack *s)
{
    return s->bucket[s->top];
}
int isEmpty(Stack* s)
{
    if  (s->top==-1)
        return 1;
    else
        return 0;

}

int isFull(Stack* s)
{
    if  (s->top==100-1)
        return 1;
    else
        return 0;

}

Stack* initialize()
{


    Stack* s = malloc(sizeof(Stack));
    s->top=-1;
    return s;
}


void push(Stack* s,Item a)
{
    s->top++;
    s->bucket[s->top]=a;


}

Item pop (Stack* s)
{
    s->top--;
    return s->bucket[s->top+1];

}

