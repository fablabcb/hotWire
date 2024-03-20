#ifndef ARDUINOFAKE_H
#define ARDUINOFAKE_H

#include <cstddef>

using note_t = int;

static const int NOTE_C = 1;
static const int NOTE_D = 2;
static const int NOTE_E = 3;
static const int NOTE_F = 4;

void ledcSetup(int, int, int);
void ledcAttachPin(int, int);
void ledcWrite(int, int);

void ledcWriteNote(int, note_t note, int octave);
size_t millis();

#endif // ARDUINOFAKE_H
