##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

INCLUDE_DIRS = -I../../../include -I../../../include/core -I../../../include/games/ -I../../../include/games/nibbler -I../../../include/libs/ncurses -I../../../include/libs/sdl -I../../../include/libs/sfml -I../../../include/libs/test

SRC = test.cpp

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = ../../../tests/test_interface.so

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -fPIC -fno-gnu-unique -g

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
