#include "Audio.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    std::cout << "Playing SOUND::TEST. Press CTRL-c to quit" << std::endl;

    Audio audio;
    audio.play(Audio::Sound::WON);

    bool running = true;
    while(running)
    {
        audio.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
