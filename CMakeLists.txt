cmake_minimum_required(VERSION 3.10)
set(This ChessEngine)
set(ThisLib ChessEngineLib)


project(${This} CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


enable_testing()

add_subdirectory(test)

# include_directories("include")

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

add_executable(${This} ${HEADERS} ${SOURCES})

add_library(${ThisLib} STATIC ${HEADERS} ${SOURCES})
