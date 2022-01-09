cmake_minimum_required(VERSION 3.0)

#nom sous projet
project(libgame C)

set(CMAKE_C_FLAGS "-std=c99 -Wall")

#définition des sousrces et headers
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

#création de la lib
add_library(game ${SRCS} ${HEADERS})

#copie la libraire à la racine du projet pour l'éavluateur moodle
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy libgame.a ../
)