//
// Created by Roncy on 2026/10/31.
//
#include <malloc.h>
#include "../00utils/total.h"

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;
// 这里LinkList p 等价于 LNode *p;

// 创建链表，这里创建的是头结点，没有数值，返回的是一个地址，这个地址指向链表的头节点
LNode *createNode() {
    LNode *lNode;
    lNode = (LNode *) malloc(sizeof(LNode));
    if (!lNode) return NULL;
    (*lNode).next = NULL;
    return lNode;
}

// 获取一个新的节点，值为e
LNode *getNewNode(int e) {
    LNode *lNode;
    lNode = (LNode *) malloc(sizeof(LNode));
    if (!lNode) return NULL;
    (*lNode).data = e;
    (*lNode).next = NULL;
    return lNode;
}

// 释放整个链表
void freeNode(LNode *lNode) {
    LNode *curr = (*lNode).next;
    while (curr) {
        LNode *tmp = curr;
        curr = (*curr).next;
        free(tmp);
    }
    free(lNode);
}

/*
 * 链表初始化
 *
 * 为什么这里要传入二重指针？
 *      C语言的所有传递是值传递，不会更改原来的值，而我们操作LNode是用指针去找到地址然后去操作的，
 * 也就是说，C语言这里如果传递LNode *lNode，那么这是与main中不同地址但值相同的变量，这些变量的值
 * 指向同一个主存空间，如果在这个函数中更改了地方，主存中的那个指针存的值并不会更改，所以这里应该
 * 传二重指针，指向main中的那个指针，才能更改main中指针指向的位置。
 *
 * 注意：这里**lNode是直接指向链表，能直接通过它来操作链表
 *          *lNode是指针里存的值，也就是链表的地址
 *          都是通过指针来更改的，与main同步
 *
 * 想改变 LNode 里的数据 -> 传 LNode *（指过去直接改）。
 * 想改变 LNode * 的指向（比如 malloc 新节点） -> 传 LNode **（取指针的地址，解引用后改）。
 */
boolean initNode(LNode **lNode) {
    // malloc 在堆区分配一块内存，并返回这块内存的首地址。
    // 将这个首地址赋值给 *lNode（即 main 函数里的 lNode 指针）。
    *lNode = (LNode *) malloc(sizeof(LNode));
    if (!*lNode) return false;
    (**lNode).next = NULL; //通过双重地址找到node的位置，然后设置next节点为null
    return true;
}

// 获取节点长度
// 直接传指针(地址)
int nodeLength(LNode *lNode) {
    int len = 0;
    LNode *tmpNode = lNode;
    // 下一个节点还有的话，循环继续
    while ((*tmpNode).next) {
        // len自增，tmpNode指向下一个
        len++;
        tmpNode = (*tmpNode).next;
    }
    return len;
}

// 插入，头插
boolean lNodeInsert_Head(LNode *lNode, int e) {
    if (!lNode) return false;
    LNode *tmpNode = (*lNode).next;
    // 拿到初始节点的下一个节点
    LNode *newNode = getNewNode(e);
    (*lNode).next = newNode;
    (*newNode).next = tmpNode;
    return true;
}

int main() {
    // 这里定义了一个地址，但这个地址位置并没有添加东西。
    LNode *lNode;
    // 传入存放这个node地址的地址。
    initNode(&lNode);
    // 循环插入20个节点
    for (int i = 0; i < 20; ++i) {
        lNodeInsert_Head(lNode, i + 1);
    }

    printf("%d\n", nodeLength(lNode));
    freeNode(lNode);
    return 0;
}