#ifndef AUDIO_HPP
#define AUDIO_HPP

#ifdef FAKE_ARDUINO
#include "ArduinoFake.hpp"
#else
#include <Arduino.h>
#endif

#include <cstdint>
#include <map>
#include <queue>
#include <vector>

class Audio
{
  public:
    enum class Sound
    {
        START,
        WON,
        LOST,
        BUTTON,
        PENALTY,
        NEW_HIGHSCORE
    };

  public:
    Audio(size_t bpm = 120); // we assume 4/4

    void init();
    void play(Sound sound);
    void stopAll();
    void update();

  private:
    struct Note
    {
        bool isPause = false;
        note_t note = NOTE_C;
        uint8_t octave = 0;
        uint8_t length16th = 4;

        Note(uint8_t length16);
        Note(note_t note, uint8_t octave, uint8_t length16);
    };

    using Melody = std::vector<Note>;

  private:
    bool running = false;
    size_t lastNoteTick = 0;
    size_t bpm = 0;
    size_t currentIndex = 0;

    std::queue<Sound> queue;
    std::map<Sound, Melody> melodies;
    Melody currentMelody;
};

#endif // AUDIO_HPP
