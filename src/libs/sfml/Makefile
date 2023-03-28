##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

INCLUDE_DIRS = -I../../../include -I../../../include/core -I../../../include/games/nibbler -I../../../include/libs/ncurses -I../../../include/libs/sdl -I../../../include/libs/sfml -I../../../include/libs/test

SOURCEDIR = ./

SRC = \
	utils.cpp \
	sfml.cpp

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = ../../../lib/arcade_sfml.so

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -fPIC -fno-gnu-unique -lX11

all: try-clean $(NAME)

$(NAME):   $(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) -rdynamic -lc $(CXXFLAGS)

try-clean:
	(ls *.gc* > /dev/null 2>&1 && rm -rf $(OBJ) *.gc*) || true

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all

run: 	  all
	./$(NAME)
