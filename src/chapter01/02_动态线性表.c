//
// Created by Roncy on 2026/10/31.
//
#include <malloc.h>
#include "../00utils/total.h"

//动态线性表
typedef struct DynLinearList {
    int *elem;
    int length;
    int capacity;
} DynLinearList;

// 初始化函数
boolean initDynLinearList(DynLinearList *dll, int initSize) {
    // 直接用malloc函数来申请一大块内存。其实与int a[10]有相似之处。
    (*dll).elem = (int *) malloc(sizeof((*dll).elem) * initSize);
    // 健壮性检测
    if (!(*dll).elem) {
        return false;
    }
    // 容量赋值
    (*dll).capacity = initSize;
    (*dll).length = 0;
    // 将分配的一整块都赋值为0
    for (int i = 0; i < (*dll).capacity; ++i) {
        (*dll).elem[i] = 0;
    }
    return true;
}

// 遍历
void printList(DynLinearList dll){
    for (int i = 0; i < dll.length; ++i) {
        printf("dll.elem[%d]=%d\n", i, dll.elem[i]);
    }
}

// 取值，给的index是序列号
boolean getElem(DynLinearList dll, int index, int *elem) {
    if (index < 1 || index > dll.length) {
        return false;
    }
    *elem = dll.elem[index - 1];
    return true;
}

// 按值查找，如果找到了，返回的是序列号，返回0则为失败
int locateElem(DynLinearList dll, int e) {
    for (int i = 0; i < dll.length; ++i) {
        if (dll.elem[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

// 插入 index是序列号
boolean listInsert(DynLinearList *dll, int index, int e) {
    if (index < 1 || index > (*dll).length) {
        return false;
    }
    for (int j = (*dll).length; j >= index; j--) {
        (*dll).elem[j] = (*dll).elem[j - 1];
    }
    (*dll).elem[index - 1] = e;
    (*dll).length++;
    return true;
}

// 删除
boolean listDelete(DynLinearList *dll, int index) {
    if (index < 1 || index > (*dll).length) {
        return false;
    }
    for (int i = index - 1; i < (*dll).length - 1; ++i) {
        (*dll).elem[i] = (*dll).elem[i + 1];
    }
    (*dll).length--;
    return true;
}


int main() {
    // 创建、初始化与赋值
    DynLinearList dll;
    initDynLinearList(&dll, 100);
    for (int i = 0; i < 50; ++i) {
        dll.elem[i] = i + 1;
        dll.length++;
    }

    // 取数
    int elem = 0;
    int index = 6; // 序列号，不是下标
    if (getElem(dll, index, &elem)) {
        printf("%d\n", elem);
    }

    // 按值查找
    elem = 20;
    printf("locate Index = %d\n", locateElem(dll,elem));

    // 插入
    index = 9; // 序列号
    elem = 100;
    listInsert(&dll, index, elem);
    printList(dll);
    printf("\n");

    // 删除，index是序列号
    listDelete(&dll, index);
    printList(dll);

    return 0;
}