#include<stdio.h>
#include<stdlib.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
	int height;
};

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int height(struct Node* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + max(height(root->left), height(root->right));
}

struct Node* newNode(int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->height = 0;
	return newNode;
}

struct Node* rightRotate(struct Node* y)
{
	struct Node* x = y->left;
	struct Node* T2 = x->right;
	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

struct Node* leftRotate(struct Node* x)
{
	struct Node* y = x->right;
	struct Node* T2 = y->left;
	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int getBalance(struct Node* root)
{
	if (root == NULL)
		return 0;
	else
		return height(root->left) - height(root->right);
}

struct Node* insert(struct Node* root, int data)
{
	if (root == NULL)
		return newNode(data);

	if (data < root->data)
		root->left = insert(root->left, data);
	else if (data > root->data)
		root->right = insert(root->right, data);
	else
		return root;

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	if (balance > 1 && data < root->left->data)
		return rightRotate(root);

	if (balance < -1 && data > root->right->data)
		return leftRotate(root);

	if (balance > 1 && data > root->left->data)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && data < root->right->data)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void preorder(struct Node* root)
{
	if (root == NULL)
		return;

	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);

	return;
}

int main()
{
	struct Node* root = NULL;
	printf("1. Insert  2. Preorder  3. Exit\n");

	while (1)
	{
		int ch;
		printf("Command: ");
		scanf("%d", &ch);

		if(ch == 1)
		{
			int data;
			scanf("%d", &data);
			root = insert(root, data);
		}
		else if (ch == 2)
		{
			preorder(root);
			printf("\n");
		}
		else if (ch == 3)
			break;
	}
}