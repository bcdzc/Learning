#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE   1
#define FALSE  0
#define OK     1
#define ERROR  0
#define IBFEASIBLE  -1
#define OVERFLOW    -2 

typedef int Status;

typedef	struct node {
	int key;
	struct node *lChild, *rChild;
}Node, *BST;

Status InitBST(BST &t);

Status DestroyBST(BST &t);

Node* SearchBST(BST t, int key);

Status InsertBST(BST &t, Node* newNode);

Status DeleteBST(BST t, int key);

void PreOrderTraverseBST(BST t, void(*Visit) (Node* node));

void InOrderTraverseBST(BST t, void(*Visit) (Node* node));

void PostOrderTraverseBST(BST t, void(*Visit) (Node* node));