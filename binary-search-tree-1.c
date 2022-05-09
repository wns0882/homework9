#include <stdio.h>
#include <stdlib.h>

typedef struct node { //node 구조체 정의
	int key; //key값을 입력 받을 변수 선언
	struct node *left; //구조체 포인터 변수 선언 ->좌측 노드
	struct node *right; //구조체 포인터 변수 선언 -> 우측 노드
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
	char command; //char형 command 변수 정의
	int key; //int형 key 변수 정의
	Node* head = NULL; //구조체 포인터 변수 정의
	Node* ptr = NULL;	/* temp */

	do{
        printf("\n\n");
		printf("[----- [박준용] [2019038010] -----]");
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
		scanf(" %c", &command);//command를 입력 받는다

		switch(command) {
		case 'z': case 'Z': //z를 입력 받는 경우
			initializeBST(&head);//initailizeBST 함수 실행
			break;
		case 'q': case 'Q'://q를 입력 받는 경우
			freeBST(head);//freeBST 함수 실행
			break;
		case 'n': case 'N': // n을 입력 받는 겨우
			printf("Your Key = ");
			scanf("%d", &key);//key값 입력
			insert(head, key);//insert 함수 실행
			break;
		case 'd': case 'D'://d를 입력 받는 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값 입력
			deleteLeafNode(head, key);//deleteLeafNode 함수 실행
			break;
		case 'f': case 'F'://f를 입력 받는 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 받는다
			ptr = searchIterative(head, key);//searchIterative 함수 실행 후 ptr에 return 값 대입
			if(ptr != NULL) 
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 값이 존재하는 경우 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr이 존재하지않는 경우
			break;
		case 's': case 'S'://s를 입력 받는 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력
			ptr = searchRecursive(head->left, key); //searchRecursive 함수 실행 후 return 값 대입
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //ptr의 값이 존재하는 경우 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //ptr이 존재하지않는 경우
			break;

		case 'i': case 'I'://i를 입력 받는 경우
			inorderTraversal(head->left); //inorderTraversal 함수 실행
			break;
		case 'p': case 'P'://p를 입력 받는 경우
			preorderTraversal(head->left); //preorderTraversal 함수 실행
			break;
		case 't': case 'T'://t를 입력 받는 경우
			postorderTraversal(head->left); //postorderTraversal 함수 실행
			break;
		default://다른 command를 입력 받으면 경고 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q를 입력 받기 전까지 반복문 실행

	return 1;
}

int initializeBST(Node** h) { //노드를 동적할당 해주는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //*h가 NULL이 아닌 경우 메모리 해제
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //*h를 동적할당
	(*h)->left = NULL;	/* root */ //h노드의 left를 NULL로 초기화
	(*h)->right = *h; // h노드의 right에 *h를 가리키게 한다
	(*h)->key = -9999; //h노드의 key값 초기화
	return 1;
}



void inorderTraversal(Node* ptr) //중위 순회 트리
{
	if(ptr) { //leftchild로 가서 왼쪽 노드 -> 뿌리 -> 오른쪽 노드 순으로 출력
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr) // 전위 순회 트리
{
	if(ptr) {  //뿌리 -> 왼쪽 노드 -> 오른쪽 노드 순으로 출력
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr) //후위 순회 트리
{
	if(ptr) { //왼쪽 노드 -> 오른쪽 노드 -> 뿌리 순으로 출력
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key) //노드를 추가하는 함수 
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //구조체 포인터 변수 동적할당
	newNode->key = key; // key값 입력
	newNode->left = NULL;//Null로 초기화
	newNode->right = NULL;//Null로 초기화

	if (head->left == NULL) { //노드의 값이 존재하지 않는 경우
		head->left = newNode; //입력받은 key값에 대한 노드를 뿌리 노드로 지정
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr을 뿌리노드로 지정

	Node* parentNode = NULL;//부모노드 생성
	while(ptr != NULL) {//ptr이 NULL일 때까지 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //입력받은 key값이랑 같은 경우 리턴 해준다

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;//부모노드에 ptr 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key값이 입력받은 key값보다 작은 경우
			ptr = ptr->right;//ptr에 ptr->right 대입
		else //ptr의 key값이 입력받은 key값보다 큰 경우
			ptr = ptr->left;//ptr에 ptr -> left 대입
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //부모노드의 key값이 입력받은 key값보다 큰 경우
		parentNode->left = newNode; //부모노드의 left에 노드 입력
	else//작은 경우
		parentNode->right = newNode;//right에 노드 입력
	return 1;
}

int deleteLeafNode(Node* head, int key)//리프노드를 삭제하는 함수
{
	if (head == NULL) { //값이 존재하지 않는 경우 메세지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //값이 존재하지 않는 경우 메세지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr에 루트 노드 대입


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;//헤드노드를 부모노드로 지정

	while(ptr != NULL) { //ptr이 NULL이 될 때까지 반복문 실행

		if(ptr->key == key) { //ptr의 key값이 입력받은 key값과 같은 경우
			if(ptr->left == NULL && ptr->right == NULL) { //좌우측 노드가 없는 경우

				/* root node case */
				if(parentNode == head) //부모노드가 헤드노드인 경우
					head->left = NULL; //헤드노드의 좌측 노드를 NULL로 초기화

				/* left node case or right case*/
				if(parentNode->left == ptr) //부모노드의 좌측 노드가 ptr인 경우
					parentNode->left = NULL;//NULL로 초기화해서 삭제
				else//우측인 경우
					parentNode->right = NULL;//NULL로 초기화해서 삭제

				free(ptr);//메모리해제
			}
			else {//리프노드가 아닌경우 
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //부모노드에 ptr대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr key값이 입력받은 key값보다 작은 경우
			ptr = ptr->right; //우측으로 이동
		else//큰 경우
			ptr = ptr->left;//좌측으로 이동


	}

	printf("Cannot find the node for key [%d]\n ", key); //일치하는게 없는 경우

	return 1;
}

Node* searchRecursive(Node* ptr, int key) //순환법 방식
{
	if(ptr == NULL) //노드가 존재하지 않는 경우
		return NULL; //NULL 리턴

	if(ptr->key < key) //ptr의 key값이 입력받은 key값보다 작은 경우
		ptr = searchRecursive(ptr->right, key);//우측 노드로 이동
	else if(ptr->key > key)//큰 경우
		ptr = searchRecursive(ptr->left, key);//좌측 노드로 이동

	/* if ptr->key == key */
	return ptr; //key값이 일치하는 경우 리턴

}
Node* searchIterative(Node* head, int key)//반복법 방식
{
	/* root node */
	Node* ptr = head->left; //ptr에 루트노드 대입

	while(ptr != NULL) //ptr이 NULL이 될 때까지 반복문 실행
	{
		if(ptr->key == key) //ptr key값과 입력받은 key값이 같은 경우
			return ptr; //ptr 리턴

		if(ptr->key < key) ptr = ptr->right; //ptr의 key이 작은 경우 -> 우측 노드로 이동
		else //큰 경우
			ptr = ptr->left; //좌측 노드로 이동
	}

	return NULL;
}

void freeNode(Node* ptr) //노드를 메모리 해제하는 함수
{
	if(ptr) { //ptr에 값이 존재 하는 경우 
		freeNode(ptr->left); //ptr의 좌측 노드를 메모리 해제
		freeNode(ptr->right);//ptr의 우측 노드를 메모리 해제
		free(ptr);//ptr 메모리 해제
	}
}

int freeBST(Node* head) //이진탐색트리 메모리해제
{

	if(head->left == head) //루트노드가 헤드노드인 경우
	{
		free(head);//헤드노드 메모리 해제
		return 1;
	}

	Node* p = head->left; //p에 루트노드 대입

	freeNode(p);//루트노드 메모리 해제

	free(head);//헤드노드 메모리 해제
	return 1;
}





