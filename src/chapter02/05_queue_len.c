//
// Created by Roncy on 2026/11/2.
//
#include "total.h"

// 数组来实现，牺牲一个数组空间来做队列
typedef struct QueueLen {
    int *data;
    int front;
    int rear;
    int maxSize;
    int len;
} QueueLen;

// 创建队列
QueueLen *createQueue(int size) {
    if (size < 2) return NULL;
    // 先给结构体本身分配内存（原先写的是 nullptr，C 里没有这个关键字，且指针为空不能直接解引用）
    QueueLen *queueLen = (QueueLen *) malloc(sizeof(QueueLen));
    if (!queueLen) return NULL;
    queueLen->data = (int *) malloc(sizeof(int) * size);
    if (!queueLen->data) {
        free(queueLen);
        return NULL;
    }
    queueLen->front = 0; // 头
    queueLen->rear = 0; // 尾
    queueLen->maxSize = size;
    queueLen->len = 0;
    return queueLen;
}

// 判断队列为空，头=尾则为空
boolean queueIsEmpty(QueueLen *queueLen) {
    return queueLen->len == 0;
}

// 入队
boolean enQueue(QueueLen *queueLen, int data) {
    // 头指针加一对最大值取模等于尾指针，则队列满了。模运算优先级高于加减运算
    // 看看有没有满队列，长度=maxSize
    if (queueLen->len == queueLen->maxSize) return false;
    // 前指针加一取模赋值
    queueLen->data[queueLen->front] = data;
    queueLen->front = (queueLen->front + 1) % queueLen->maxSize;

    queueLen->len++;   // 关键：入队后长度必须 +1，否则判空/判满全失效
    return true;
}

// 出队
boolean deQueue(QueueLen *queueLen, int *data) {
    // 如果为空，则返回false
    if (queueIsEmpty(queueLen)) return false;
    *data = queueLen->data[queueLen->rear];
    queueLen->rear = (queueLen->rear + 1) % queueLen->maxSize;
    queueLen->len--;   // 关键：出队后长度必须 -1
    return true;
}

// 读队列首元素
boolean getHead(QueueLen *queueLen, int *data) {
    // 如果为空，返回false
    if (queueIsEmpty(queueLen)) return false;
    *data = queueLen->data[(queueLen->rear + 1) % queueLen->maxSize];
    return true;
}

int main() {
    QueueLen *queueLen = createQueue(10);
    if(!queueLen) return 0;

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queueLen));

    // 入队
    for (int i = 0; i < 10; ++i) {
        enQueue(queueLen, i + 1);
    }

    // 读元素但不出队
    int data;
    getHead(queueLen, &data);
    printf("Read queue = %d\n", data);

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queueLen));

    // 出队
    for (int i = 0; i < 10; ++i) {
        deQueue(queueLen, &data);
        printf("Pop queue = %d\n", data);
    }

    free(queueLen->data);
    free(queueLen);
    return 0;
}