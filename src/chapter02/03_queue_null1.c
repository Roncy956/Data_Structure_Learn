//
// Created by Roncy on 2026/11/2.
//
#include "total.h"

/*
 *      队列，尾进头出，统一先读写再加
 *      为什么尾进头出？想象成排队办理业务，后来的人排到后面去
 * 前面的人办完了就离开队列了，后面的人补上。
 */
// 数组来实现，牺牲一个数组空间来做队列
typedef struct Queue1 {
    int *data;
    int rear;
    int front;
    int maxSize;
} Queue1;

// 创建队列
Queue1 *createQueue(int size) {
    if (size < 2) return NULL;
    // 先给结构体本身分配内存（原先漏了这步，queue1 是空指针，往下赋值必崩）
    Queue1 *queue1 = (Queue1 *) malloc(sizeof(Queue1));
    if (!queue1) return NULL;
    queue1->data = (int *) malloc(sizeof(int) * size);
    if (!queue1->data) {
        free(queue1);
        return NULL;
    }
    queue1->rear = 0; // 尾
    queue1->front = 0; // 头
    queue1->maxSize = size;
    return queue1;
}

// 判断队列为空，头=尾则为空
boolean queueIsEmpty(Queue1 *queue1) {
    return queue1->front == queue1->rear;
}

// 入队
boolean enQueue(Queue1 *queue1, int data) {
    // 尾指针加一对最大值取模，结果等于头指针 front，则队列满（rear+1 撞上 front，说明只剩一个空位）
    // 所以实际最多能存 maxSize-1 个元素，这就是"牺牲一个空间"的代价。
    // 模运算优先级高于加减运算，不加括号会变成 rear + (1 % maxSize)
    if ((queue1->rear + 1) % queue1->maxSize == queue1->front) return false;
    // 尾指针先赋值再+1取模
    queue1->data[queue1->rear] = data;
    queue1->rear = (queue1->rear + 1) % queue1->maxSize;
    return true;
}

// 出队
boolean deQueue(Queue1 *queue1, int *data) {
    if (queueIsEmpty(queue1)) return false;
    // 先把头指针指向的元素读出来，再把头指针加一取模；顺序不能反，反了队头数据就丢了
    *data = queue1->data[queue1->front];
    queue1->front = (queue1->front + 1) % queue1->maxSize;
    return true;
}

// 读队列首元素
boolean getHead(Queue1 *queue1, int *data) {
    if (queueIsEmpty(queue1)) return false;
    *data = queue1->data[(queue1->front) % queue1->maxSize];
    return true;
}

int main() {
    Queue1 *queue1 = createQueue(20);
    if (!queue1) return 0;

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queue1));

    // 入队
    for (int i = 0; i < 10; ++i) {
        enQueue(queue1, i + 1);
    }

    // 读元素但不出队
    int data;
    getHead(queue1, &data);
    printf("Read queue = %d\n", data);

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queue1));

    // 出队
    for (int i = 0; i < 10; ++i) {
        deQueue(queue1, &data);
        printf("Pop queue = %d\n", data);
    }

    free(queue1->data);
    free(queue1);
    return 0;
}