#ifndef TREE_H
#define TREE_H
typedef struct
{
    char *key;
    float value;
    struct node* left;
    struct node* right;
} node;
node* root;
node* newnode(char* key,float value);
node* search(node* n,char *key);
node* insert(node* node,char* key,float value);
void put(char* key,float value);
void InOrdertraverse(node *t);
int size(node* root);
#endif
