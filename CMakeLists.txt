cmake_minimum_required(VERSION 3.28)
project(Learn C)

set(CMAKE_C_STANDARD 23)

add_executable(Learn
        src/chapter02/04_queue_tag_flag.c
        src/chapter02/03_queue_null1.c
        src/chapter02/02_stack_linked.c
        src/chapter02/01_stack_sequential.c
        src/00零基础/pointer.c
        src/chapter01/01_static_linear_list.c
        src/chapter01/02_dynamic_linear_list.c
        src/chapter01/03_linked_list_bok_style.c
        src/chapter01/04_linked_list_industrial_lnode.c)

# 公共头文件目录：使 #include "total.h" 可直接使用
# 注意：必须在 add_executable 之后，target 已存在才能设置属性
target_include_directories(Learn PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/00utils
)
