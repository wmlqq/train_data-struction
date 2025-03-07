#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    char data;//数据域
    struct Node*next;//指针域
}Node,LinkList;//定义链表节点

typedef struct Stack{
    LinkList *top;//栈顶指针
    int count;//栈中元素个数
}Stack;//定义栈

//头插法添加链表节点
void addNodefront(LinkList*list,char data){
    Node*node=(Node*)malloc(sizeof(Node));
    node->data=data;
    node->next=list->next;
    list->next=node;
}

//入栈
void push(Stack*stack,char data){
    addNodefront(stack->top,data);
    stack->count++;
}

//出栈
void pop(Stack*stack){
    if(stack->count==0)return;
    Node*node=stack->top->next;
    stack->top->next=node->next;
    stack->count--;
    free(node);
}

//获取栈顶元素
char top(Stack*stack){
    if(stack->count==0)return '@';
    return stack->top->next->data;
}

//释放栈内存
void freestack(Stack*stack){
    while(stack->count>0){
        pop(stack);
    }
    free(stack);
}

//判断是否是回文字符串
int isBackString(){
    Stack*stack=(Stack*)malloc(sizeof(Stack));
    LinkList*list=(LinkList*)malloc(sizeof(LinkList));
    stack->top=list;
    stack->count=0;
    list->next=NULL;
    while(1){
        //读取输入
        char c=getchar();
        if(c=='&')break;
        else{
            //入栈
            push(stack,c);
        }
    }
    while(1){
        char c=getchar();
        if(c=='@'){freestack(stack);return 1;}
        else if(top(stack)=='@'||c!=top(stack)){freestack(stack);return 0;}
        else pop(stack);
    }
    freestack(stack);
    return 0;
}