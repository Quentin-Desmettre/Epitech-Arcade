#include <cstdio>

extern "C"
{
    void *createGame() {
        return new int;
    }

    void deleteGame(void *game) {
        delete static_cast<int *>(game);
    }
}
