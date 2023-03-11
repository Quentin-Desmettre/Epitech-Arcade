##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))
INCLUDE_DIRS := $(shell find ../../ -name "*.hpp" -printf '%h\n' | sed 's/ /\\ /g' | sort | uniq | awk '{printf " -I%s", $$0}')

SOURCEDIR_TEST = ./
SOURCEDIR_SRC = ../../src/core/

TMP_SRC = $(call rwildc,$(SOURCEDIR_TEST),*.cpp) $(call rwildc,$(SOURCEDIR_SRC),*.cpp)
SRC = $(filter-out $(call rwildc,$(SOURCEDIR_SRC),main.cpp),$(TMP_SRC))

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = tests_core

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 --coverage -g3

all: clean $(NAME)

$(NAME):   $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete
	find . -name "*~" -delete
	find . -name "\#*" -delete

fclean:    clean
	rm -f $(NAME)

re:        fclean all

run: 	  all
	./$(NAME)
