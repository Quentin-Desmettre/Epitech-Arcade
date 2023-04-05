##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

INCLUDE_DIRS = -I../../../include -I../../../include/core -I../../../include/games/ -I../../../include/games/nibbler -I../../../include/libs/ncurses -I../../../include/libs/sdl -I../../../include/libs/sfml -I../../../include/libs/test

SOURCEDIR = ./

SRC = Centipede.cpp \
	Entity.cpp \
	GameData.cpp \
	Snake.cpp

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = ../../../lib/arcade_centipede.so

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 -fPIC

all: try-clean $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -shared -o $(NAME) $(OBJ) -rdynamic -lc

try-clean:
	(ls *.gc* > /dev/null 2>&1 && rm -rf $(OBJ) *.gc*) || true

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)
