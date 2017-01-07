#include "BST.h"

//初始化节点 
Status InitBST(BST &t) {
	if (NULL == t) {
		t = (Node*)malloc(sizeof(Node));
		if (NULL == t) {
			return OVERFLOW;	//内存不足 
		}
		t->lChild = t->rChild = NULL;
	}
	else
		return ERROR;	//该节点已经存在 
	return OK;	//开辟空间成功 
}

//二叉排序树销毁 
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

//返回key值的节点 
Node* SearchBST(BST t, int key) {
	Node *left;
	Node *right;
	if (t != NULL &&  t->key == key) {
		return t;
	}
	else if (t != NULL) {
		left = SearchBST(t->lChild, key);  //搜索左子树 
		if (left == NULL) {
			right = SearchBST(t->rChild, key);  //搜索右子树 
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
		return ERROR;	//key所指的结点并不存在 
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
		printf("现有的数字为：");
		PrintNum(num, n);
		printf("请选择：\n");
		printf("1.添加节点并重新构造排序树\n2.删除节点\n3.先序遍历\n4.中序遍历\n5.后序遍历\n6.搜索结点\n");
		int select;
		scanf("%d", &select);
		switch (select) {
			case 1: {
				printf("请添加key:");
				int addNum;
				scanf("%d", &addNum);
				int i;
				int flag = 0;
				for (i = 0; i < n; i++) {
					if (num[i] == addNum) {
						printf("在数组中已存在该数字\n");
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
				printf("请输入key:");
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
					printf("数组中没有这个key\n");
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
				printf("请输入key值：");
				scanf("%d", &searchKey);
				Node* node = SearchBST(T, searchKey);
				if (node != NULL) {
					printf("搜索成功！节点key值%d\n", node->key);
				}
			default:
				break;
			fflush(stdin);
		}
	}
}