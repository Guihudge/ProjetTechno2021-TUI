#Makefile game TD02

CC=gcc
CPPFLAGS=
CFLAGS=-std=c99 -Wall
LDFLAGS=-L. -lgame

AR=ar
ARFLAGS=-rcs

all: game_text

game_text: game_text.o libgame.a
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

libgame.a: game.o game_aux.o
	$(AR) $(ARFLAGS) $@ $^

game_aux.o:game_aux.h game_aux.c
	$(CC) $(CFLAGS) -c $^ $(LDFLAGS)

.PHONY: clean

clean:
	rm -rf game_text *.a game_text.o game_aux.o *.gch
