#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

node* root=NULL;

node* newnode(char* key,float value)
{
    node* n=malloc(sizeof(node));
    n->key=malloc(strlen(key)+1);
    strcpy(n->key,key);
    n->value=value;
    n->left=NULL;
    n->right=NULL;
    return n;
}

node* search(node* n,char *key)
{
    if(n==NULL)
        return NULL;
    if(strcmp(key,n->key)==0)
        return n;
    else if(strcmp(n->key,key)>0)
        return search(n->left,key);
    else
        return search(n->right,key);
}

node* insert(node* node,char* key,float value)
{
    if(node==NULL)
        return newnode(key,value);
    if(strcmp(node->key,key)>0)
        node->left=insert(node->left,key,value);
    else if(strcmp(node->key,key)<0)
        node->right=insert(node->right,key,value);
    return node;
}

void put(char* key,float value)
{
    if(root==NULL)
    {
        root=insert(root,key,value);
    }
    else
    {
        node* node=search(root,key);
        if(node==NULL)
        {
            root=insert(root,key,value);
        }
        else
        {
            node->value=value;
        }
    }
}

void InOrdertraverse(node *t)
{
    if (t!=NULL)
    {
        InOrdertraverse(t->left);
        printf("%s = %.2f\n",t->key,t->value);
        InOrdertraverse(t->right);
    }
}

int size(node* root)
{
    if (root==NULL)
        return 0;
    else
        return 1+size(root->left)+size(root->right);
}
