#include <cstdio>

extern "C"
{
    void *createDisplay() {
        return new int;
    }

    void deleteDisplay(void *display) {
        delete static_cast<int *>(display);
    }
}
