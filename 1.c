
#include <stdio.h>
#include <stdlib.h>

//节点定义
typedef struct Node {
	int value;
	struct Node* next;
}Node;

//链表定义
typedef struct List {
	Node* head;
	int length;
}List;

//创建链表
List* createList() {
	List* newList = (List*)malloc(sizeof(List));
	newList->length = 0;
	newList->head = NULL;
}

//在链表结尾添加节点
void addNode(List* list,int value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->value = value;
	if (list->head == NULL) {
		list->head = newNode;
		(list->length)++;
		return;
	}
	Node* now = list->head;
	while (now->next != NULL) {
		now = now->next;
	}
	now->next = newNode;
	(list->length)++;
}


//按照要求直接对原链表更改
void Solution(List* list) {
	Node* two=list->head->next;
	Node* two_head = two;
	Node* one = list->head;
	for (int k = 0; k < (list->length) / 2-1; k++) {
		one->next = one->next->next;
		two->next = two->next->next;
		one = one->next;
		two = two->next;
	}

	one->next = NULL;

	Node* prev = NULL;
	Node* current = two_head;
	Node* next = NULL;

	while (current != NULL) {
		next = current->next; // 保存下一个节点
		current->next = prev; // 反转当前节点的指向
		prev = current;       // 移动 prev 和 current
		current = next;
	}
	two_head->next = list->head;
	list->head = prev;

}

//测试
int main() {
	List* list = createList();

	for (int k = 1; k < 7; k++) {
		addNode(list, k);
	}
	Solution(list);
	Node* now = list->head;
	for (int k = 0; k < list->length; k++) {
		printf("%d  ", now->value);
		now = now->next;
	}
	return 0;
}