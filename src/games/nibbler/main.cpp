#include <cstdio>
#include "games/nibbler/Nibbler.hpp"

extern "C"
{
    void *createGame() {
        return new Arcade::Nibbler::Game();
    }

    void deleteGame(void *game) {
        delete static_cast<Arcade::Nibbler::Game *>(game);
    }
}
