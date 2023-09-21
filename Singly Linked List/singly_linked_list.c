#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
	int data;	// 가지고 있는 데이터
	struct Node *next;	// 다음 노드 정보
}Node;

Node *head;	//더미 머리 
Node *tail;	//더미 꼬리 
int size;	//링크드 리스트 크기

void InitList();						//리스트 초기화
bool InsertAfter(int value, Node *node);			//특정 노드 뒤 삽입
bool DeleteNext(Node *node);					//특정 노드 뒤 삭제
bool DeleteNode(Node *node);					//특정 노드 삭제
Node *FindNodeUsingValue(int value);				//data 비교하여 노드 찾기
Node *FindNodeUsingIndex(int num);				//index 비교하여 노드찾기
int GetIndex(int value);					//특정 data 의 index 반환
int GetSize() { return size; }					//리스트의 크기 반환
void DeleteAll();						//모든 노드 제거
void PrintList();

void InitList()
{
	head = (Node*)malloc(sizeof(Node));		//머리 메모리 할당
	tail = (Node*)malloc(sizeof(Node));		//꼬리 메모리 할당
	head->next = tail;				//머리 다음은 꼬리
	tail->next = tail;				//꼬리 다음도 꼬리
	size = 0;					//사이즈는 0
}

bool InsertAfter(int value, Node* node)
{
	if (node == tail)				//꼬리 뒤에 삽입 할수 없다.
		return false;

	Node* newNode = (Node*)malloc(sizeof(Node));	//메모리 할당
	newNode->data = value;				//값을 넣어준다
	newNode->next = node->next;			//특정노드가 가르키던 노드를 내가 대신 가르키고
	node->next = newNode;				//특정노드가 나를 가르키게 한다.
	++size;						//크기를 하나 늘려준다.
	printf("Insert : %d \n", newNode->data);	//메세지 출력
	return true;
}

bool DeleteNext(Node* node)
{
	if (node->next == tail)				//꼬리를 지울수 없다.
		return false;

	Node* deleteNode = node->next;			//지울 노드를 기억한다.
	printf("delete : %d \n", deleteNode->data);	//메세지 출력
	node->next = deleteNode->next;			//지울 노드가 가르키던 노드를 특정 노드가 가르키게 한다.
	free(deleteNode);				//메모리를 해제해준다(중요)
	--size;						//크기를 줄여준다.
	return true;
}

bool DeleteNode(Node* node)
{
	if (node == head || tail == node)	//머리나 꼬리는 지울수 없다.
		return false;

	Node* preNode = head;			//노드는 이전노드 정보를 가지고 있지 않아서 따로 기억해야한다.
	Node* temp = head->next;		//찾는 노드

	while (temp != tail)					//리스트를 끝까지 돈다.
	{
		if (node == temp)				//지울 노드를 찾았다면
		{
			Node* deleteNode = node;		//지울 노드를 기억한다.
			preNode->next = deleteNode->next;	//이전 노드가 지울 노드의 다음을 가르키게한다.
			printf("delete : %d \n", deleteNode->data);
			free(deleteNode);			//지울 노드를 메모리 해제
			--size;					//크기를 줄여준다.
			return true;
		}

		preNode = temp;			//못 찾았으면
		temp = temp->next;		//다음 노드로
	}
	return false;
}

Node* FindNodeUsingValue(int value)
{
	Node* temp = head->next;		//찾는 노드
	while (temp != tail)			//리스트를 끝까지 돈다
	{
		if (temp->data == value)	//특정 값을 가진 노드를 찾았으면
		{
			printf("Find Value Data : %d \n", temp->data);
			return temp;		//노드를 반환한다.
		}
		temp = temp->next;		//못 찾았으면 다음 노드로
	}
	return temp;				//끝까지 돌았는데 없으면 꼬리 노드 반환
}

Node* FindNodeUsingIndex(int num)
{
	if (num < 0 || num >= size)			//크기에 벗어나 있으면 꼬리반환
		return tail;

	Node* temp = head->next;			//head next 가 index 0 노드이다
	for (int i = 0; i < num;++i)			//반복문을 돌아서
		temp = temp->next;			//num 번째 node를 찾는다.

	printf("Find index : %d Data : %d \n", num, temp->data);
	return temp;
}

int GetIndex(int value)
{
	int index = 0;
	Node* temp = head->next;		
	while (temp != tail)		
	{
		if (temp->data == value)
		{
			printf("Value : %d index : %d \n", value, index);
			return index;
		}
		++index;
		temp = temp->next;
	}

	return -1;
}

void DeleteAll()
{
	Node* temp = head->next;		//찾는 노드
	Node* deleteNode;			//지울 노드
	while (temp != tail)			//리스트 끝까지 돈다.
	{
		deleteNode = temp;		//현재 노드를 지울 노드로 지정한다.
		temp = temp->next;		//현재 노드는 다음 노드로 넘어간다.
		free(deleteNode);		//지울 노드를 지워준다.
	}
	size = 0;				//사이즈 초기화
	head->next = tail;			//다 비었으니 head 다음은 tail

	printf("Delete All\n");
}

void PrintList()
{
	Node* temp = head->next;			//찾는 노드
	while (temp != tail)				//리스트 끝까지 돈다.
	{
		printf("%d \n", temp->data);		//메세지 출력
		temp = temp->next;			//다음 노드로
	}
	printf("size : %d \n", size);			//크기도 출력
}