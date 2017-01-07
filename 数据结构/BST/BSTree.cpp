#include "BST.h"

//��ʼ���ڵ� 
Status InitBST(BST &t) {
	if (NULL == t) {
		t = (Node*)malloc(sizeof(Node));
		if (NULL == t) {
			return OVERFLOW;	//�ڴ治�� 
		}
		t->lChild = t->rChild = NULL;
	}
	else
		return ERROR;	//�ýڵ��Ѿ����� 
	return OK;	//���ٿռ�ɹ� 
}

//�������������� 
Status DestroyBST(BST &t) {
	if (NULL == t) {
		return OK;
	}
	else {
		DestroyBST(t->lChild);
		DestroyBST(t->rChild);
		free(t);
		t = NULL;
	}
	return OK;
}

//����keyֵ�Ľڵ� 
Node* SearchBST(BST t, int key) {
	Node *left;
	Node *right;
	if (t != NULL &&  t->key == key) {
		return t;
	}
	else if (t != NULL) {
		left = SearchBST(t->lChild, key);  //���������� 
		if (left == NULL) {
			right = SearchBST(t->rChild, key);  //���������� 
			if (right != NULL)
				return right;
			else
				return NULL;
		} else {
			return left;
		}
	}
	else {
		return NULL;
	}
}

Status InsertBST(Node* &node, Node* newNode) {
	if (newNode->key == NULL) {
		return ERROR;
	}
	if (NULL == node) {
		node = newNode;
		return TRUE;
	}
	if (newNode->key == node->key) {
		return FALSE;		
	}
	if (newNode->key < node->key) {
		return InsertBST(node->lChild, newNode);
	}
	return InsertBST(node->rChild, newNode);
}


bool DeleteNode(Node* &node, Node* &father) {
	if (!node->lChild && !node->rChild) {
		if (node == father->lChild) {
			father->lChild = NULL;
		}
		else {
			father->rChild = NULL;
		}
		free(node);
	}
	else if (node->lChild && !node->rChild) {
		if (node == father->lChild) {
			father->lChild = node->lChild;
		}
		else {
			father->rChild = node->lChild;
		}
		free(node);
	}
	else if (node->rChild && !node->lChild) {
		if (node == father->lChild) {
			father->lChild = node->rChild;
		}
		else {
			father->rChild = node->rChild;
		}
		free(node);
	}
	else {
		Node* maxNodeFather = node;
		Node* maxNode = node->lChild;
		while (maxNode->rChild) {
			maxNodeFather = maxNode;
			maxNode = maxNode->rChild;
		}
		node->key = maxNode->key;
		if (maxNodeFather != node) {
			maxNodeFather->rChild = maxNode->lChild;
		}
		else {
			maxNodeFather->lChild = maxNode->lChild;
		}
		free(maxNode);	
	}
	return true;
}

Status DeleteBST(Node* node, int key) {
	Node* father;
	while (node) {
		if (node->key == key) {
			break;
		}
		father = node;
		node = (key < node->key)?node->lChild : node->rChild;
	}
	if (!node) {
		return ERROR;	//key��ָ�Ľ�㲢������ 
	}
	DeleteNode(node, father);
	return OK;
}

void Visit(Node* node) {
	printf("%d ", node->key);
}

void PreOrderTraverseBST(BST T, void(*Visit) (Node* node)) {
	if (T != NULL) {
		Visit(T);
		PreOrderTraverseBST(T->lChild, Visit);
		PreOrderTraverseBST(T->rChild, Visit);
	}
}

void InOrderTraverseBST(BST T, void(*Visit) (Node* node)) {
	if (T != NULL) {
		InOrderTraverseBST(T->lChild, Visit);
		Visit(T);
		InOrderTraverseBST(T->rChild, Visit);
	}
}

void PostOrderTraverseBST(BST T, void(*Visit) (Node* node)) {
	if (T != NULL) {
		PostOrderTraverseBST(T->lChild, Visit);
		PostOrderTraverseBST(T->rChild, Visit);
		Visit(T);
	}
}

void PrintNum(int* num, int n) {
	int i = 0;
	for (; i < n; i++) {
		printf("%d ", num[i]);
	}
	printf("\n");
}

int main() {
	int num[1000] = {15, 55, 6, 7, 25, 2, 1, 66, 94, 64};
	int n = 10;
	BST T = NULL;
	InitBST(T);
	T->key = num[0];
	int k = 1;
	for (; k < n; k++) {
		Node* node = NULL;
		InitBST(node);
		node->key = num[k];
		InsertBST(T, node);
	}
	
	while (1) {
		printf("���е�����Ϊ��");
		PrintNum(num, n);
		printf("��ѡ��\n");
		printf("1.��ӽڵ㲢���¹���������\n2.ɾ���ڵ�\n3.�������\n4.�������\n5.�������\n6.�������\n");
		int select;
		scanf("%d", &select);
		switch (select) {
			case 1: {
				printf("�����key:");
				int addNum;
				scanf("%d", &addNum);
				int i;
				int flag = 0;
				for (i = 0; i < n; i++) {
					if (num[i] == addNum) {
						printf("���������Ѵ��ڸ�����\n");
						flag = -1;
						break;
					}
				}
				if (flag == -1) {
					continue;
				}
				num[n] = addNum;
				n++;
				DestroyBST(T);
				
				InitBST(T);
				T->key = num[0];
				i = 1;
				for (; i < n; i++) {
					Node* node = NULL;
					InitBST(node);
					node->key = num[i];
					InsertBST(T, node);
				}
				break;
			}
			case 2: {
				printf("������key:");
				int delNum;
				scanf("%d", &delNum);
				int i;
				int index;
				int flag = 0;
				for (i = 0; i < n; i++) {
					if (num[i] == delNum) {
						flag = 1;
						index = i;
						break;
					}
				}
				if (flag == 0) {
					printf("������û�����key\n");
					continue;
				}
				DeleteBST(T, delNum);
				
				for (i = index; i < n - 1; i++) {
					num[i] = num[i + 1];
				}
				n--;
				 
				break;
			}
			case 3:
				PreOrderTraverseBST(T, Visit);
				printf("\n");
				break;
			case 4:
				InOrderTraverseBST(T, Visit);
				printf("\n");
				break;
			case 5:
				PostOrderTraverseBST(T, Visit);
				printf("\n");
				break;
			case 6:
				int searchKey;
				printf("������keyֵ��");
				scanf("%d", &searchKey);
				Node* node = SearchBST(T, searchKey);
				if (node != NULL) {
					printf("�����ɹ����ڵ�keyֵ%d\n", node->key);
				}
			default:
				break;
			fflush(stdin);
		}
	}
}