#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "infix.h"

int checkOperator(char input)
{
    if(input=='+'|| input=='/'|| input=='*'|| input=='^'|| input=='('|| input==')')
        return 1;
    else
        return 0;
}

char* cutTillOp(char* input)
{
    char* temp=malloc(strlen(input)+1);
    char* final=malloc(10);
    strcpy(final,"");
    strcpy(temp,input);
    char* tok = (char*)malloc(10);
    if(temp[0]=='-')
    {
        final[0]='-';
        temp++;
        tok = strtok(temp,"+-*/)(^");
        strcat(final,tok);
        return final;
    }
    else
    {
        tok = strtok(temp,"+-*/)(^");
        return tok;

    }

}

char* AddSpaces(char* input)
{
    char* output=malloc(100);
    strcpy(output,"");
    char* cursor=malloc(50);
    char* token=malloc(50);
    strcpy(cursor,input);
    char temp[30];
    int i=0;
    char check;
    while(cursor[0]!=NULL)
    {


        if(cursor[0]=='-')
        {

            if(i==0)
            {
                strcpy(temp,cutTillOp(cursor));
                strcat(output,temp);
                strcat(output," ");
                check=cursor[strlen(temp)-1];
                cursor+=strlen(temp);
                i+=strlen(temp);

            }
            else if(checkOperator(check))
            {
                strcpy(temp,cutTillOp(cursor));
                strcat(output,temp);
                strcat(output," ");
                check=cursor[strlen(temp)-1];
                cursor+=strlen(temp);
                i+=strlen(temp);
            }
            else
            {
                temp[0]=cursor[0];
                temp[1]='\0';
                strcat(output,temp);
                strcat(output," ");
                check=temp[0];
                cursor++;
                i++;
            }

        }
        else if(checkOperator(cursor[0]))
        {
            strcpy(temp,"");
            temp[0]=cursor[0];
            temp[1]='\0';
            strcat(output,temp);
            strcat(output," ");
            check=temp[0];
            cursor++;
            i++;

        }
        else
        {
            strcpy(token,cursor);
            strcpy(temp,cutTillOp(token));
            strcat(output,temp);
            strcat(output," ");
            check=cursor[strlen(temp)-1];
            cursor+=strlen(temp);
            i+=strlen(temp);

        }

    }
    return output;




}

int weight(char a,char b)
{
    if (a=='^')
    {


        if(b=='^')
            return 0;
        else
            return 1;
    }
    if (a=='*')
    {


        if(b=='*'||b=='^'||b=='/')
            return 0;
        else
            return 1;
    }
    if (a=='/')
    {


        if(b=='*'||b=='/'||b=='^')
            return 0;
        else
            return 1;
    }
    if (a=='+')
    {


        if(b=='*'||b=='/'||b=='^'||b=='+'||b=='-')
            return 0;
        else
            return 1;
    }
    if (a=='-')
    {


        if(b=='*'||b=='/'||b=='^'||b=='+'||b=='-')
            return 0;
        else
            return 1;
    }

}

float calc(char o, float op1, float op2)
{

    if (o=='*')
    {
        return (op1*op2);
    }
    else if(o=='/')
    {
        return (op1/op2);
    }
    else if(o=='+')
    {

        return op1+op2;
    }
    else if(o=='-')
    {
        return (op1-op2);
    }
    else if(o=='^')
    {
        return (pow(op1,op2));
    }

}

void infixToPostfix(char* in,char* post)
{
    Stack* s = initialize();

    char str[100]="";
    char* token;
    int len=strlen(in);
    char tok;
    char check;
    Item temp;
    token = strtok(in," ");
    while(token!=NULL)
    {
        tok=token[0];
        check=token[1];
        if(tok=='-')
        {
            if(tok=='-'&&check!='\0')
            {

                strcat(post,token);
                strcat(post," ");
            }
            else
            {
                while(!isEmpty(s) &&  s->bucket[s->top].cData!='(' && !weight(tok,s->bucket[s->top].cData ))
                {


                    str[0]=s->bucket[s->top].cData;
                    str[1]='\0';
                    strcat(post,str);
                    strcat(post," ");

                    pop(s);
                }
                temp.cData=tok;
                push(s,temp);

            }

        }
        else if(tok!='+'&&tok!='*'&&tok!='/'&&tok!='^'&&tok!='('&&tok!=')')
        {

            strcat(post,token);
            strcat(post," ");




        }


        else if(tok=='(')
        {
            temp.cData=tok;
            push(s,temp);


        }
        else if(tok==')')
        {


            while(!isEmpty(s) && s->bucket[s->top].cData!='(' )

            {
                str[0]=s->bucket[s->top].cData;
                str[1]='\0';
                strcat(post,str);
                strcat(post," ");
                pop(s);
            }

            pop(s);

        }



        else if(tok=='+'||tok=='*'||tok=='/'||tok=='^'||tok=='-')
        {


            while(!isEmpty(s) &&  s->bucket[s->top].cData!='(' && !weight(tok,s->bucket[s->top].cData) )
            {


                str[0]=s->bucket[s->top].cData;
                str[1]='\0';
                strcat(post,str);
                strcat(post," ");

                pop(s);
            }
            temp.cData=tok;
            push(s,temp);


        }



        token = strtok(NULL," ");
    }


    while(!isEmpty(s))
    {
        str[0]=s->bucket[s->top].cData;
        str[1]='\0';
        strcat(post,str);
        strcat(post," ");
        pop(s);

    }


}
float evaluatePostfix(char* post)
{
    Stack* s= initialize();
    char* token;
    char tok;
    char check;
    Item temp;
    float num;
    float result=0;
    float op1,op2;
    token = strtok(post," ");
    while(token!=NULL)
    {
        tok=token[0];
        check=token[1];
        if(tok=='-')
        {
            if(tok=='-'&&check!='\0')
            {

                num=atof(token);
                temp.fData=num;
                push(s,temp);
            }
            else
            {
                op2=s->bucket[s->top].fData;
                pop(s);
                op1=s->bucket[s->top].fData;
                pop(s);
                result=calc(tok,op1,op2);
                temp.fData= result;
                push(s,temp);




            }

        }
        else if(tok!='+'&&tok!='*'&&tok!='/'&&tok!='^'&&tok!='-')
        {

            num=atof(token);
            temp.fData=num;
            push(s,temp);

        }
        else
        {
            op2=s->bucket[s->top].fData;
            pop(s);
            op1=s->bucket[s->top].fData;
            pop(s);
            result=calc(tok,op1,op2);
            temp.fData=result;
            push(s,temp);



        }

        token = strtok(NULL," ");
    }

    return s->bucket[s->top].fData;
}
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
