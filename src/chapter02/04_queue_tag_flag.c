//
// Created by Roncy on 2026/11/2.
//
#include "total.h"

// 数组来实现，通过一个tag标签来判断空队列和满队列
typedef struct QueueTag {
    int *data;
    int front;
    int rear;
    int maxSize;
    // 初始为true，入队列操作变为false，出队列操作变为true
    boolean isOut;
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
    queueTag->isOut = true;
    return queueTag;
}

// 判断队列为空，头=尾则为空
boolean queueIsEmpty(QueueTag *queueTag) {
    return queueTag->front == queueTag->rear && queueTag->isOut;
}

// 入队
boolean enQueue(QueueTag *queueTag, int data) {
    // 两指针相同且tag不为false
    if (queueTag->front == queueTag->rear && !queueTag->isOut) return false;
    // 指针加一取模
    queueTag->data[queueTag->front] = data;
    queueTag->front = (queueTag->front + 1) % queueTag->maxSize;

    // 添加了元素，tag就不为false了
    queueTag->isOut = false;

    return true;
}

// 出队
boolean deQueue(QueueTag *queueTag, int *data) {
    // 如果为空，则返回false
    if (queueIsEmpty(queueTag)) return false;
    // 先出队再加一
    *data = queueTag->data[queueTag->rear];
    queueTag->rear = ((queueTag->rear + 1) % queueTag->maxSize);


    // 出队了，isOut改为true；
    queueTag->isOut = true;

    return true;
}

// 读队列首元素
boolean getHead(QueueTag *queueTag, int *data) {
    // 如果为空，返回false
    if (queueIsEmpty(queueTag)) return false;
    *data = queueTag->data[queueTag->rear];
    return true;
}

int main() {
    QueueTag *queueTag = createQueue(20);
    if (!queueTag) return false;

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queueTag));

    // 入队
    for (int i = 0; i < 10; ++i) {
        enQueue(queueTag, i + 1);
    }

    // 读元素但不出队
    int data;
    getHead(queueTag, &data);
    printf("Read queue = %d\n", data);

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queueTag));

    // 出队
    for (int i = 0; i < 10; ++i) {
        deQueue(queueTag, &data);
        printf("Pop queue = %d\n", data);
    }

    free(queueTag->data);
    free(queueTag);
    return 0;
}