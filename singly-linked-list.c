/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

 /* 필요한 헤더파일 추가 */

typedef struct Node {                  // listnode 형의 연결리스트를 구성하는 노드.
	int key;                           // 값을 저장하는 key와 다음 노드를 가리키는 포인터 link로 구성되어 있다.
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;              // 연결리스트의 첫번째 노드를 가리키는 headnode.
}headNode;                           // first라는 이름의 Node타입 포인터로 구성 된다.


/* 함수 리스트 */
headNode* initialize(headNode* h);        // 첫번째 노드를 가리키는 headnode에 동적으로 메모리를 할당하거나, headnode가 NULL이면 메모리 해제
int freeList(headNode* h);         // 동적할당된 연결리스트의 메모리를 모두 해제.

int insertFirst(headNode* h, int key);  // 연결리스트의 첫번째 위치에 새로운 노드를 삽입
int insertNode(headNode* h, int key);   // 연결리스트가 오름차순이 되도록 입력 받은 key값에 따라 적절한 위치에 새로운 노드 삽입.
int insertLast(headNode* h, int key);   // 연결리스트 마지막 위치에 새로운 노드를 삽입

int deleteFirst(headNode* h);            // 연결리스트의 첫번째 노드 삭제
int deleteNode(headNode* h, int key);    // 입력받은 key값을 갖고 있는 노드를 찾아서 삭제
int deleteLast(headNode* h);             // 연결리스트의 마지막 노드 삭제
int invertList(headNode* h);             // 연결리스트를 거꾸로 전환

void printList(headNode* h);          // 연결리스트 내용 출력

int main()
{
	char command;
	int key;
	headNode* headnode = NULL;    

	printf("\n----- [조수현]  [2018038084] -----\n\n");

	do {
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


		switch (command) {
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

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
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
int insertFirst(headNode* h, int key) 
{
    if(h == NULL)                         // 헤드노드가 초기화 되지 않고 null을 가리키는 상태라면 초기화 먼저 수행하도록 경고문 출력.
    {                                     // 각 함수의 시작마다 헤드노드의 초기화 검사를 수행.
        printf("헤드 노드를 초기화 해주십시오.\n\n");
        return 0;
    }

	listNode* node = (listNode*)malloc(sizeof(listNode));  // 삽입할 새로운 노드를 동적할당하고 입력 받은 key값을 넣음
	node->key = key;

	node->link = h->first;      // 새로운 노드가 기존의 첫번째 노드를 가리키도록 링크
	h->first = node;           // 첫번째 노드를 가리키는 first가 node를 가리키도록 변경.

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key)
{
    if(h == NULL)              
    {
        printf("헤드 노드를 초기화 해주십시오.\n\n");
        return 0;
    }

	listNode* temp;   // 헤드노드의 위치를 담을 포인터 temp를 할당.
	temp = h->first;  // temp가 가리키는 주소를 연결리스트의 시작점으로 둠.

	if (h->first == NULL)        // 연결리스트의 노드가 하나 뿐이라면 insertFirst를 호출하여 리스트의 첫번째에 노드 삽입.
	{
		insertFirst(h, key);
		return 0;
	}

	else                    // 노드가 하나보다 많이 존재한다면
	{
		while(temp != NULL)     // temp가 연결리스트의 끝에 도달할 때까지
		{
			if (temp->link == NULL)   // 만약 현재 temp의 다음이 연결리스트의 끝이라면
			{
				insertLast(h, key);    // insertlast를 호출하여 리스트의 끝에 노드 삽입.
				return 0;
			}
			else if (key < temp->link->key)  // key값이 현재 temp의 다음 노드의 key값보다 작다면
			{
				listNode* node = (listNode*)malloc(sizeof(listNode));  // 삽입할 새로운 노드 동적 할당.
				node->key = key;                   // 입력 받은 key값을 새로운 노드에 넣음.
				node->link = temp->link;           // 새로운 노드가 현재 temp의 다음 노드를 가리키도록 링크.
				temp->link = node;                 // temp의 링크가 node를 가리키도록 변경.
				return 0;
			}
			temp = temp->link;     // temp가 연결리스트의 링크를 타고 다음 노드로 이동.
		}
	}
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key)
{
    if(h == NULL)
    {
        printf("헤드 노드를 초기화 해주십시오\n\n");
        return 0;
    }

	listNode* temp;     // 헤드 노드의 주소를 담을 포인터 temp 할당.
	temp = h->first;   // 현재 헤드 노드가 가리키는 주소를 temp에 넣음

	if (temp->link == NULL)               // 현재 temp가 마지막 노드를 가리키고 있다면
	{
		listNode* node = (listNode*)malloc(sizeof(listNode));   // 새로 삽입할 노드 동적 할당
		node->key = key;    // key값 대입
		node->link = NULL;  // 새로운 노드가 NULL을 가리키도록 링크.
		temp->link = node;  // 마지막 노드였던 temp가 node를 가리키도록 링크.
		
		return 0;
	}
	else
	{
		while (temp->link != NULL)   // 현재 마지막 노드가 아니라면
		{
			temp = temp->link;       // temp가 링크를 타고 한 노드씩 뒤로 이동. 마지막 노드에 도달하면 반복 종료.
		}

		listNode* node = (listNode*)malloc(sizeof(listNode));   // 반복이 끝나면 temp가 마지막 노드를 가리키고 있다는 뜻이므로
		node->key = key;        // 위의 if문과 마찬가지로 새로운 노드를 동적할당하여 리스트의 마지막에 삽입.
		node->link = NULL;
		temp->link = node;

		return 0;
	}
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h)
{
    if(h == NULL)
    {
        printf("헤드 노드를 초기화 해주십시오\n\n");
        return 0;
    }

    if(h->first == NULL)
    {
        printf("지울 노드가 없습니다.\n\n");
        return 0;
    }

	listNode* temp;  // 헤드 노드가 가리키는 주소를 담을 포인터 temp 선언.

	temp = h->first;    // 헤드 노드가 가리키는 현재 주소를 temp에 담음.
	h->first = h->first->link;   // 헤드 노드가 first의 다음 노드르 가리키도록 링크.
	free(temp);          // 첫번째 노드의 주소를 가진 temp를 free.

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key)
{
    if(h == NULL)
    {
        printf("헤드 노드를 초기화 해주십시오.\n\n");
        return 0;
    }

	listNode* temp;    // 헤드 노드가 가리키는 주소를 담을 포인터 temp
	listNode* trail;   // temp의 선행 노드를 가리킬 포인터 trail
	temp = h->first;
	trail = temp;

	if (temp == NULL)
	{
		printf("지울 노드가 없습니다.\n\n");
		return 0;
	}

	while (temp != NULL)       // 리스트의 끝에 도달할 때까지
	{
		if (temp->key == key)   // 입력 받은 key값과 일치하는 노드를 발견하면
		{
			if (trail == temp)   // trail과 temp가 같은 주소를 가리킴. 즉, 찾은 노드가 첫번째 노드라면 deletefirst 호출.
			{
				deleteFirst(h);
				return 0;
			}

			trail->link = temp->link;  // 선행 노드 trail의 링크를 temp가 가리키던 노드를 가리키도록 변경.
			free(temp);               // 현재 노드 temp를 free.
			return 0;
		}

		trail = temp;              // trail이 temp를 따라서 이동.
		temp = temp->link;         // temp를 하나 더 뒷 노드로 이동.
	}

	printf("해당 노드가 존재하지 않습니다.\n\n");    // 만일 위 반복문에서 return 되지 않았다면 입력 받은 key값을 담은 노드가 없다는 뜻이므로
	return 0;                                      // 해당 노드가 존재하지 않다는 텍스트 출력.
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h)
{
    if(h == NULL)
    {
        printf("헤드 노드를 초기화 해주십시오.\n\n");
        return 0;
    }

    if(h->first == NULL)
    {
        printf("지울 노드가 없습니다.\n\n");
        return 0;
    }

	listNode* temp;    // 헤드 노드의 주소를 담을 포인터 temp
	listNode* trail;   // 선행 노드의 주소를 담을 포인터 trail
	temp = h->first;

	while (temp->link != NULL)   // 마지막 노드에 도달할 때까지 temp와 trail 이동.
	{
		trail = temp;
		temp = temp->link;
	}

	trail->link = NULL;  // 선행 노드 trail이 NULL을 가리키도록 변경.
	free(temp);         // free(temp)

	return 0;
}

/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h)
{
    if(h == NULL)
    {
        printf("헤드 노드를 초기화 해주십시오.\n\n");
        return 0;
    }

	listNode* middle;    // node와 trail 사이에서 한 칸씩 다음 노드로 이동하며 링크를 역순으로 재배치할 포인터 middle
	listNode* trail;     // middle의 선행 노드를 가리킬 trail. middle이 자신의 앞에 있는 노드를 가리킬 수 있도록 선행 노드의 주소를 담는다.
	listNode* node;      // 헤드 노드의 주소를 담아서 가장 앞에서 먼저 이동할 포인터 node.

	node = h->first;     // node에 헤드 노드의 주소를 담고, middle을 NULL로 초기화
	middle = NULL;

	while (node != NULL)   // 리스트의 마지막에 도달할 때까지 반복
	{
		trail = middle;   // trail이 middle을 따라서 이동
		middle = node;    // middle이 node를 따라서 이동.
		node = node->link;    // node가 다음 노드로 이동.
		middle->link = trail;   // middle의 링크를 선행 노드 trail로 변경.
	}

	h->first = middle;          // 마지막으로 리스트의 시작 주소를 가리키는 헤드 노드가 middle을 가리키도록 해줌.

	return 0;
}

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}