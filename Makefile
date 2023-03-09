##
## EPITECH PROJECT, 2023
## helloworld
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))

SOURCEDIR = src

SRC = $(call rwildc,$(SOURCEDIR),*.cpp)

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = arcade

CXXFLAGS = -Wall -Wextra -I ./include -std=c++20

all: $(NAME)

$(NAME):   $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CXXFLAGS)

tests_run:
	cd tests && make && ./tests

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete
	find . -name "*~" -delete
	find . -name "\#*" -delete

fclean:    clean
	rm -f $(NAME)

re:        fclean all
