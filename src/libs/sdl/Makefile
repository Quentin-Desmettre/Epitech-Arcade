##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))
INCLUDE_DIRS = -I ../../../include/libs -I ../../../include/

SOURCEDIR = ./

SRC = $(call rwildc,$(SOURCEDIR),*.cpp)

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = ../../../lib/arcade_sdl2.so

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -fPIC -g  -fno-gnu-unique -g

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
