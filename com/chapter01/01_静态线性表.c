//
// Created by Roncy on 2026/10/30.
//

#include <stdio.h>
// 静态线性表
#define MaxSize 50

typedef struct StaticLinearList {
    int data[MaxSize];
    int length;
} StaticLinearList;

StaticLinearList initStaticLinerList() {
    StaticLinearList sll;
    //用循环初始化（更直观）
    for (int i = 0; i < MaxSize; i++) {
        sll.data[i] = 0;  // 初始化为 0，避免垃圾值
    }
    sll.length = 0;  // 空表长度为 0
    return sll;
}

int main() {
    StaticLinearList sll = initStaticLinerList();
    for (int j = 0; j < 20; j++) {
        sll.length++;
        sll.data[j] = j;
    }

    // 此时 length 为 0，不会打印垃圾值
    for (int j = 0; j < sll.length; j++) {
        printf("%d ", sll.data[j]);
    }
    return 0;
}

