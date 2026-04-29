cmake_minimum_required(VERSION 3.20)

project(standupc)

set(CMAKE_CXX_STANDARD 20)

set (COMPILATION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/compilation)

add_executable(standupc
    src/main.cpp
)

target_include_directories(standupc PRIVATE
    ${COMPILATION_DIR}/lexer
)