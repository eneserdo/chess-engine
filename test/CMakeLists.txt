cmake_minimum_required(VERSION 3.10)
set(This ChessEngineTests)

project(${This} CXX)

set(SOURCES
    tests.cpp
    )

add_executable(${This} ${SOURCES})

target_link_libraries(${This} PUBLIC
    gtest
    pthread
    ChessEngineLib
    )


add_test(NAME ${This} COMMAND ${This})