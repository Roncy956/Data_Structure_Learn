//
// Created by Roncy on 2026/11/2.
//
#include "total.h"

// 数组来实现，用 len 记录元素个数来区分队空和队满
// 好处：maxSize 个空间全部能用，不像"牺牲一个单元"那样必须空一格
typedef struct QueueLen {
    int *data;
    int rear;
    int front;
    int maxSize;
    int len;
} QueueLen;

// 创建队列
QueueLen *createQueue(int size) {
    if (size < 1) return NULL;
    // 先给结构体本身分配内存（原先写的是 nullptr，C 里没有这个关键字，且指针为空不能直接解引用）
    QueueLen *queueLen = (QueueLen *) malloc(sizeof(QueueLen));
    if (!queueLen) return NULL;
    queueLen->data = (int *) malloc(sizeof(int) * size);
    if (!queueLen->data) {
        free(queueLen);
        return NULL;
    }
    queueLen->rear = 0; // 尾
    queueLen->front = 0; // 头
    queueLen->maxSize = size;
    queueLen->len = 0;
    return queueLen;
}

// 判断队列为空：len == 0
boolean queueIsEmpty(QueueLen *queueLen) {
    return queueLen->len == 0;
}

// 入队
boolean enQueue(QueueLen *queueLen, int data) {
    // 判满：len == maxSize
    if (queueLen->len == queueLen->maxSize) return false;
    // 先写入 rear 位置，再把尾指针加一取模赋值
    queueLen->data[queueLen->rear] = data;
    queueLen->rear = (queueLen->rear + 1) % queueLen->maxSize;

    queueLen->len++;   // 关键：入队后长度必须 +1，否则判空/判满全失效
    return true;
}

// 出队
boolean deQueue(QueueLen *queueLen, int *data) {
    // 如果为空，则返回false
    if (queueIsEmpty(queueLen)) return false;
    *data = queueLen->data[queueLen->front];
    queueLen->front = (queueLen->front + 1) % queueLen->maxSize;
    queueLen->len--;   // 关键：出队后长度必须 -1
    return true;
}

// 读队列首元素
boolean getHead(QueueLen *queueLen, int *data) {
    // 如果为空，返回false
    if (queueIsEmpty(queueLen)) return false;
    *data = queueLen->data[queueLen->front];
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