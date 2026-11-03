//
// Created by Roncy on 2026/11/2.
//
#include <malloc.h>
#include "total.h"

// 数组来实现，牺牲一个数组空间来做队列
typedef struct QueueTag {
    int *data;
    int front;
    int rear;
    int maxSize;
    int len;
} QueueTag;

// 创建队列
QueueTag *createQueue(int size) {
    if (size < 2) return NULL;
    // 先给结构体本身分配内存（原先写的是 nullptr，C 里没有这个关键字，且指针为空不能直接解引用）
    QueueTag *queueTag = (QueueTag *) malloc(sizeof(QueueTag));
    if (!queueTag) return NULL;
    queueTag->data = (int *) malloc(sizeof(int) * size);
    if (!queueTag->data) {
        free(queueTag);
        return NULL;
    }
    queueTag->front = 0; // 头
    queueTag->rear = 0; // 尾
    queueTag->maxSize = size;
    queueTag->len = 0;
    return queueTag;
}

// 判断队列为空，头=尾则为空
boolean queueIsEmpty(QueueTag *queueTag) {
    return queueTag->len == 0;
}

// 入队
boolean enQueue(QueueTag *queueTag, int data) {
    // 头指针加一对最大值取模等于尾指针，则队列满了。模运算优先级高于加减运算
    if (queueTag->len == queueTag->maxSize) return false;
    // 前指针加一取模赋值
    queueTag->front = (queueTag->front + 1) % queueTag->maxSize;
    queueTag->data[queueTag->front] = data;
    return true;
}

// 出队
boolean deQueue(QueueTag *queueTag, int *data) {
    // 如果为空，则返回false
    if (queueIsEmpty(queueTag)) return false;
    *data = queueTag->data[(queueTag->rear + 1) % queueTag->maxSize];
    queueTag->rear = (queueTag->rear + 1) % queueTag->maxSize;
    return true;
}

// 读队列首元素
boolean getHead(QueueTag *queue1, int *data) {
    // 如果为空，返回false
    if (queueIsEmpty(queue1)) return false;
    *data = queue1->data[(queue1->rear + 1) % queue1->maxSize];
    return true;
}

int main() {
    QueueTag *queue1 = createQueue(20);

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