#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infix.h"
#include "load.h"
#include "tree.h"
#include "heap.h"

char* getVar(char* equation)
{
    char* name;
    name=strtok(equation,"=");
    // returns variable name
    return name;
}
char* remove_spaces(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] !=' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}
int check(char* equation)
{


    int flag1=0,flag2=0,flag3=1,flag4=1,i;
    char* eqcopy;
    char* token;

    //first check if there are any invalid symbols

    for(i=0; i<strlen(equation); i++)
    {
        if(equation[i]=='+'|| equation[i]=='=' || equation[i]==' ' || equation[i]=='-' || equation[i]=='/'|| equation[i]=='*'|| equation[i]=='^'|| equation[i]=='('|| equation[i]==')' || equation[i]=='.' || isalpha(equation[i]) || isdigit(equation[i]))
        {
            flag1=1;

        }
        else
        {
            flag1=0;
            printf("Unknown Symbol Found: %c\n",equation[i]);
            break;
        }


    }



//    then check if = is missing in the expression

    for(i=0; i<strlen(equation); i++)
    {
        if(equation[i]=='=')
        {
            flag2=1;
            break;
        }

    }
    if(flag2==0)
    {

        printf("Equal Sign doesn't exist\n");

    }



    //then check for unclosed parenthesis

    for(i=0; i<strlen(equation); i++)
    {
        if(equation[i]=='(')
            flag3=0;
        if(equation[i]==')')
            flag3=1;

    }
    if(flag3==0)
        printf("Unclosed Parenthesis\n");


    //lastly check if left hand side has more than 1 variable

    eqcopy=malloc(strlen(equation+1));
    strcpy(eqcopy,equation);
    token=strtok(eqcopy,"=");
    for(i=0; i<strlen(token); i++)
    {
        if(token[i]=='+'|| token[i]=='-' || token[i]=='/'|| token[i]=='*'|| token[i]=='^'|| token[i]=='('|| token[i]==')' || token[i]=='.')
        {
            flag4=0;
            printf("More than 1 variable found in left hand side\n");
            break;
        }
        else
            flag4=1;
    }

    free(eqcopy);

    return flag1&&flag2&&flag3&&flag4;


}
int checkfirstequation(char* input)
{
    int i;
    for(i=0; i<strlen(input); i++)
    {
        if(isalpha(input[i]))
            return 0;
    }
    return 1;
}
char* replaceVariable(char *input,char *oldW,char *newW)
{
    char *result;
    int i, counter = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    /*    Counting the number of times old word
        occur in the string */

    for (i = 0; input[i] != '\0'; i++)
    {
        if (strstr(&input[i], oldW) == &input[i])
        {
            counter++;

            //Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    //Making new string of enough length
    result = (char *)malloc(i + counter * (newWlen - oldWlen) + 1);

    i = 0;
    while (*input)
    {
        //compare the substring with the result
        if (strstr(input, oldW) == input)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            input += oldWlen;
        }
        else
            result[i++] = *input++;
    }

    result[i] = '\0';
    return result;
}

char* swapvariables(char* rightside)
{
    node* treevar;
    char valuestr[10];
    char* copyrs=malloc(strlen(rightside)+1);
    strcpy(copyrs,rightside);
    char* var = strtok(rightside,"+-^/*) ");



    while(var!=NULL)
    {

        if(isalpha(var[0]))
        {
            treevar=search(root,var);

            if(treevar==NULL)
            {
                printf("Undefined Variables found\n");
                exit(0);

            }
            else
            {

                char*f=gcvt(treevar->value,4,valuestr);
                strcpy(copyrs,replaceVariable(copyrs,treevar->key,valuestr));


            }
            var=strtok(NULL,"+-^/*) ");

        }
        else if (isalpha(var[1]))
        {

            treevar=search(root,var+1);
            if(treevar==NULL)
            {
                printf("Undefined Variables found\n");
                exit(0);

            }
            else
            {
                char* b=gcvt(treevar->value,4,valuestr);
                strcpy(copyrs,replaceVariable(copyrs,treevar->key,valuestr));

            }
            var=strtok(NULL,"+-^/*) ");


        }
        else
        {

            var = strtok(NULL,"+-^/*) ");

        }

    }
    return copyrs;

}

int AddToArray(node* root, variable arr[], int i)
{
    if(root == NULL)
        return i;

    variable v1;
    v1.name = malloc(strlen(root->key)+1);
    strcpy(v1.name,root->key);
    v1.value=root->value;
    arr[i] = v1;
    i++;
    if(root->left != NULL)
        i = AddToArray(root->left, arr, i);
    if(root->right != NULL)
        i = AddToArray(root->right, arr, i);

    return i;
}
void interpretFile(char* filename)
{
    FILE* file;
    file=fopen(filename,"r");
    if (file==NULL)
    {
        printf("File Doesn't Exist\n");
        exit(1);
    }
    char equation[500];
    int i;
    char* token;
    char* variable_name;
    char* rightside=malloc(50);
    char postfix[100]="";
    float result=0;
    int counter=0;
    variable v1;
    while(fgets(equation,500 ,file))
    {
        replaceNewLineBySpace(equation);
        char* new_equation=remove_spaces(equation);
        counter++;

        //checks if first equation is equal to constant
        if(counter==1)
        {
            if(check(new_equation))
            {

                token=strtok(new_equation,"=");
                strcpy(variable_name,token);
                token=strtok(NULL,"\0");
                strcpy(rightside,token);
                int flag=checkfirstequation(rightside);
                if(flag==0)
                {
                    printf("Undefined Variables found\n");
                    exit(0);
                }
                else
                {
                    result = atof(rightside);
                    put(variable_name,result);

                }

            }
            else
            {
                printf("Invalid Expression\n");
                exit(0);
            }


        }


        // checks input for invalid expressions and terminates if so

        else if(check(new_equation))
        {

            // put variable name and result
            token=strtok(new_equation,"=");
            strcpy(variable_name,token);
            token=strtok(NULL," ");
            strcpy(rightside,token);
            strcpy(rightside,swapvariables(rightside));
            strcpy(rightside,AddSpaces(rightside));
            infixToPostfix(rightside,postfix);
            result=evaluatePostfix(postfix);
            put(variable_name,result);
            strcpy(postfix,"");
        }
        else
        {
            printf("Invalid Expression\n");
            exit(0);
        }

    }
    int heap_size=size(root);
    variable heap[heap_size];
    AddToArray(root,heap,0);
    printf("\t\t\t\t\t <<<<<< Interpreter >>>>>>\n");
    printf("\nSort According to Variable Names using BST\n\n");
    InOrdertraverse(root);
    printf("\n------------------------------------------\n");
    BuildHeap(heap,heap_size);
    SortHeap(heap,heap_size);
    print(heap,heap_size);
    printf("\n------------------------------------------\n");


}
