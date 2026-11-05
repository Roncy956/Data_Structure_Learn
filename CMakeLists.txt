cmake_minimum_required(VERSION 3.28)
project(Learn C)

set(CMAKE_C_STANDARD 17)

# 公共头文件目录：使任意源文件都能直接 #include "total.h"
set(LEARN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/00utils)

# 自动收集 src 下所有 .c（CONFIGURE_DEPENDS：新增/删除文件时自动重新配置）
file(GLOB_RECURSE LEARN_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# 每个 .c 各自生成一个独立可执行文件。
# 这些是练习程序，每个都带 main() 且有同名函数（push/pop/createQueue...），
# 绝不能编进同一个 target，否则链接期报 multiple definition。
foreach(src ${LEARN_SOURCES})
    # 跳过没有 main 的文件（例如尚未动笔的 05_queue_len.c），否则链接必失败
    file(READ ${src} _content)
    if (NOT _content MATCHES "main[ \t]*\\(")
        message(STATUS "跳过（无 main，不生成可执行文件）: ${src}")
        continue()
    endif()

    # target 名 = 目录名_文件名，避免不同章的同名文件冲突
    get_filename_component(_name ${src} NAME_WE)
    get_filename_component(_dir ${src} DIRECTORY)
    get_filename_component(_dirname ${_dir} NAME)

    add_executable(${_dirname}_${_name} ${src})
    target_include_directories(${_dirname}_${_name} PRIVATE ${LEARN_INCLUDE_DIR})
endforeach()
