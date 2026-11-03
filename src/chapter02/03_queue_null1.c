//
// Created by Roncy on 2026/11/2.
//
#include <malloc.h>
#include "total.h"

// 数组来实现，牺牲一个数组空间来做队列
typedef struct Queue1 {
    int *data;
    int front;
    int rear;
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
    queue1->front = 0; // 头
    queue1->rear = 0; // 尾
    queue1->maxSize = size;
    return queue1;
}

// 判断队列为空，头=尾则为空
boolean queueIsEmpty(Queue1 *queue1) {
    return queue1->rear == queue1->front;
}

// 入队
boolean enQueue(Queue1 *queue1, int data) {
    // 头指针加一对最大值取模等于尾指针，则队列满了。模运算优先级高于加减运算
    if ((queue1->front + 1) % queue1->maxSize == queue1->rear) return false;
    // 前指针加一取模赋值
    queue1->front = (queue1->front + 1) % queue1->maxSize;
    queue1->data[queue1->front] = data;
    return true;
}

// 出队
boolean deQueue(Queue1 *queue1, int *data) {
    if (queueIsEmpty(queue1)) return false;
    *data = queue1->data[(queue1->rear + 1) % queue1->maxSize];
    queue1->rear = (queue1->rear + 1) % queue1->maxSize;
    return true;
}

// 读队列首元素
boolean getHead(Queue1 *queue1, int *data) {
    if (queueIsEmpty(queue1)) return false;
    *data = queue1->data[(queue1->rear + 1) % queue1->maxSize];
    return true;
}

int main() {
    Queue1 *queue1 = createQueue(20);

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