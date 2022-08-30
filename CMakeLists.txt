project(Mastermind)

set(CMAKE_CXX_STANDARD 17)

set(NAME Mastermind)

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(SOURCES
    main.cpp
    Game.cpp
)

set(HEADERS
    Game.h
)

add_executable(${NAME} ${SOURCES} ${HEADERS})