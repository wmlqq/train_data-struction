#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
    int secret;
    int index;
} Node;

//创建新节点
Node* createNode(int secret, int index) {
    Node* New = (Node*)malloc(sizeof(Node));
    if (New == NULL) {
        printf("内存分配失败！\n");
        exit(1);
    }
    New->index = index;
    New->secret = secret;
    New->next = NULL;
    return New;
}

//创建约瑟夫环
Node* createCircle(int* n) {
    printf("输入人数：");
    scanf_s("%d", n);
    
    if (*n <= 0) {
        printf("人数必须为正整数！\n");
        return NULL;
    }

    int* secrets = (int*)malloc((*n) * sizeof(int));
    if (secrets == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }
    
    printf("\n输入依次%d个人的密码\n", *n);
    for (int k = 0; k < *n; k++) {
        scanf_s("%d", &secrets[k]);
    }

    Node* head = NULL;
    Node* last = NULL;
    for (int k = 0; k < *n; k++) {
        if (!k) {
            head = createNode(secrets[k], k + 1);
            last = head;
        }
        else {
            Node* ex = createNode(secrets[k], k + 1);
            last->next = ex;
            last = ex;
        }
        if (k == *n - 1) {
            last->next = head;
        }
    }

    free(secrets);
    return head;
}

//一轮开枪
int shOOton(Node** head, int size, int m) {
    if (size == 1) {
        printf("%d", (*head)->index);
        int secret = (*head)->secret;
        free(*head);
        *head = NULL;
        return secret;
    }

    Node* before = *head;
    Node* now = *head;

    //使before指向head之前
    for (int k = 1; k < size; k++) {
        before = before->next;
    }

    // 移动到要删除的位置
    int steps = (m % size == 0) ? size : (m % size);
    for (int k = 1; k < steps; k++) {
        before = now;
        now = now->next;
    }

    int secret = now->secret;
    printf("%d   ", now->index);

    // 更新链表连接
    if (now == *head) {
        *head = now->next;
    }
    before->next = now->next;

    // 释放节点
    free(now);

    return secret;
}

//结果
void shOOtend(Node** head, int size, int* m) {
    int M = *m;
    for (int k = 0; k < size; k++) {
        M = shOOton(head, size - k, M);
    }
}

//游戏开始
void beginning() {
    int m, size;
    Node* head = createCircle(&size);
    if (head == NULL) {
        return;
    }
    
    printf("输入初始报数：");
    scanf_s("%d", &m);
    if (m <= 0) {
        printf("报数必须为正整数！\n");
        return;
    }
    
    printf("\n");
    shOOtend(&head, size, &m);
}

int main(void) {
    beginning();
    return 0;
}