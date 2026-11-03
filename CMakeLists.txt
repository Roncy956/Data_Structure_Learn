cmake_minimum_required(VERSION 3.28)
project(Learn C)

set(CMAKE_C_STANDARD 17)

target_include_directories(Learn PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/com/00utils
)

add_executable(Learn
        com/chapter01/01_静态线性表.c
        com/chapter01/01_静态线性表.c
        com/chapter01/01_静态线性表.c
        com/chapter01/02_动态线性表.c
        com/chapter01/02_动态线性表.c
        com/00utils/boolean.h
        com/00utils/total.h
        com/00utils/boolean.h
        com/00零基础/指针.c
        "com/chapter01/03_链式存储线性表(BOK课程写法).c"
        com/chapter01/04_链式存储线性表_工业化LNode.c
        com/chapter02/01_栈的顺序表示.c
        com/chapter02/02_栈的链式表示.c
        com/chapter02/02_栈的链式表示.c
        com/chapter02/03_队列_NULL1.c)

