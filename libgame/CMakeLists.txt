cmake_minimum_required(VERSION 3.0)

project(libgame)

set(CMAKE_C_FLAGS "-std=c99 -Wall")

set(SRCS
    game_aux.c 
    game.c 
    auxiliars.c 
    game_ext.c
    )

set(HEADERS
    game_aux.h
    game.h
    auxiliars.h
    game_ext.h
    game_struct.h
)

add_library(game ${SRCS} ${HEADERS})