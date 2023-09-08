#include <iostream>
#include <chrono>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "SDLWrapper.h"
#include "SDLException.h"
#include "Yarl.h"

#pragma warning(disable: 4100)
int main(int argc, char* argv[])
{
    try {
        auto wrapper = std::make_unique<SDLWrapper>(SCREEN_WIDTH, SCREEN_HEIGHT);

        Yarl yarl(std::move(wrapper), Size(SCREEN_WIDTH, SCREEN_HEIGHT));
        yarl.Main();
    }
    catch (SDLException e)
    {
        std::cerr << e.Message() << std::endl;
        return -1;
    }
    return 0;
}
