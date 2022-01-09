#include <stdio.h>
#include<stdlib.h>
#define MARKER -1
typedef struct node
{

    int key;
    struct node *left,*right;
}Node;
Node* newNode(int key)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->left = temp->right = NULL;
    return(temp);
}
void serialize(Node *root, FILE *fp)
{
    if (root == NULL)
    {
        fprintf(fp, "%d ", MARKER);
        return;
    }
    serialize(root->left,fp);
    fprintf(fp, "%d ", root->key);
    serialize(root->right, fp);
}
void deSerialize(Node *root, FILE *fp)
{
    int val;
    if ( !fscanf(fp, "%d ", &val) || val == MARKER)
       return;
    root = newNode(val);
    deSerialize(root->left, fp);
    deSerialize(root->right, fp);
}
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
int main()
{

    Node *root    =newNode(20);
    root->left    =newNode(8);
    root->right   =newNode(22);
    root->left->left        =newNode(4);
    root->left->right       =newNode(12);
    root->left->right->left =newNode(10);
    root->left->right->right=newNode(14);
    FILE *fp = fopen("tree.txt", "w");
    if (fp == NULL)
    {
        puts("Could not open file");
        return 0;
    }
    serialize(root, fp);
    fclose(fp);
    struct node *root1 = NULL;
    fp = fopen("tree.txt", "r");
    deSerialize(root1, fp);
    printf("Inorder Traversal of the tree constructed from file:\n");
    inorder(root1);
    return 0;
}