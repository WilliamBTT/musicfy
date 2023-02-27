cmake_minimum_required(VERSION 3.5)

project(inputTerminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(inputTerminal
    datasender.h
    datasender.cpp
    splitter.h
    splitter.cpp
    messageencoder.h
    messageencoder.cpp
    main.cpp
    ../../outputTerminal/canbus.h
    ../../outputTerminal/canbus.cpp
    )


