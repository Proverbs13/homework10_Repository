/* �ʿ��� ������� �߰� */
#include <stdio.h>
#include <stdlib.h>

typedef struct node { //Ʈ�� ����ü ���
	int key; // ���� ��
	struct node *left;  //���� �ڽ� ��� ����ų �ڱ����� ����ü ������
	struct node *right; //������ �ڽ� ��� ī��ų �ڱ����� ����ü ������
} Node; //��Ī Node

/* �ݺ������ ���� ��ȸ���� ����� ���� */
#define MAX_STACK_SIZE 20   // �ִ� ���� ������ 20
Node* stack[MAX_STACK_SIZE];// ����ü ������ �迭 ����
int top = -1; //���� ž -1�� �ʱ�ȭ

Node* pop(); // ���Լ� ���� - ����ü ������ ��ȯ
void push(Node* aNode); //Ǫ���Լ� ���� - ����ü ������ �Ű������� ����

/* ������ȸ ���� ����� ���� ť  */
#define MAX_QUEUE_SIZE 20 //�ִ� ť������ 20, ���� ť���� 19�� ���� ��밡��
Node* queue[MAX_QUEUE_SIZE]; //����ü ������ �迭 ť
int front = -1; //ť front -1 �� �ʱ�ȭ
int rear = -1;  //ť rear -1 �� �ʱ�ȭ

Node* deQueue(); //��ť �Լ����� - ����ü ������ ��ȯ
void enQueue(Node* aNode);  // ��ť �Լ����� - ����ü ������ �Ű������� ����


/* �Լ� ����Ʈ */
int initializeBST(Node** h);          //��� ��� ����, �޸� �����Ҵ�, ����,ť �ʱ�ȭ
// �Ű������� ���������� ����� ������� �ּҸ� �μ��� ������ ����带 ���� �ǵ�
void recursiveInorder(Node* ptr);	  //��͹�� ���� ��ȸ
void iterativeInorder(Node* ptr);     //�ݺ���� ���� ��ȸ
void levelOrder(Node* ptr);	          //���� ��ȸ
int insert(Node* head, int key);      //Ʈ���� ��� �߰�
int deleteNode(Node* head, int key);  //��� ����
int freeBST(Node* head);   //Ʈ�� ������ ���� �޸� ����
void freeNode(Node* ptr) ; //����������� ���� �޸� ������ ���� �Լ�

int main()
{
	char command; //��� �Է¹��� command
	int key;      //��忡 ���� ���� key
	Node* head = NULL; //Ʈ�� ����ü �������� ���,���� ��Ʈ��带 ����Ŵ
	printf("[----- [����] [2019038029] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);
		switch(command) { //������� �Է¿� ���� ��� ����
		case 'z': case 'Z':
			initializeBST(&head); //����� �������� �ּҸ� ����
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;
		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;
		case 'l': case 'L':
			levelOrder(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}while(command != 'q' && command != 'Q');
	return 1; //���α׷�����
}

 //��� ��� ����, �޸� �����Ҵ�, ����,ť �ʱ�ȭ
int initializeBST(Node** h) {//head��ü�� �ּҰ� �޾ƿ�, �Լ����� *h=head
	// Ʈ���� ������� �ʴٸ� �����޸� ���� ���� ����
	if(*h != NULL){
		freeBST(*h);
	}
	*h = (Node*)malloc(sizeof(Node)); //����� �����Ҵ�
	(*h)->left = NULL; // ��Ʈ��� ����ų left
	(*h)->right = *h;  // �ڱ��ڽ��� ����Ű�� right 
	(*h)->key = -9999;
	top = -1;          //���� �ʱ�ȭ
	front = rear = -1; // ť �ʱ�ȭ
	return 1; //�Լ� ����
}

//��͹�� ���� ��ȸ = �����ڽ� ���� ���-> �θ�->�������ڽ�
void recursiveInorder(Node* ptr)
{
	//�̵��� ptr�� NULL�� �ƴϸ� ����
	if(ptr!=NULL) {
		recursiveInorder(ptr->left); // �����ڽĳ��� �̵��� �ּҷ� �Լ� ȣ��
		printf(" [%d] ", ptr->key);  // ���� ��� key ���
		recursiveInorder(ptr->right);// �������ڽĳ��� �̵��� �ּҷ� �Լ� ȣ��
	}
}

//�ݺ���� ���� ��ȸ - ���� ���
void iterativeInorder(Node* node){ //�Ű������� ��Ʈ��� �޾ƿ�
//���ÿ� �ٳణ ��带 ��Ƶΰ� ������ȸ�� ��Ĵ�� pop�ϸ� ���
	while(1){ //���ѷ���
		while(node!=NULL){ //node �� NULL�϶� ���� �ݺ�,���ѷ��� �ݺ��ɶ� node=NULL�̸� �۵� x
			push(node);    //���� node�� ���ÿ� Ǫ��
			node=node->left; //���� �ڽĳ��� �̵�
		}
		node = pop(); //���� ž���ִ� ���� node�� ������
		if(node == NULL) //���ÿ� �����ִ°��� ���� �� 
			break; //���ѷ��� Ż��
		printf(" [%d] ", node->key); //���� ����� Ű �� ���
		node = node->right; //������ �ڽ� ���� �̵�
	}
	return ; //�Լ�����
}

//���� ��ȸ - ���� ť ���
void levelOrder(Node* ptr){//�Ű������� ��Ʈ��� �޾ƿ�
	if(ptr==NULL){ //Ʈ���� ����ִٸ�
		printf("your tree is empty."); //�ȳ��޼��� ���
		return ;// �Լ�����
	}
	enQueue(ptr); //��Ʈ��带 ť�� �������

	//���ѷ��� ���鼭 ������ȸ ������� ť�� ����ְ�,���ָ鼭 �����
	//ť�� ���� �����̹Ƿ� �̸� ť�� ���� ���� ���� ������ ���� ���������� ��� 
	while(1){ 
		ptr = deQueue(); //ť���� �ǹ̻� ������ ��ġ ����ü ������ ptr�� ����
		if(ptr!=NULL){ //ptr�� NULL�� �ƴҶ�= ť�� ���� �ʾ��� ��
			printf(" [%d] ", ptr->key); //��ť�� ptr ���
			if(ptr->left != NULL) //����ptr�� ���� �ڽĳ�尡 ���� ��
				enQueue(ptr->left); // ť�� �������
			if(ptr->right !=NULL) //����ptr�� ������ �ڽĳ�尡 ���� ��
				enQueue(ptr->right);// ť�� �������
		}
		else //ť�� �� ���̻� ����� ���� ���� ��
			break; //���ѷ��� ����
	}
}

//Ʈ���� ��� �߰� 
int insert(Node* head, int key){
	Node* Nnode = (Node*)malloc(sizeof(Node)); //���� ���� �ڽ� ��� �����Ҵ�
	Nnode->key = key; 	//�Է¹��� key �� ���key������ �ʱ�ȭ
	Nnode->left = NULL; //left,right�� �ʱⰪ���� NULL �ʱ�ȭ
	Nnode->right = NULL;

	// ��Ʈ��尡 �� ������� ���
	if (head->left == NULL) {
		head->left = Nnode; //����� ������ ��Ʈ��� ���� ��
		return 0; // �Լ�����
	}
	//����Ž��Ʈ�� ������Ģ�� ���� ��Ʈ��� �������� ��ҿ� ���� ��� ������ ��ġ ����
	Node* ptr1 = head->left; //Ž���� Ʈ������ü ������ ptr1
	Node* ptr2 = NULL; //Ž���ϴ� ptr1����� �θ��� ��ġ�� ������ ���� ������ ptr2
	
	while (ptr1!=NULL) { // Ž���ϴ� ptr�� NULL�� ������ �ݺ�
		//Ʈ�� ���� �̹��Է��� key��尡 �ִ°��
		if(ptr1->key == key){
			printf("\nThe key you entered is already in the tree.");
			return 0; //�ٷ� �Լ��� ������
		}
		//ptr1�� Ž���ϱ����� �̵��ϱ� �� �θ��� ��ġ ����
		ptr2 = ptr1;
		//�Էµ� key �� ���� ����� Ű������ ��
		if(ptr1->key > key) // ������ġ�� ���key�� �Էµ� key���� Ŭ ��
			ptr1= ptr1->left; // ���� �ڽĳ��� �̵�
		else //���� �� (���� ���� �̹� �� ���ǿ��� �ɷ���)
			ptr1= ptr1->right;// ������ �ڽĳ��� �̵�
	} 
	//�ݺ��� ����Ǹ鼭 ptr1=NULL�� �ǰ� 
	//ptr2�� �߰��Ǵ� ����� �θ��� ��ġ�� ����

	if (ptr2->key > key) // �θ��庸�� ���ο� ����� ���� ������
		ptr2->left = Nnode; // ������ ���� �ڽĳ���
	else //ũ�ٸ�
		ptr2->right = Nnode; // ������ ������ �ڽĳ��� 
	return 0; //�Լ�����
}

//��� ���� - ������������ �ƴϱ� ������ �ڽ��� �ִ� ��� ������, ���� ���̽� ����ؾ���
int deleteNode(Node* head, int key){

}

//����������� ���� �޸� ������ ���� �Լ�
void freeNode(Node* ptr)
{
	//�޾ƿ� ptr�� NULL�� �ƴҶ� ����-> �ڽĳ�尡 ���� �� ���� Ž��
	if(ptr!=NULL) {
		freeNode(ptr->left);  //�����ڽĳ�� �ּҷ� �Լ�ȣ��
		freeNode(ptr->right); //������ �ڽ� ��� �ּҷ� �Լ�ȣ�� 
		free(ptr);  //���� ptr ��ġ ���� �޸� ����
	}
	// �ڽĳ����� ���� ���� �޸� ���� ��Ų ���Ŀ� �θ��尡 �����Ǿ�
	// ��� �ڽĵ��� �����޸� ������ų �� �ֱ� ������ ���� ��ȸ ������� ������
	return ; //�Լ�����
}

//Ʈ�� ������ ���� �޸� ����
int freeBST(Node* head){	
	// Ʈ���� ����ִٸ�
	if(head->left == NULL)
	{
		free(head); //��� ���� �޸� ����
		return 1;   //�Լ�����
	}
	Node* dt = head->left; // ��� ������ p�� ��Ʈ��� ����Ŵ
	freeNode(dt);  //��Ʈ����� �ּҸ� ������ ��������� �����޸� ����
	free(head); // ó���� ����� ���� �޸� ����
	return 1;   //�Լ� ����
}

//���� �� �Լ�
Node* pop(){
	 if(top == -1) //���ÿ� �ƹ��͵� ������� ������
        return NULL; //NULL ����
    else //������ ������� ������
    	return stack[top--]; 
		//���� ž��ġ�� ����ü ������ �迭 ��� ��ȯ�� top�� ��ĭ ����
}

//���� Ǫ�� �Լ�
void push(Node* aNode){
	stack[++top] = aNode; //ž�� ��ĭ �ø��� 
	//�޾ƿ� ����ü ������ ž ��ġ�� ����
}

// ����ť ��ť �Լ�
Node* deQueue(){
	//ť�� ������� ��
	if (front == rear) {
		return NULL; //NULL ��ȯ
	}
	//front �������� front��ġ ��� �ǹ̻����� ť���� ����
	front = (front + 1) % MAX_QUEUE_SIZE; //modulo �����̿� front 1ĭ����
	return queue[front]; //front�� �����Ǿ� ť���� ��������ġ ���(����ü ������) ��ȯ 
}

//����ť ��ť �Լ�
void enQueue(Node* aNode){ 	//����ü �����͸� �Ű������� �޾ƿ�
	//ť�� �� á�� �� = ������Ų rear�� front �� ��
	if (front == (rear + 1) % MAX_QUEUE_SIZE) {
		return; //�Լ�����
	} 
	rear = (rear + 1) % MAX_QUEUE_SIZE; //modulo �����̿� rear 1ĭ����
	queue[rear] = aNode; //������Ų rear��ġ�� �޾ƿ� ����ü ������ �־���
}

