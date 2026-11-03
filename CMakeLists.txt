cmake_minimum_required(VERSION 3.28)
project(Learn C)

set(CMAKE_C_STANDARD 17)

target_include_directories(Learn PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/00utils
)

add_executable(Learn
        src/*)

