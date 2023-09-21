#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
}Node;

Node* Insert(Node* node, int data)
{
    if (node == NULL)
    {
        Node* newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }
    else
    {
        if(node->data > data)
        {
            node->left = Insert(node->left, data)
        }
        else if
    }
}