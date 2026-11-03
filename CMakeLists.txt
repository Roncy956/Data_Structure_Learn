cmake_minimum_required(VERSION 3.28)
project(Learn C)

set(CMAKE_C_STANDARD 17)

target_include_directories(Learn PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/00utils
)

add_executable(Learn
        src/chapter01/01_静态线性表.c
        src/chapter01/01_静态线性表.c
        src/chapter01/01_静态线性表.c
        src/chapter01/02_动态线性表.c
        src/chapter01/02_动态线性表.c
        src/00utils/boolean.h
        src/00utils/total.h
        src/00utils/boolean.h
        src/00零基础/指针.c
        "src/chapter01/03_链式存储线性表(BOK课程写法).c"
        src/chapter01/04_链式存储线性表_工业化LNode.c
        src/chapter02/01_栈的顺序表示.c
        src/chapter02/02_栈的链式表示.c
        src/chapter02/02_栈的链式表示.c
        src/chapter02/03_队列_NULL1.c)

