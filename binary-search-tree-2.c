/* 필요한 헤더파일 추가 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node { //트리 구조체 노드
	int key; // 가질 값
	struct node *left;  //왼쪽 자식 노드 가리킬 자기참조 구조체 포인터
	struct node *right; //오른쪽 자식 노드 카리킬 자기참조 구조체 포인터
} Node; //별칭 Node

/* 반복방식의 중위 순회에서 사용할 스택 */
#define MAX_STACK_SIZE 20   // 최대 스택 사이즈 20
Node* stack[MAX_STACK_SIZE];// 구조체 포인터 배열 스택
int top = -1; //스택 탑 -1로 초기화

Node* pop(); // 팝함수 선언 - 구조체 포인터 반환
void push(Node* aNode); //푸쉬함수 선언 - 구조체 포인터 매개변수로 보냄

/* 레벨순회 에서 사용할 원형 큐  */
#define MAX_QUEUE_SIZE 20 //최대 큐사이즈 20, 원형 큐에선 19개 공간 사용가능
Node* queue[MAX_QUEUE_SIZE]; //구조체 포인터 배열 큐
int front = -1; //큐 front -1 로 초기화
int rear = -1;  //큐 rear -1 로 초기화

Node* deQueue(); //디큐 함수선언 - 구조체 포인터 반환
void enQueue(Node* aNode);  // 인큐 함수선언 - 구조체 포인터 매개변수로 받음


/* 함수 리스트 */
int initializeBST(Node** h);          //헤드 노드 생성, 메모리 동적할당, 스택,큐 초기화
// 매개변수로 이중포인터 사용해 헤드노드의 주소를 인수로 보내고 헤드노드를 직접 건듬
void recursiveInorder(Node* ptr);	  //재귀방식 중위 순회
void iterativeInorder(Node* ptr);     //반복방식 중위 순회
void levelOrder(Node* ptr);	          //레벨 순회
int insert(Node* head, int key);      //트리에 노드 추가
int deleteNode(Node* head, int key);  //노드 삭제
int freeBST(Node* head);   //트리 노드들의 동적 메모리 해제
void freeNode(Node* ptr) ; //재귀형식으로 동적 메모리 해제를 위한 함수

int main()
{
	char command; //명령 입력받을 command
	int key;      //노드에 넣을 내용 key
	Node* head = NULL; //트리 구조체 포인터인 헤드,헤드는 루트노드를 가리킴
	printf("[----- [이찬] [2019038029] -----]\n");
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
		switch(command) { //사용자의 입력에 따른 명령 실행
		case 'z': case 'Z':
			initializeBST(&head); //헤드노드 포인터의 주소를 보냄
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
	return 1; //프로그램종료
}

 //헤드 노드 생성, 메모리 동적할당, 스택,큐 초기화
int initializeBST(Node** h) {//head자체의 주소값 받아옴, 함수에서 *h=head
	// 트리가 비어있지 않다면 동적메모리 해제 먼저 진행
	if(*h != NULL){
		freeBST(*h);
	}
	*h = (Node*)malloc(sizeof(Node)); //헤드노드 동적할당
	(*h)->left = NULL; // 루트노드 가리킬 left
	(*h)->right = *h;  // 자기자신을 가리키는 right 
	(*h)->key = -9999;
	top = -1;          //스택 초기화
	front = rear = -1; // 큐 초기화
	return 1; //함수 종료
}

//재귀방식 중위 순회 = 왼쪽자식 먼저 출력-> 부모->오른쪽자식
void recursiveInorder(Node* ptr)
{
	//이동한 ptr이 NULL이 아니면 실행
	if(ptr!=NULL) {
		recursiveInorder(ptr->left); // 왼쪽자식노드로 이동한 주소로 함수 호출
		printf(" [%d] ", ptr->key);  // 현재 노드 key 출력
		recursiveInorder(ptr->right);// 오른쪽자식노드로 이동한 주소로 함수 호출
	}
}

//반복방식 중위 순회 - 스택 사용
void iterativeInorder(Node* node){ //매개변수로 루트노드 받아옴
//스택에 다녀간 노드를 담아두고 중위순회의 방식대로 pop하며 출력
	while(1){ //무한루프
		while(node!=NULL){ //node 가 NULL일때 까지 반복,무한루프 반복될때 node=NULL이면 작동 x
			push(node);    //현재 node를 스택에 푸쉬
			node=node->left; //왼쪽 자식노드로 이동
		}
		node = pop(); //스택 탑에있는 것을 node에 팝해줌
		if(node == NULL) //스택에 남아있는것이 없을 때 
			break; //무한루프 탈출
		printf(" [%d] ", node->key); //현재 노드의 키 값 출력
		node = node->right; //오른쪽 자식 노드로 이동
	}
	return ; //함수종료
}

//레벨 순회 - 원형 큐 사용
void levelOrder(Node* ptr){//매개변수로 루트노드 받아옴
	if(ptr==NULL){ //트리가 비어있다면
		printf("your tree is empty."); //안내메세지 출력
		return ;// 함수종료
	}
	enQueue(ptr); //루트노드를 큐에 집어넣음

	//무한루프 돌면서 레벨순회 순서대로 큐에 집어넣고,빼주면서 출력함
	//큐가 선입 선출이므로 미리 큐에 넣은 낮은 레벨 노드들이 먼저 빠져나오며 출력 
	while(1){ 
		ptr = deQueue(); //큐에서 의미상 삭제된 위치 구조체 포인터 ptr에 대입
		if(ptr!=NULL){ //ptr이 NULL이 아닐때= 큐가 비지 않았을 떄
			printf(" [%d] ", ptr->key); //디큐한 ptr 출력
			if(ptr->left != NULL) //현재ptr의 왼쪽 자식노드가 있을 때
				enQueue(ptr->left); // 큐에 집어넣음
			if(ptr->right !=NULL) //현재ptr의 오른쪽 자식노드가 있을 때
				enQueue(ptr->right);// 큐에 집어넣음
		}
		else //큐가 비어서 더이상 출력할 것이 없을 때
			break; //무한루프 종료
	}
}

//트리에 노드 추가 
int insert(Node* head, int key){
	Node* Nnode = (Node*)malloc(sizeof(Node)); //새로 만든 자식 노드 동적할당
	Nnode->key = key; 	//입력받은 key 를 노드key값으로 초기화
	Nnode->left = NULL; //left,right는 초기값으로 NULL 초기화
	Nnode->right = NULL;

	// 루트노드가 안 만들어진 경우
	if (head->left == NULL) {
		head->left = Nnode; //헤드노드 연결해 루트노드 생성 후
		return 0; // 함수종료
	}
	//이진탐색트리 생성규칙에 맞춰 루트노드 기준으로 대소에 따라 노드 생성될 위치 설정
	Node* ptr1 = head->left; //탐색용 트리구조체 포인터 ptr1
	Node* ptr2 = NULL; //탐색하는 ptr1노드의 부모노드 위치를 저장해 놓을 포인터 ptr2
	
	while (ptr1!=NULL) { // 탐색하던 ptr이 NULL일 때까지 반복
		//트리 내에 이미입력한 key노드가 있는경우
		if(ptr1->key == key){
			printf("\nThe key you entered is already in the tree.");
			return 0; //바로 함수를 종료함
		}
		//ptr1이 탐색하기위해 이동하기 전 부모노드 위치 저장
		ptr2 = ptr1;
		//입력된 key 와 원래 노드의 키값과의 비교
		if(ptr1->key > key) // 현재위치의 노드key가 입력된 key보다 클 때
			ptr1= ptr1->left; // 왼쪽 자식노드로 이동
		else //작을 때 (같을 때는 이미 윗 조건에서 걸러짐)
			ptr1= ptr1->right;// 오른쪽 자식노드로 이동
	} 
	//반복문 종료되면서 ptr1=NULL이 되고 
	//ptr2는 추가되는 노드의 부모노드 위치에 있음

	if (ptr2->key > key) // 부모노드보다 새로운 노드의 값이 작으면
		ptr2->left = Nnode; // 새노드는 왼쪽 자식노드로
	else //크다면
		ptr2->right = Nnode; // 새노드는 오른쪽 자식노드로 
	return 0; //함수종료
}

//노드 삭제 - 리프노드삭제가 아니기 때문에 자식이 있는 노드 삭제등, 여러 케이스 고려해야함
int deleteNode(Node* head, int key){

}

//재귀형식으로 동적 메모리 해제를 위한 함수
void freeNode(Node* ptr)
{
	//받아온 ptr가 NULL이 아닐때 실행-> 자식노드가 없을 때 까지 탐색
	if(ptr!=NULL) {
		freeNode(ptr->left);  //왼쪽자식노드 주소로 함수호출
		freeNode(ptr->right); //오른쪽 자식 노드 주소로 함수호출 
		free(ptr);  //현재 ptr 위치 동적 메모리 해제
	}
	// 자식노드들을 먼저 동적 메모리 해제 시킨 이후에 부모노드가 해제되야
	// 모든 자식들을 동적메모리 해제시킬 수 있기 때문에 후위 순회 방식으로 해제함
	return ; //함수종료
}

//트리 노드들의 동적 메모리 해제
int freeBST(Node* head){	
	// 트리가 비어있다면
	if(head->left == NULL)
	{
		free(head); //헤드 동적 메모리 해제
		return 1;   //함수종료
	}
	Node* dt = head->left; // 노드 포인터 p는 루트노드 가리킴
	freeNode(dt);  //루트노드의 주소를 보내줘 재귀적으로 동적메모리 해제
	free(head); // 처음의 헤드노드 동적 메모리 해제
	return 1;   //함수 종료
}

//스택 팝 함수
Node* pop(){
	 if(top == -1) //스택에 아무것도 들어있지 않으면
        return NULL; //NULL 리턴
    else //스택이 비어있지 않으면
    	return stack[top--]; 
		//현재 탑위치의 구조체 포인터 배열 요소 반환후 top을 한칸 내림
}

//스택 푸쉬 함수
void push(Node* aNode){
	stack[++top] = aNode; //탑을 한칸 올리고 
	//받아온 구조체 포인터 탑 위치에 대입
}

// 원형큐 디큐 함수
Node* deQueue(){
	//큐가 비어있을 떄
	if (front == rear) {
		return NULL; //NULL 반환
	}
	//front 증가시켜 front위치 요소 의미상으로 큐에서 삭제
	front = (front + 1) % MAX_QUEUE_SIZE; //modulo 연산이용 front 1칸증가
	return queue[front]; //front가 증가되어 큐에서 삭제된위치 요소(구조체 포인터) 반환 
}

//원형큐 인큐 함수
void enQueue(Node* aNode){ 	//구조체 포인터를 매개변수로 받아옴
	//큐가 꽉 찼을 때 = 증가시킨 rear가 front 일 때
	if (front == (rear + 1) % MAX_QUEUE_SIZE) {
		return; //함수종료
	} 
	rear = (rear + 1) % MAX_QUEUE_SIZE; //modulo 연산이용 rear 1칸증가
	queue[rear] = aNode; //증가시킨 rear위치에 받아온 구조체 포인터 넣어줌
}

