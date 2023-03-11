##
## EPITECH PROJECT, 2023
## helloworld
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))
INCLUDE_DIRS := $(shell find ./include/ -name "*.hpp" -printf '%h\n' | sed 's/ /\\ /g' | sort | uniq | awk '{printf " -I%s", $$0}')

SOURCEDIR_NIBBLER = src/games/nibbler
SRC_NIBBLER = $(call rwildc,$(SOURCEDIR_NIBBLER),*.cpp)
OBJ_NIBBLER = $(SRC_NIBBLER:.cpp=.o)
NIBBLER_NAME = ./lib/arcade_nibbler.so

SOURCEDIR_CENTIPEDE = src/games/centipede
SRC_CENTIPEDE = $(call rwildc,$(SOURCEDIR_CENTIPEDE),*.cpp)
OBJ_CENTIPEDE = $(SRC_CENTIPEDE:.cpp=.o)
CENTIPEDE_NAME = ./lib/arcade_centipede.so

SOURCEDIR_SFML = src/libs/sfml
SRC_SFML = $(call rwildc,$(SOURCEDIR_SFML),*.cpp)
OBJ_SFML = $(SRC_SFML:.cpp=.o)
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_NAME = ./lib/arcade_sfml.so

SOURCEDIR_SDL = src/libs/sdl
SRC_SDL = $(call rwildc,$(SOURCEDIR_SDL),*.cpp)
OBJ_SDL = $(SRC_SDL:.cpp=.o)
SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
SDL_NAME = ./lib/arcade_sdl2.so

SOURCEDIR_NCURSES = src/libs/ncurses
SRC_NCURSES = $(call rwildc,$(SOURCEDIR_NCURSES),*.cpp)
OBJ_NCURSES = $(SRC_NCURSES:.cpp=.o)
NCURSES_FLAGS = -lcurses
NCURSES_NAME = ./lib/arcade_ncurses.so

SOURCEDIR_CORE = src/core/
SRC_CORE = $(call rwildc,$(SOURCEDIR_CORE),*.cpp)
OBJ_CORE = $(SRC_CORE:.cpp=.o)

ALL_SRC = $(SRC_NIBBLER) $(SRC_CENTIPEDE) $(SRC_SFML) $(SRC_SDL) $(SRC_NCURSES) $(SRC_CORE)
ALL_OBJ = $(OBJ_NIBBLER) $(OBJ_CENTIPEDE) $(OBJ_SFML) $(OBJ_SDL) $(OBJ_NCURSES) $(OBJ_CORE)

CXX = g++

NAME = arcade

BASE_FLAGS = -Wall -Wextra $(INCLUDE_DIRS) -std=c++20 -g
CXXFLAGS = $(BASE_FLAGS)

all: core games graphicals

core: try-clean-CORE $(OBJ_CORE)
	g++ -o $(NAME) $(OBJ_CORE) $(CXXFLAGS)
core-clean:
	rm -f $(OBJ_CORE)
core-fclean: core-clean
	rm -f $(NAME)
core-re: core-fclean core

try-clean-%:
	(ls $(SOURCEDIR_$*)/*.gc* > /dev/null 2>&1 && rm -rf $(OBJ_$*) $(SOURCEDIR_$*)/*.gc*) || true

games: try-clean-NIBBLER try-clean-CENTIPEDE $(OBJ_NIBBLER) $(OBJ_CENTIPEDE)
	ld -fPIC -shared -o $(NIBBLER_NAME) $(OBJ_NIBBLER)
	ld -fPIC -shared -o $(CENTIPEDE_NAME) $(OBJ_CENTIPEDE)
games-clean:
	rm -f $(OBJ_NIBBLER) $(OBJ_CENTIPEDE)
games-re: games-clean games

graphicals:	CXXFLAGS = $(BASE_FLAGS) $(SFML_FLAGS)
graphicals: try-clean-SFML try-clean-SDL try-clean-NCURSES $(OBJ_SFML)

graphicals:	CXXFLAGS = $(BASE_FLAGS) $(SDL_FLAGS)
graphicals: $(OBJ_SDL)

graphicals:	CXXFLAGS = $(BASE_FLAGS) $(NCURSES_FLAGS)
graphicals: $(OBJ_NCURSES)
	ld -fPIC -shared -o $(SFML_NAME) $(OBJ_SFML)
	ld -fPIC -shared -o $(SDL_NAME) $(OBJ_SDL)
	ld -fPIC -shared -o $(NCURSES_NAME) $(OBJ_NCURSES)

graphicals-clean:
	rm -f $(OBJ_SFML) $(OBJ_SDL) $(OBJ_NCURSES)
graphicals-re: graphicals-clean graphicals

tests_run:
	cd tests && make

clean:
	rm -f $(ALL_OBJ)
	find . -name "vgcore.*" -delete
	find . -name "*~" -delete
	find . -name "\#*" -delete
	find . -name "*.gc*" -delete

fclean:    clean
	rm -f $(NAME) $(NIBBLER_NAME) $(CENTIPEDE_NAME) $(SFML_NAME) $(SDL_NAME) $(NCURSES_NAME)

re:        fclean all
