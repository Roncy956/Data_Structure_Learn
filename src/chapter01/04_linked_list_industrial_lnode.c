//
// Created by Roncy on 2026/11/1.
//
#include "total.h"

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode;

// 申请新的LNode，返回的是指针。
LNode *createLNode(int data) {
    LNode *newLNode = (LNode *) malloc(sizeof(LNode));
    if (!newLNode) return NULL;
    newLNode->data = data;
    newLNode->next = NULL;
    return newLNode;
}

// 链表结构体，
typedef struct LinkList {
    LNode *head;
    LNode *tail;
    int len;
} LinkList;

// 创建链表函数
LinkList createLinkList() {
    LinkList linkList;
    // 申请第一个节点，使头尾节点都指向它。
    LNode *firNode = createLNode(0);
    firNode->next = NULL;
    linkList.head = firNode;
    linkList.tail = firNode;
    linkList.len = 0;
    return linkList;
}

// 遍历打印
void printList(LinkList *linkList) {
    LNode *cur = linkList->head->next;
    for (int i = 0; i < linkList->len; ++i) {
        printf("Node[%d]=%d\n", i + 1, cur->data);
        cur = cur->next;
    }
}

// 释放链表空间函数
boolean freeLinkList(LinkList *linkList) {
    if (!linkList) return false;
    LNode *curr = linkList->head;
    // 循环释放掉所有的node
    while (curr) {
        LNode *tmp = curr->next;
        free(curr);
        curr = tmp;
    }
    return true;
}

// 头插入
boolean linkListInsertHead(LinkList *linkList, int data) {
    // 判断是否为空
    if (!linkList) return false;
    // 调用函数创建一个node并判断是否为空
    LNode *newNode = createLNode(data);
    if (!newNode) {
        free(newNode);
        return false;
    }
    // 原头节点的下一个节点接到新节点的next
    newNode->next = linkList->head->next;
    linkList->head->next = newNode;
    // 如果是第一个真实节点，更新尾指针
    if (linkList->head == linkList->tail) {
        linkList->tail = newNode;
    }
    linkList->len++;
    return true;
}

// 尾插入
boolean linkListInsertTail(LinkList *linkList, int data) {
    // 判断是否为空
    if (!linkList) return false;
    // 调用函数创建一个node
    LNode *newNode = createLNode(data);
    if (!newNode) {
        free(newNode);
        return false;
    }
    // 打开将新的node添加到尾节点的next上
    linkList->tail->next = newNode;
    // 如果新节点是第一个节点，增加到头节点的next上
    if (linkList->head == linkList->tail) {
        linkList->head->next = newNode;
    }
    linkList->tail = newNode;
    linkList->len++;

    return true;
}

// 按序查找
LNode *getElemByIndex(LinkList *linkList, int index) {
    if (index < 1 || index > linkList->len) return NULL;
    LNode *curNode = linkList->head;
    for (int i = 0; i < index; ++i) {
        curNode = curNode->next;
    }
    return curNode;
}

// 插入，从某个序号插入，插在当前序号的前面
boolean linkListInsert(LinkList *linkList, int index, int data) {
    if (index < 1 || index > linkList->len) return false;
    // 拿到头节点
    LNode *curNode = linkList->head;
    // 让这个node遍历到index的前一个节点。
    for (int i = 0; i < index - 1; ++i) {
        curNode = curNode->next;
    }
    // 创建一个新的节点
    LNode *newNode = createLNode(data);
    if (!newNode) {
        free(newNode);
        return false;
    }
    // 将index前一个节点的
    LNode *tmp = curNode->next;
    curNode->next = newNode;
    newNode->next = tmp;
    // 自增长度
    linkList->len++;
    return true;
}

// 删除某个序号的内容
boolean linkListDelete(LinkList *linkList, int index) {
    if (index < 1 || index > linkList->len) return false;
    // 拿到头节点
    LNode *curNode = linkList->head;
    // 让这个node遍历到index的前一个节点。
    for (int i = 0; i < index - 1; ++i) {
        curNode = curNode->next;
    }
    free(curNode->next);
    // 将index前一个节点的接到后一个节点去
    curNode->next = curNode->next->next;
    // 自减长度
    linkList->len--;
    return true;
}


int main() {
    LinkList linkList = createLinkList();

    // 插入1-20个数 头插入
    for (int i = 0; i < 10; ++i) {
        linkListInsertHead(&linkList, i + 1);
    }

    // 插入20个数 尾插入
    for (int i = 0; i < 10; i++) {
        linkListInsertTail(&linkList, i + 101);
    }

    printList(&linkList);

    // 获取链表长度
    printf("len=%d\n", linkList.len);

    // 按序查找
    LNode *aim = getElemByIndex(&linkList, 15);
    printf("nodeIndex=15: %d\n", aim->data);

    // 插入
    linkListInsert(&linkList, 12, 666);
    printList(&linkList);

    // 删除
    linkListDelete(&linkList, 12);
    printList(&linkList);


    freeLinkList(&linkList);
    return 0;
}

