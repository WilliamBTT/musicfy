cmake_minimum_required(VERSION 3.5)

project(outputTerminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(outputTerminal
    main.cpp)

target_link_libraries(outputTerminal
    PRIVATE pthread
)
