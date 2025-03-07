#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define dataSIZE 100

//定义链表节点
typedef struct Node{
    char data[dataSIZE];
    struct Node*next;
}Node;

//顺序栈定义
typedef struct Stack{
    char**data;//存放栈元素的数组
    int top;//栈顶指针
    int size;//栈的容量
}Stack;

//链队列定义
typedef struct Queue{
    Node*front;//队头指针
    Node*rear;//队尾指针
    int count;//队列元素个数
}Queue;

//链队列模拟便道
typedef struct Sidewalk{
    Queue*queue;//队列指针
}Sidewalk;

//顺序栈模拟停车场
typedef struct Parking{
    float*timein;//进入时间
    int size;//停车场容量
    int prizeperhour;//每小时停车费
    Stack*stack;//栈指针
    Sidewalk*sidewalk;//便道指针
}Parking;

//队列添加节点
void addQueueNode(Queue*queue,char data[dataSIZE]){
    Node*node=(Node*)malloc(sizeof(Node));
    strcpy(node->data,data);
    node->next=NULL;
    if(queue->front==NULL){
        queue->front=node;
        queue->rear=node;
    }
    else{
        queue->rear->next=node;
        queue->rear=node;
    }
    queue->count++;
}

//初始化顺序栈
void initStack(Stack*stack,int size){
    stack->data=(char**)malloc(sizeof(char*)*size);
    for(int i=0;i<size;i++){
        stack->data[i]=(char*)malloc(sizeof(char)*dataSIZE);//每个元素最多100个字符
    }
    stack->top=-1;
    stack->size=size;
}

//入栈操作
void addStack(Stack*stack,char data[dataSIZE]){
    stack->top++;
    strcpy(stack->data[stack->top],data);
}

//出栈操作
void popStack(Stack*stack){
    stack->top--;//将栈顶指针下移
}

//获取栈顶元素
char*topStack(Stack*stack){
    return stack->data[stack->top];//返回栈顶元素
}

//初始化队列
void initQueue(Queue*queue){
    queue->front=NULL;
    queue->rear=NULL;
    queue->count=0;
}

//出队操作
char* popQueue(Queue*queue){
    Node*node=queue->front;
    char*data=node->data;
    queue->front=node->next;
    free(node);
    queue->count--;
    return data;
}

//初始化便道
void initSidewalk(Sidewalk*sidewalk){
    sidewalk->queue=(Queue*)malloc(sizeof(Queue));
    initQueue(sidewalk->queue);
}

//初始化停车场
void initParking(Parking*parking,int size,int prizeperhour){
    parking->size=size;
    parking->prizeperhour=prizeperhour;
    initStack(parking->stack,size);
    initSidewalk(parking->sidewalk);
    parking->timein=(float*)malloc(sizeof(float)*size);//初始化进入时间数组
}

//添加车辆到便道
void addCarToSidewalk(Sidewalk*sidewalk,char*car){
    addQueueNode(sidewalk->queue,car);
}

//判断停车场是否已满
int isFullParking(Parking*parking){
    if(parking->stack->top==parking->size-1){
        return 1;
    }
    return 0;
}

//安全的输入函数
void ffgets(char*str,int n){
    fgets(str,n,stdin);
    str[strcspn(str, "\n")] = '\0';//将换行符替换为字符串结束符
}

//停车场进入操作
int carPark(Parking*parking){
    char*car=(char*)malloc(sizeof(char)*dataSIZE);
    printf("请输入车牌号：\n");
    ffgets(car,dataSIZE);
    if(isFullParking(parking)){
        printf("停车场已满，请到便道等待\n");
        addCarToSidewalk(parking->sidewalk,car);
        return parking->sidewalk->queue->count;
    }
    else{
        printf("请输入进入时间：\n");
        float timein;
        scanf("%f",&timein);
        addStack(parking->stack,car);
        parking->timein[parking->stack->top]=timein;
        printf("停车成功\n");
        return parking->stack->top+1;
    }
    
}

//停车场离开操作
void carLeave(Parking*parking){
    char*car=(char*)malloc(sizeof(char)*dataSIZE);
    printf("请输入车牌号：\n");
    ffgets(car,dataSIZE);
    //建立临时停车场
    Parking tempParking;
    initParking(&tempParking,parking->size,parking->prizeperhour);
    //将停车场中的车辆移到临时停车场
    while(strcmp(topStack(parking->stack), car) != 0){
        addStack(&tempParking.stack,topStack(parking->stack));
        popStack(parking->stack);
    }
    if(parking->stack->top==-1){
        //说明不存在该车辆
        printf("不存在该车辆\n");
        //将临时停车场的车辆移回停车场
        while(tempParking.stack->top!=-1){
            addStack(parking->stack,topStack(&tempParking.stack));
            popStack(&tempParking.stack);
        }
        free(car);
        return;
    }
    else{
        //存在该车辆
        printf("输入离开时间：\n");
        float timeout;
        scanf("%f",&timeout);
        float timein=parking->timein[parking->stack->top];
        float time=timeout-timein;
        float prize=time*(parking->prizeperhour);
        printf("停车时间为%f小时，停车费用为%f元\n",time,prize);
        popStack(parking->stack);
        //将临时停车场的车辆移回停车场
        while(tempParking.stack->top!=-1){
            addStack(parking->stack,topStack(&tempParking.stack));
            popStack(&tempParking.stack);
        }

        //如果便道上有车辆，则将便道上第一个移入停车场
        if(parking->sidewalk->queue->count!=0){
            addStack(parking->stack,parking->sidewalk->queue->front->data);
            popQueue(parking->sidewalk->queue);
            parking->timein[parking->stack->top]=timeout;
        }
        free(car);
        return;
    }
}

int main(){
    Parking parking;
    printf("请输入停车场大小：\n");
    int size;
    scanf("%d",&size);
    printf("请输入停车费每小时：\n");
    float prizeperhour;
    scanf("%f",&prizeperhour);
    initParking(&parking,size,prizeperhour);
    while(1){
        printf("请输入操作：1.停车 2.离开 3.查看停车场 4.查看便道 5.退出\n");
        int choice;
        scanf("%d",&choice);
        switch(choice){
            case 1:
                carPark(&parking);
                break;
            case 2:
                carLeave(&parking);
                break;
            case 3:
                printf("停车场中车辆数量为%d\n",topStack(parking.stack->data));
                break;
            case 4:
                printf("便道中车辆数量为%d\n",parking.sidewalk->queue->count);
                break;
            case 5:
                return 0;
            default:
                printf("输入错误\n");
                break;
        }

    }
    return 0;
}
