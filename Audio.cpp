#include "Audio.hpp"

#include "Config.h"

// see https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-ledc.c
// main octave is 4
/*
void playShortC(){
    ledcWriteNote(LEDC_CHANNEL_0,NOTE_C,8); // 8th octave for tone to be hearable
    //ledcWrite(LEDC_CHANNEL_0,50);
    delay(30);
    ledcWrite(LEDC_CHANNEL_0,0);
}
*/

Audio::Note::Note(uint8_t length16)
    : isPause{true}
    , length16th(length16)
{}

Audio::Note::Note(note_t note, uint8_t octave, uint8_t length16)
    : note(note)
    , octave(octave)
    , length16th(length16)
{}

Audio::Audio(size_t bpm)
    : bpm{bpm}
{

    // done
    melodies[Sound::BUTTON] = {{NOTE_C, 3, 1}};
    melodies[Sound::START] = {{8}, {NOTE_C, 5, 4}, {4}, {NOTE_C, 5, 4}, {4}, {NOTE_C, 6, 8}};
    melodies[Sound::PENALTY] = {{NOTE_A, 6, 2}};
    melodies[Sound::WON] = {{NOTE_C, 5, 4}, {NOTE_D, 5, 1}, {NOTE_E, 5, 1}, {NOTE_F, 5, 1}, {NOTE_G, 5, 4}};
    melodies[Sound::LOST] = {{NOTE_C, 5, 1}, {NOTE_A, 4, 1}, {NOTE_F, 4, 1}, {NOTE_D, 4, 1}, {NOTE_C, 4, 8}};
    melodies[Sound::NEW_HIGHSCORE] = melodies[Sound::WON];

    // TODO remove this - shorter for testing
    melodies[Sound::START] = {{NOTE_C, 4, 4}};
}

void Audio::init()
{
    // ledc (pwm) setup for piezo speaker
    ledcSetup(LEDC_CHANNEL_0, 1000, 12); // does not matter, but required for ledAttachPin
    ledcAttachPin(LEDC_PIN, LEDC_CHANNEL_0);
    ledcWrite(LEDC_CHANNEL_0, 0);
}

void Audio::play(Sound sound)
{
    queue.push(sound);
}

void Audio::stopAll()
{
    queue = {};
    ledcWrite(LEDC_CHANNEL_0, 0);
}

void Audio::update()
{
    auto currentMillis = millis();

    if(not running)
    {
        if(queue.empty())
            return;

        running = true;
        currentIndex = 0;
        lastNoteTick = currentMillis;

        currentMelody = melodies[queue.front()];
        queue.pop();
        Note const& note = currentMelody[0];
        if(note.isPause)
            ledcWrite(LEDC_CHANNEL_0, 0);
        else
            ledcWriteNote(LEDC_CHANNEL_0, note.note, note.octave);

        return;
    }

    size_t msPer16th = 1000.0f / (bpm / 60.0f) / 4.0f;
    size_t msToPlayNote = currentMelody[currentIndex].length16th * msPer16th;

    bool noteNotYetOver = lastNoteTick + msToPlayNote > currentMillis;
    if(noteNotYetOver)
        return;

    lastNoteTick += msToPlayNote;

    currentIndex++;
    if(currentIndex >= currentMelody.size())
    {
        ledcWrite(LEDC_CHANNEL_0, 0);
        running = false;
        return;
    }

    Note const& note = currentMelody[currentIndex];
    ledcWriteNote(LEDC_CHANNEL_0, note.note, note.octave);
}
