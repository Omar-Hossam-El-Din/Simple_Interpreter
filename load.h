#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED
#include "tree.h"
#include "heap.h"
int check(char* equation);
char*  remove_spaces(char* str);
void interpretFile(char* filename);
int checkfirstequation(char* input);
char *replaceVariable(char *input,char *oldW,char *newW);
char* swapvariables(char* rightside);
int AddToArray(node* root, variable arr[], int i);
#endif
