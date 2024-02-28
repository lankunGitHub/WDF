### 编程练习
8. **修改宠物俱乐部程序，把所有同名的宠物都储存在同一个节点中。当用户选择查找宠物时，程序应询问用户该宠物的名字，然后列出该名字的有宠物（及其种类）。**
```c
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 20
struct Date
{
    int typenum;
    char name[SIZE];
    char type[SIZE][SIZE];
};
typedef struct Date date;
typedef struct Node
{
    date pet;
    struct Node *left;
    struct Node *right;
};
typedef struct Node node;
struct Tree
{
    node *item;
    int num;
};
typedef struct Tree tree;
typedef struct {
    node *parent;
    node *child;
}pair;


void Init_Tree(tree *ptree);
bool Judge_Empty(tree *ptree);
bool Judge_Full(tree *ptree);
int Count_tree(tree *ptree);
bool Add_Item(date *pi,tree *ptree);
bool Find_Item(date *pi,tree *ptree);
bool Del_Item(date *pi,tree *ptree);
node* MakeNode(date *pi);
bool AddNode(node *new_node,node *root);
bool Toleft(char *name1,char *name2);
bool Toright(char *name1,char *name2);
pair Seektree(date *pi,tree *ptree);
void DeleteNode(node **pa);

node* MakeNode(date *pi)
{
    node *new_node=(node *)malloc(sizeof(node));
    if(new_node!=NULL)
    {
        new_node->pet=*pi;
        new_node->left=NULL;
        new_node->right=NULL;
    }
    return new_node;
}
bool AddNode(node *new_node,node *root)
{
    if(Toleft(&new_node->pet.name,&root->pet.name))
    {
        if(root->left==NULL)
        {
            new_node=root->left;
        }
        else
        {
            AddNode(new_node,root->left);
        }
        return 1;
    }
    else if(Toright(&new_node->pet.name,&root->pet.name))
    {
        if(root->right==NULL)
        {
            new_node=root->left;
        }
        else
        {
            AddNode(new_node,root->right);
        }
        return 1;
    }
    else
    {
        
        for(int i=0;i<root->pet.typenum;i++)
        {
            if(new_node->pet.type[0]!=root->pet.type[i])
            {
                strcpy(root->pet.type[root->pet.typenum],new_node->pet.type[0]);
                root->pet.typenum++;
                free(new_node);
                return 1;
            }
        }
        printf("Your pet is present");
        return 0;
    }
}
pair Seektree(date *pi,tree *ptree)
{
    pair look;
    look.parent=NULL;
    look.child=ptree->item;
    if(look.child==NULL)  return look;
    while(look.child!=NULL)
    {
        if(Toleft(pi->name,ptree->item->pet.name))
        {
            look.parent=look.child;
            look.child=look.child->left;
        }
        else if(Toright(pi->name,ptree->item->pet.name))
        {
            look.parent=look.child;
            look.child=look.child->right;
        }
        else{
            break;
        }
    }
    return look;
}
void DeleteNode(node **pa)
{
    node *temp;
    if((*pa)->left==NULL)
    {
        temp=*pa;
        *pa=(*pa)->right;
        free(temp);
    }
    else if((*pa)->right==NULL)
    {
        temp=*pa;
        *pa=(*pa)->left;
        free(temp);
    }
    else{
        for(temp=(*pa)->left;temp->right!=NULL;temp=temp->right)
        continue;
        temp->right=(*pa)->right;
        temp=*pa;
        *pa=(*pa)->left;
        free(temp);
    }
}
void Init_Tree(tree *ptree)
{
    ptree->item=NULL;
    ptree->num=0;
    ptree->item->pet.typenum=0;
}
bool Judge_Empty(tree *ptree)
{
    if(ptree->item=NULL)  return 1;
    else return 0;
}
bool Judge_Full(tree *ptree)
{
    if(ptree->num==SIZE)   return 1;
    else  return 0;
}
int Count_tree(tree *ptree)
{
    return ptree->num;
}
bool Add_Item(date *pi,tree *ptree)
{
    node *prev,*pcurrent;
    if(Judge_Full(ptree))
    {
        fprintf(stderr,"The tree is full");
        return 0;
    }
    if(Find_Item(pi,ptree))
    {
        fprintf(stderr,"The Item is present");
        return 0;
    }
    node *new_node=MakeNode(pi);
    if(new_node==NULL)
    {
        fprintf(stderr,"The item created failly");
        return 0;
    }
    ptree->num++;
    if(ptree->item==NULL)  ptree->item=new_node;
    else AddNode(new_node,ptree);
    return 1; 
}
bool Find_Item(date *pi,tree *ptree)
{
    return (Seektree(pi,ptree).child==NULL)?0:1;
}
bool Del_Item(date *pi,tree *ptree)
{
    pair look;
    look=(Seektree(pi,ptree));
    if(look.child==NULL)  return 0;
    if(look.parent==NULL)
    {
        DeleteNode(&ptree->item);
    }
    else if(look.parent->left==look.child)
    {
        DeleteNode(&look.parent->left);
    }
    else if(look.parent->right==look.child)
    {
        DeleteNode(&look.parent->right);
    }
    ptree->num--;
    return 1;

}
```