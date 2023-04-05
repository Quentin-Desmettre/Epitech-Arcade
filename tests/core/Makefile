##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))
INCLUDE_DIRS = -I../../../include -I../../../include/core -I../../../include/games/ -I../../../include/games/nibbler -I../../../include/libs/ncurses -I../../../include/libs/sdl -I../../../include/libs/sfml -I../../../include/libs/test

SOURCEDIR_TEST = ./
SOURCEDIR_SRC = ../../src/core/

TMP_SRC = $(call rwildc,$(SOURCEDIR_TEST),*.cpp) $(call rwildc,$(SOURCEDIR_SRC),*.cpp)
SRC = $(filter-out $(call rwildc,$(SOURCEDIR_SRC),main.cpp),$(TMP_SRC))

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = tests_core

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 --coverage -g

all:
	echo 'done!'

$(NAME):   $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all

run: 	  all
	./$(NAME)
