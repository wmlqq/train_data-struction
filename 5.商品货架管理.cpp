#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define nameSIZE 20
#define GOODSNUM 100

//链表节点
typedef struct Node{
    int month;
    int day;
    struct Node*next;
}Node,linkList;

//栈模拟商品架
typedef struct GoodsStack{
    char*name;
    linkList*top;//栈顶是top的next
    int length; //栈的长度
}GoodsStack;

//队列暂时储存商品
typedef struct tempQueue{
    linkList*front;
    linkList*rear;
    int size; //队列的长度
}tempQueue;

//头插添加节点到链表
void addNodefront(linkList*head,int month,int day){
    Node*node=(Node*)malloc(sizeof(Node));
    node->month=month;
    node->day=day;
    node->next=head->next;
    head->next=node;
}

//尾插添加节点到链表
void addNoderear(linkList*head,int month,int day){
    Node*node=(Node*)malloc(sizeof(Node));
    node->month=month;
    node->day=day;
    node->next=NULL;
    Node*temp=head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=node;
}

//初始化链表
linkList*initlinkList(){
    linkList*head=(linkList*)malloc(sizeof(linkList));
    head->next=NULL;
    return head;
}

//初始化货架
GoodsStack*initGoodsStack(char*name){
    GoodsStack*Goods=(GoodsStack*)malloc(sizeof(GoodsStack));
    strncpy(Goods->name,name,nameSIZE);
    Goods->top=initlinkList();
    Goods->length=0;
    return Goods;
}

//初始化中转队列
tempQueue*inittempQueue(){
    tempQueue*temp=(tempQueue*)malloc(sizeof(tempQueue));
    temp->front=NULL;
    temp->rear=NULL;
    temp->size=0;
    return temp;
}

//判断栈是否为空
int isEmptyStack(GoodsStack*Goods){
    return Goods->length==0;
}

//访问栈顶元素
int*topStack(GoodsStack*Goods){
    int a[2]= {Goods->top->next->month,Goods->top->next->day};
    return a;
}

//出栈操作
void popStack(GoodsStack*Goods){
    if(isEmptyStack(Goods)){
        return;
    }
    Node*temp=Goods->top->next;
    Goods->top->next=temp->next;
    free(temp);
    Goods->length--;
}

//入栈操作
void pushStack(GoodsStack*Goods,int month,int day){
    addNodefront(Goods->top,month,day);
    Goods->length++;
}

//判断队列是否为空
int isEmptyQueue(tempQueue*temp){
    return temp->size==0;
}

//访问队头元素
int*frontQueue(tempQueue*temp){
    int a[2]= {temp->front->month,temp->front->day};
    return a;
}

//出队操作
void popQueue(tempQueue*temp){
    if(isEmptyQueue(temp))return;
    Node*temp1=temp->front;
    temp->front=temp->front->next;
    free(temp1);
    temp->size--;
}

//入队操作
void pushQueue(tempQueue*temp,int month,int day){
    addNoderear(temp->rear,month,day);
    temp->size++;
}

//将商品从货架中取出，并添加到队列中
void fromStackToQueue(GoodsStack*Goods,tempQueue*temp){
    while(!isEmptyStack(Goods)){
        pushQueue(temp,topStack(Goods)[0],topStack(Goods)[1]);
        popStack(Goods);
    }
}

//将商品从队列中取出，并添加到货架中
void fromQueueToStack(tempQueue*temp,GoodsStack*Goods){
    while(!isEmptyQueue(temp)){
        pushStack(Goods,frontQueue(temp)[0],frontQueue(temp)[1]);
        popQueue(temp);
    }
}

//某个货架上货过程
void loadGoods(GoodsStack*Goods,int month,int day,int num){
    tempQueue*temp=inittempQueue();
    fromStackToQueue(Goods,temp);
    for(int i=0;i<num;i++){
        pushQueue(temp,month,day);
    }
    fromQueueToStack(temp,Goods);
    //再次操作保证生产日期早的在栈顶
    fromStackToQueue(Goods,temp);
    fromQueueToStack(temp,Goods);
    free(temp);
}

//主程序
int main(){
    GoodsStack*Goods[GOODSNUM];
    //在主程序中对货架上的货品名称，数量，生产日期进行初始化
}