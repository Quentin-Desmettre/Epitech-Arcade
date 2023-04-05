##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

INCLUDE_DIRS = -I../../include -I../../include/core -I../../include/games/nibbler -I../../include/libs/ncurses -I../../include/libs/sdl -I../../include/libs/sfml -I../../include/libs/test -I ../../include/games

SRC = \
	Core.cpp \
	LibHandle.cpp \
	LibLoader.cpp \
	main.cpp

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = ../../arcade

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 -fno-gnu-unique -g -lX11

all: try-clean $(NAME)

$(NAME):   $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

try-clean:
	(ls *.gc* > /dev/null 2>&1 && rm -rf $(OBJ) *.gc*) || true

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all

run: 	  all
	./$(NAME)
