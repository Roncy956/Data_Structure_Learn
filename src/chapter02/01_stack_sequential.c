//
// Created by Roncy on 2026/11/1.
//
#include "total.h"
/*
 * 栈的指针可以选择初始化的时候指向-1或者0,
 */
// 定义结构体
typedef struct Stack {
    int maxSize;
    int *data;
    int top;
} Stack;

// 栈的初始化
boolean initStack(Stack *stack, int maxSize) {
    if (maxSize < 1) return false;
    stack->maxSize = maxSize;
    stack->data = (int *) malloc(sizeof(int) * maxSize);
    if (!stack->data) return false;
    stack->top = -1;
    return true;
}

// 判断是否为空
boolean stackIsEmpty(Stack *stack) {
    return stack->top == -1;
}

// 入栈操作
boolean push(Stack *stack, int data) {
    if (stack->top == stack->maxSize - 1) return false;
    stack->top++;
    stack->data[stack->top] = data;
    return true;
}

// 出栈操作
boolean pop(Stack *stack, int *data) {
    if (stack->top == -1) return false;
    *data = stack->data[stack->top];
    stack->top--;
    return true;
}

// 读栈顶元素但不出栈
boolean readTop(Stack *stack, int *data) {
    if (stack->top == -1) return false;
    *data = stack->data[stack->top];
    return true;
}

// 销毁栈
boolean destroyStack(Stack *stack) {
    free(stack->data);
    return true;
}

int main() {
    Stack stack;
    // 初始化
    initStack(&stack, 50);

    // 判断是否为空
    printf("is Empty=%d\n", stackIsEmpty(&stack));

    // 入栈
    for (int i = 0; i < 20; ++i) {
        push(&stack, i + 1);
    }

    printf("is Empty=%d\n", stackIsEmpty(&stack));

    // 读栈顶元素
    int data;
    readTop(&stack, &data);
    printf("Stack top data=%d\n\n", data);

    // 出栈
    for (int i = 0; i < 20; ++i) {
        pop(&stack, &data);
        printf("Stack pop data=%d\n", data);
    }

    // 销毁
    destroyStack(&stack);

    return 0;
}