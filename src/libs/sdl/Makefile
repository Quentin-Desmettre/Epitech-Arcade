##
## EPITECH PROJECT, 2023
## arcade
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))
INCLUDE_DIRS := $(shell find ../../../ -name "*.hpp" -printf '%h\n' | sed 's/ /\\ /g' | sort | uniq | awk '{printf " -I%s", $$0}')

SOURCEDIR = ./

SRC = $(call rwildc,$(SOURCEDIR),*.cpp)

CXX = g++

OBJ = $(SRC:.cpp=.o)

NAME = ../../../lib/arcade_sdl2.so

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: try-clean $(NAME)

$(NAME):   $(OBJ)
	ld -fPIC -shared -o $(NAME) $(OBJ)

try-clean:
	(ls *.gc* > /dev/null 2>&1 && rm -rf $(OBJ) *.gc*) || true

clean:
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)

re:        fclean all

run: 	  all
	./$(NAME)
