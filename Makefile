##
## EPITECH PROJECT, 2023
## helloworld
## File description:
## Makefile
##

all: core games graphicals

core:
	@make -C src/core/

games:
	@make -C src/games/nibbler/
	@make -C src/games/centipede/

graphicals:
	@make -C src/libs/sfml/
	@make -C src/libs/sdl/
	@make -C src/libs/ncurses/
	@make -C src/libs/test/

tests_run:
	cd tests && make

apply-rule-%:
	@make -C src/core/ $*
	@make -C src/games/nibbler/ $*
	@make -C src/games/centipede/ $*
	@make -C src/libs/sfml/ $*
	@make -C src/libs/sdl/ $*
	@make -C src/libs/ncurses/ $*

clean: apply-rule-clean

fclean: apply-rule-fclean

re: fclean all
