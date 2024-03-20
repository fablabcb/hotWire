#include "ArduinoFake.hpp"

#include <chrono>
#include <iostream>

void ledcSetup(int, int, int) {}
void ledcAttachPin(int, int) {}
void ledcWrite(int, int v)
{
    if(v == 0)
        std::cout << "Audio off" << std::endl;
}

void ledcWriteNote(int, note_t note, int octave)
{
    std::cout << "Note: " << note << " " << octave << std::endl;
}

size_t millis()
{
    using namespace std::chrono;
    static auto start = steady_clock::now();

    return duration_cast<milliseconds>(steady_clock::now() - start).count();
}
