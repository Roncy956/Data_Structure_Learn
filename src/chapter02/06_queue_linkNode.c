//
// Created by Roncy on 2026/11/5.
//
#include "total.h"


/*
 *      链表队列的做法：初始一个next为空的链表结构，front指针与rear指针都指向它，
 * front指针指向的节点的next就是头节点，rear指针指向的节点就是尾节点。
 *
 * 1️⃣
 * front
 *   ↓
 * head → NULL
 *   ↑
 * rear
 * 2️⃣
 * front
 *   ↓
 * head → A → NULL
 *                ↑
 *               rear
 */
// 链表结构
typedef struct LinkNode {
    int data;
    struct LinkNode *next;
} LinkNode;

// 创建链表函数
LinkNode *createLinkNode(int data) {
    LinkNode *linkNode = (LinkNode *) malloc(sizeof(LinkNode));
    if (!linkNode) return NULL;
    linkNode->data = data;
    linkNode->next = NULL;

    return linkNode;
}

// 队列结构
typedef struct QueueLink {
    LinkNode *front;
    LinkNode *rear;
} QueueLink;

// 创建队列函数
QueueLink *createQueueLine() {
    // 申请空间
    QueueLink *queueLink = (QueueLink *) malloc(sizeof(QueueLink));
    if (!queueLink) return NULL;
    // 设置一个链表，将首尾指针都指向它
    LinkNode *linkNode = (LinkNode *) malloc(sizeof(LinkNode));
    if (!linkNode) return NULL;
    queueLink->front = linkNode;
    queueLink->rear = linkNode;

    return queueLink;
}

// 判断队列是否为空
boolean queueIsEmpty(QueueLink *queueLink) {
    // 前后指针相同则为空
    return queueLink->rear == queueLink->front;
}

// 入队列
boolean enQueue(QueueLink *queueLink, int data) {
    LinkNode *linkNode = createLinkNode(data);
    if (!linkNode) return false;

    // 尾指针指向的尾节点的next始终为空，现在将空指针指向新的节点，然后尾指针指向新的节点
    queueLink->rear->next = linkNode;
    queueLink->rear = linkNode;

    return true;
}

// 出队列
boolean deQueue(QueueLink *queueLink, int *data) {
    // 判断队列是否为空
    if (queueIsEmpty(queueLink)) return false;

    LinkNode *tmpLink = queueLink->front->next;
    *data = tmpLink->data;
    queueLink->front->next = tmpLink->next;

    // 如果这时候的尾节点已经是读取的这个链表了
    if (queueLink->rear == tmpLink) {
        // 将头指针直接赋值给尾指针。
        queueLink->rear = queueLink->front;
    }

    free(tmpLink);
    return true;
}

// 读取头
boolean readHead(QueueLink *queueLink, int *data) {
    // 判断队列是否为空
    if (queueIsEmpty(queueLink)) return false;
    *data = queueLink->front->next->data;
    return true;
}

// 销毁队列
void destroyQueue(QueueLink *queueLink){
    LinkNode *curLinkNode = queueLink->front;
    // front指向的node还存在的时候，进while
    while (curLinkNode){
        LinkNode *tmpNode = curLinkNode->next;
        free(curLinkNode);
        curLinkNode = tmpNode;
    }
    // 循环结束，都是空指针了
    queueLink->front=NULL;
    queueLink->rear = NULL;
}

int main() {
    QueueLink *queueLink = createQueueLine();
    if (!queueLink) return 0;

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queueLink));

    // 循环插入20个数字
    for (int i = 0; i < 20; ++i) {
        enQueue(queueLink, i + 1);
    }

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queueLink));

    // 读取头
    int data;
    readHead(queueLink, &data);
    printf("\n");
    printf("Queue head is = %d\n\n", data);

    // 循环取出20个数字
    for (int i = 0; i < 20; ++i) {
        deQueue(queueLink, &data);
        printf("Queue out is = %d\n", data);
    }

    // 判断是否为空
    printf("Queue is empty = %d\n", queueIsEmpty(queueLink));

//    destroyQueue(queueLink);
    return 0;
}
