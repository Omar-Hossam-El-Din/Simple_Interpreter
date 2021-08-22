#ifndef INFIX_H_INCLUDED
#define INFIX_H_INCLUDED
int checkOperator(char input);
char* cutTillOp(char* input);
char* AddSpaces(char* input);
int weight(char a,char b);
float calc(char o, float op1, float op2);
void infixToPostfix(char* in,char* post);
float evaluatePostfix(char* post);
void replaceNewLineBySpace(char *s);
#endif
