//
// Created by Roncy on 2026/11/1.
//
#include <malloc.h>
#include "../00utils/total.h"

// 栈的结构体
typedef struct LinkStack {
    int data;
    struct LinkStack *next;
} LinkStack;

// 栈的初始化
LinkStack *createLinkStack() {
    return NULL;
}

// 入栈
boolean push(LinkStack **linkStack, int data) {
    LinkStack *newStack = (LinkStack *) malloc(sizeof(LinkStack));
    if (!newStack) return false;
    newStack->data = data;
    newStack->next = *linkStack;
    *linkStack = newStack;
    return true;
}

// 出栈
boolean pop(LinkStack **linkStack, int *data) {
    if (!*linkStack) return false;
    *data = (*linkStack)->data;
    // 当前的链表地址暂存一下
    LinkStack *tmpStack = *linkStack;
    // 将当前链表的下一个结构的地址赋值给当前链表
    *linkStack = (*linkStack)->next;
    free(tmpStack);
    return true;
}

boolean readTop(LinkStack **linkStack, int *data) {
    if (!*linkStack) return false;
    *data = (*linkStack)->data;

    return true;
}


int main() {
    LinkStack *linkStack = createLinkStack();

    for (int i = 0; i < 20; ++i) {
        push(&linkStack, i + 1);
    }

    int data;
    readTop(&linkStack, &data);
    printf("Stack Top data=%d\n", data);

    for (int i = 0; i < 20; ++i) {
        pop(&linkStack, &data);
        printf("Stack pop data=%d\n", data);
    }

    return 0;
}

