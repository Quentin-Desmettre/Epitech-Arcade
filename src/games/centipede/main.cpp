#include <cstdio>
#include "games/centipede/Centipede.hpp"

extern "C"
{
    void *createGame() {
        return new Arcade::Centipede::Game();
    }

    void deleteGame(void *game) {
        delete static_cast<Arcade::Centipede::Game *>(game);
    }
}
