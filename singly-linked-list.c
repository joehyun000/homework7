/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
    if (h == NULL) {
        // h가 NULL인 경우에는 새로운 노드를 할당 불가
        return -1; // 실패를 나타내는 값을 반환
    }

    listNode* node = (listNode*)malloc(sizeof(listNode));    //새로운 노드 할당
    node->key = key;                  //그 새로운 노드의 key는 입력받은 key
    node->link = h->first;     		  //새로운 노드가 가리키는 노드 =  h->first가 가리키고 있던 원래 앞에 있던 노드
    h->first = node;				  //h->first가 가리키는 것은 새로 insert된 노드

    return 0; // 성공을 나타내는 값을 반환
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//새로운 노드 할당
	newNode->key = key;											  	//그 새로운 노드의 key는 입력받은 key
	newNode->link = NULL;											//새로운 노드가 가리키는 노드 = NULL

	if(h->first == NULL) {											//만약 노드가 비어있는 상태라면
		h->first = newNode;											//새로운 노드가 젤 first에 insert됨
		return 0;
	}

	listNode* currentNode = h->first;								//현재 노드를 지칭하는 노드 생성
	listNode* previousNode = NULL;									//그 현재 노드를 가리키는 노드를 지칭하는 노드 생성
	while (currentNode != NULL && currentNode->key < key) {			//현재 노드가 연결리스트의 끝에 도달하거나
		previousNode = currentNode;									//현재 노드 key가 새 노드 key보다 작으면 
    	currentNode = currentNode->link;							//다음 노드로 이동 
	}																//(이전 노드 = 현재 노드, 현재 노드 = 현재 노드가 가리키는 노드)

	if (currentNode == h->first) {									//현재 노드가 맨 앞의 노드라면
        newNode->link = h->first;									//새 노드는 현재 노드(맨 앞 노드)를 가리킴
        h->first = newNode;											//그 후 h->first가 새 노드를 가리킴
    }
	else {															//새 노드를 노드들 중간에 삽입해야하는 경우
		newNode->link = currentNode;								//새 노드는 현재 노드를 가리킴
		previousNode->link = newNode;								//이전 노드는 새 노드를 가리킴
	}
	
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//새로운 노드 할당

	newNode->key = key;												//그 새로운 노드의 key는 입력받은 key
    newNode->link = NULL;											//새로운 노드가 가리키는 노드 = NULL

	listNode* currentNode = h->first;								//현재 노드는 연결 리스트의 맨 처음 노드를 나타냄
	if(currentNode == NULL) {										//현재 노드가 연결 리스트의 마지막 노드라면
		h->first = newNode;											//연결 리스트의 맨 앞에 새 노드를 삽입
	}
	else {
		while(currentNode->link !=NULL){							//현재 노드를 맨 뒤까지 보내기위해 while문 사용
			currentNode = currentNode->link;						//현재 노드를 한 칸 뒤로 보냄
		}
		currentNode->link = newNode;								//맨 뒤까지 도달하면 그 노드가 새 노드를 가리키도록 하여 insert함
	}
	
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {										
	if (h->first == NULL) {									// 연결 리스트가 비어있다면 
        return -1; 											// 아무 동작도 하지않고 실패를 나타내는 값 반환
    }
	listNode* temp = h->first;								//임시 노드 temp는 연결 리스트의 첫번째 노드를 나타냄
	h->first = temp->link;									//h->first는 첫번째 노드가 가리키는 노드를 가리킴
	free(temp);												//원래의 첫번째 노드를 연결리스트에서 분리시키고, free로 노드를 삭제
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* previousNode = NULL;								//현재 노드 바로 앞 노드를 나타내는 이전 노드 할당, NULL로 초기화
	listNode* currentNode = h->first;							//현재 노드는 맨 처음 노드를 나타냄

	while (currentNode != NULL && currentNode->key != key) {	//현재 노드가 끝에 도달하거나 입력한 키와 현재 노드의 key 불일치일 경우, 
		previousNode = currentNode;								//이전 노드= 현재 노드
		currentNode = currentNode->link;						//현재 노드 = 현재 노드가 가리키는 노드로 설정 => 노드를 한 칸 뒤로 이동
	}

	if (currentNode != NULL) { 									//키를 찾았을 경우를 나타냄
		if (previousNode != NULL) {								//삭제할 노드가 첫 번째 노드가 아닌 경우
			previousNode->link = currentNode->link;				//이전 노드는 현재 노드가 가리키는 노드를 가리킴
		} else {												//삭제할 노드가 첫 번째 노드인 경우
			h->first = currentNode->link;						//맨 앞 노드는 현재 노드가 가리키는 노드
		}
		free(currentNode);										//현재 노드를 free함으로써 연결 리스트에서 삭제
	}

	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL) {										//노드가 비어있으면 오류를 나타내도록 -1리턴
		return -1;
	}

	listNode* previousNode = NULL;								//현재 노드 바로 앞 노드를 나타내는 이전 노드 할당, NULL로 초기화
    listNode* currentNode = h->first;							//현재 노드는 맨 처음 노드를 나타냄

	while(currentNode->link !=NULL) {							//연결 리스트의 끝에 도달하지 못한 경우
		previousNode = currentNode;								//이전 노드 = 현재 노드를 
		currentNode = currentNode->link;						//현재 노드 = 현재 노드가 가리키는 노드로 설정 => 노드를 한 칸 뒤로 이동
	}
	if(previousNode == NULL) {									//연결 리스트에 노드가 하나만 존재할 경우
		h->first = NULL;										//연결 리스트는 비어있게 됨.
	}
	else {
		previousNode->link =NULL;								//마지막 노드와의 연결을 끊음
		free(currentNode);										//삭제할 노드를 free함으로써 연결 리스트에서 삭제
	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* previousNode = NULL;					//이전 노드를 가리키는 포인터
    listNode* currentNode = h->first;				//현재 노드를 가리키는 포인터
    listNode* nextNode = NULL;						//다음 노드를 가리키는 포인터

	while(currentNode != NULL) {					//연결 리스트의 끝에 도달하지 못한 경우
		nextNode = currentNode->link;				//다음 노드는 현재 노드가 가리키는 노드
		currentNode->link = previousNode;			//현재 노드는 이전 노드를 가리킴
		previousNode = currentNode;					//이전 노드 = 현재 노드
		currentNode = nextNode;						//현재 노드는 다음 노드를 나타냄으로써 그 다음 노드로 이동
	}
	h->first = previousNode;						//마지막엔 연결 리스트의 시작을 맨 뒤로 바꿔줌으로써 링크가 역순으로 재배치 된걸 완성
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

