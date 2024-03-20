#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <Arduino.h>

#include "ClockLEDs.h"
#include "Config.h"
#include "Game.hpp"

static const unsigned long DEBOUNCE_TIMEOUT{300};

static const unsigned long BUTTON_DEBOUNCE_TIMEOUT{1000};
static const unsigned long WIRE_DEBOUNCE_TIMEOUT{200};

extern ClockLEDs leds;
extern Game game;

void IRAM_ATTR isrStartButton()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > BUTTON_DEBOUNCE_TIMEOUT)
    {
        game.pushEvent(Game::Event::START_RESET);
        last_millis = curr_millis;
    }
}

void IRAM_ATTR isrHardcoreButton()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > BUTTON_DEBOUNCE_TIMEOUT)
    {
        game.pushEvent(Game::Event::SET_HARDCORE);
        last_millis = curr_millis;
    }
}
void IRAM_ATTR isrTimedButton()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > BUTTON_DEBOUNCE_TIMEOUT)
    {
        game.pushEvent(Game::Event::SET_TIMED);
        last_millis = curr_millis;
    }
}
void IRAM_ATTR isrResetButton()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > BUTTON_DEBOUNCE_TIMEOUT)
    {
        game.pushEvent(Game::Event::RESET_HIGHSCORE);
        last_millis = curr_millis;
    }
}

void IRAM_ATTR isrWireContact()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > WIRE_DEBOUNCE_TIMEOUT)
    {
        game.pushEvent(Game::Event::WIRE_CONTACT);
        last_millis = curr_millis;
    }
}

void IRAM_ATTR isrEndContact()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > WIRE_DEBOUNCE_TIMEOUT)
    {
        game.pushEvent(Game::Event::END_CONTACT);
        last_millis = curr_millis;
    }
}

//
// old
//
/*
void IRAM_ATTR isr_button1()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > DEBOUNCE_TIMEOUT)
    {
        // leds.next();
        // leds.prev();
        last_millis = curr_millis;
    }
}

void IRAM_ATTR isr_button2()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > DEBOUNCE_TIMEOUT)
    {
        // leds.prev();
        last_millis = curr_millis;
    }
}

void IRAM_ATTR isr_button3()
{
    static unsigned long last_millis{0};
    unsigned long curr_millis{millis()};

    if(curr_millis - last_millis > DEBOUNCE_TIMEOUT)
    {
        // leds.nextCathode();
        last_millis = curr_millis;
    }
}

void IRAM_ATTR isr_timer0()
{
    leds.next();
}
*/
#endif
