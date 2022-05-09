#include <stdio.h>
#include <stdlib.h>

typedef struct node { //node ����ü ����
	int key; //key���� �Է� ���� ���� ����
	struct node *left; //����ü ������ ���� ���� ->���� ���
	struct node *right; //����ü ������ ���� ���� -> ���� ���
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //char�� command ���� ����
	int key; //int�� key ���� ����
	Node* head = NULL; //����ü ������ ���� ����
	Node* ptr = NULL;	/* temp */

	do{
        printf("\n\n");
		printf("[----- [���ؿ�] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command�� �Է� �޴´�

		switch(command) {
		case 'z': case 'Z': //z�� �Է� �޴� ���
			initializeBST(&head);//initailizeBST �Լ� ����
			break;
		case 'q': case 'Q'://q�� �Է� �޴� ���
			freeBST(head);//freeBST �Լ� ����
			break;
		case 'n': case 'N': // n�� �Է� �޴� �ܿ�
			printf("Your Key = ");
			scanf("%d", &key);//key�� �Է�
			insert(head, key);//insert �Լ� ����
			break;
		case 'd': case 'D'://d�� �Է� �޴� ���
			printf("Your Key = ");
			scanf("%d", &key);//key�� �Է�
			deleteLeafNode(head, key);//deleteLeafNode �Լ� ����
			break;
		case 'f': case 'F'://f�� �Է� �޴� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� �޴´�
			ptr = searchIterative(head, key);//searchIterative �Լ� ���� �� ptr�� return �� ����
			if(ptr != NULL) 
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� ���� �����ϴ� ��� ���
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr�� ���������ʴ� ���
			break;
		case 's': case 'S'://s�� �Է� �޴� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է�
			ptr = searchRecursive(head->left, key); //searchRecursive �Լ� ���� �� return �� ����
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr�� ���� �����ϴ� ��� ���
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr�� ���������ʴ� ���
			break;

		case 'i': case 'I'://i�� �Է� �޴� ���
			inorderTraversal(head->left); //inorderTraversal �Լ� ����
			break;
		case 'p': case 'P'://p�� �Է� �޴� ���
			preorderTraversal(head->left); //preorderTraversal �Լ� ����
			break;
		case 't': case 'T'://t�� �Է� �޴� ���
			postorderTraversal(head->left); //postorderTraversal �Լ� ����
			break;
		default://�ٸ� command�� �Է� ������ ��� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q�� �Է� �ޱ� ������ �ݺ��� ����

	return 1;
}

int initializeBST(Node** h) { //��带 �����Ҵ� ���ִ� �Լ�

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //*h�� NULL�� �ƴ� ��� �޸� ����
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //*h�� �����Ҵ�
	(*h)->left = NULL;	/* root */ //h����� left�� NULL�� �ʱ�ȭ
	(*h)->right = *h; // h����� right�� *h�� ����Ű�� �Ѵ�
	(*h)->key = -9999; //h����� key�� �ʱ�ȭ
	return 1;
}



void inorderTraversal(Node* ptr) //���� ��ȸ Ʈ��
{
	if(ptr) { //leftchild�� ���� ���� ��� -> �Ѹ� -> ������ ��� ������ ���
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr) // ���� ��ȸ Ʈ��
{
	if(ptr) {  //�Ѹ� -> ���� ��� -> ������ ��� ������ ���
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr) //���� ��ȸ Ʈ��
{
	if(ptr) { //���� ��� -> ������ ��� -> �Ѹ� ������ ���
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key) //��带 �߰��ϴ� �Լ� 
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //����ü ������ ���� �����Ҵ�
	newNode->key = key; // key�� �Է�
	newNode->left = NULL;//Null�� �ʱ�ȭ
	newNode->right = NULL;//Null�� �ʱ�ȭ

	if (head->left == NULL) { //����� ���� �������� �ʴ� ���
		head->left = newNode; //�Է¹��� key���� ���� ��带 �Ѹ� ���� ����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr�� �Ѹ����� ����

	Node* parentNode = NULL;//�θ��� ����
	while(ptr != NULL) {//ptr�� NULL�� ������ �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //�Է¹��� key���̶� ���� ��� ���� ���ش�

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;//�θ��忡 ptr ����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr�� key���� �Է¹��� key������ ���� ���
			ptr = ptr->right;//ptr�� ptr->right ����
		else //ptr�� key���� �Է¹��� key������ ū ���
			ptr = ptr->left;//ptr�� ptr -> left ����
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //�θ����� key���� �Է¹��� key������ ū ���
		parentNode->left = newNode; //�θ����� left�� ��� �Է�
	else//���� ���
		parentNode->right = newNode;//right�� ��� �Է�
	return 1;
}

int deleteLeafNode(Node* head, int key)//������带 �����ϴ� �Լ�
{
	if (head == NULL) { //���� �������� �ʴ� ��� �޼��� ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //���� �������� �ʴ� ��� �޼��� ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr�� ��Ʈ ��� ����


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;//����带 �θ���� ����

	while(ptr != NULL) { //ptr�� NULL�� �� ������ �ݺ��� ����

		if(ptr->key == key) { //ptr�� key���� �Է¹��� key���� ���� ���
			if(ptr->left == NULL && ptr->right == NULL) { //�¿��� ��尡 ���� ���

				/* root node case */
				if(parentNode == head) //�θ��尡 ������� ���
					head->left = NULL; //������� ���� ��带 NULL�� �ʱ�ȭ

				/* left node case or right case*/
				if(parentNode->left == ptr) //�θ����� ���� ��尡 ptr�� ���
					parentNode->left = NULL;//NULL�� �ʱ�ȭ�ؼ� ����
				else//������ ���
					parentNode->right = NULL;//NULL�� �ʱ�ȭ�ؼ� ����

				free(ptr);//�޸�����
			}
			else {//������尡 �ƴѰ�� 
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //�θ��忡 ptr����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr key���� �Է¹��� key������ ���� ���
			ptr = ptr->right; //�������� �̵�
		else//ū ���
			ptr = ptr->left;//�������� �̵�


	}

	printf("Cannot find the node for key [%d]\n ", key); //��ġ�ϴ°� ���� ���

	return 1;
}

Node* searchRecursive(Node* ptr, int key) //��ȯ�� ���
{
	if(ptr == NULL) //��尡 �������� �ʴ� ���
		return NULL; //NULL ����

	if(ptr->key < key) //ptr�� key���� �Է¹��� key������ ���� ���
		ptr = searchRecursive(ptr->right, key);//���� ���� �̵�
	else if(ptr->key > key)//ū ���
		ptr = searchRecursive(ptr->left, key);//���� ���� �̵�

	/* if ptr->key == key */
	return ptr; //key���� ��ġ�ϴ� ��� ����

}
Node* searchIterative(Node* head, int key)//�ݺ��� ���
{
	/* root node */
	Node* ptr = head->left; //ptr�� ��Ʈ��� ����

	while(ptr != NULL) //ptr�� NULL�� �� ������ �ݺ��� ����
	{
		if(ptr->key == key) //ptr key���� �Է¹��� key���� ���� ���
			return ptr; //ptr ����

		if(ptr->key < key) ptr = ptr->right; //ptr�� key�� ���� ��� -> ���� ���� �̵�
		else //ū ���
			ptr = ptr->left; //���� ���� �̵�
	}

	return NULL;
}

void freeNode(Node* ptr) //��带 �޸� �����ϴ� �Լ�
{
	if(ptr) { //ptr�� ���� ���� �ϴ� ��� 
		freeNode(ptr->left); //ptr�� ���� ��带 �޸� ����
		freeNode(ptr->right);//ptr�� ���� ��带 �޸� ����
		free(ptr);//ptr �޸� ����
	}
}

int freeBST(Node* head) //����Ž��Ʈ�� �޸�����
{

	if(head->left == head) //��Ʈ��尡 ������� ���
	{
		free(head);//����� �޸� ����
		return 1;
	}

	Node* p = head->left; //p�� ��Ʈ��� ����

	freeNode(p);//��Ʈ��� �޸� ����

	free(head);//����� �޸� ����
	return 1;
}





