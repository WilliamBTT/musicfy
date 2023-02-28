cmake_minimum_required(VERSION 3.5)

project(outputTerminal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(outputTerminal
    canbus.h
    canbus.cpp
    databasereader.h
    databasereader.cpp
    datareader.h
    datareader.cpp
    main.cpp
    messagedecoder.h
    messagedecoder.cpp)

target_link_libraries(outputTerminal
    PRIVATE pthread
    PRIVATE sqlite3
)

include_directories("../sqlite-autoconf-3390400")

link_directories("../sqlite-autoconf-3390400")
