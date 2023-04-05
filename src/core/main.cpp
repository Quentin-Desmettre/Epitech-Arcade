/*
** EPITECH PROJECT, 2023
** Epitech-Arcade
** File description:
** main
*/

#include "Core.hpp"
#include <iostream>

int main(int ac, char **av)
{
   try {
        Arcade::Core::Core core(ac, av);
        return core.run(av[1]);
   } catch (std::exception &e) {
       std::cerr << e.what() << std::endl;
       return 84;
   }
}
