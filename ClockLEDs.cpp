#include "ClockLEDs.h"
#include "Config.h"
#include "LedConfig.hpp"

#include <Arduino.h>

// #define DEBUGLOG_DISABLE_LOG
#define DEBUGLOG_DEFAULT_LOG_LEVEL_TRACE
#include <DebugLog.h>

void ClockLEDs::displayNumber(uint16_t number, uint8_t onTimeMs, bool showColon, bool showBottomDot, bool showTopDot)
{
    auto t = getTupleToWrite(number);
    uint16_t left = ~std::get<0>(t);
    uint16_t right = ~std::get<1>(t);

    if(showColon)
        right |= LED_MASK::COLON_MASK;
    if(showBottomDot)
        left |= LED_MASK::DOT_BOTTOM_MASK;
    if(showTopDot)
        right |= LED_MASK::DOT_TOP_MASK;

    writeToLeds(~left, ~right, onTimeMs / 2);
}

void ClockLEDs::writeToLeds(uint16_t first, uint16_t second, uint8_t onTimePerHalf)
{
    writeToRegister(0, first);
    delay(onTimePerHalf);

    writeToRegister(1, second);
    delay(onTimePerHalf);

    // clear so both cathodes have the same "on" time to have roughly the same brightness
    writeToRegister(1, ~0);
}

void ClockLEDs::writeToRegister(uint8_t cathode, uint16_t data)
{
    uint16_t x = data;
    x <<= 1;

    for(uint8_t i = 0; i < 15; i++)
    {
        // LOG_DEBUG("i",i);
        // LOG_DEBUG("x",x);
        // LOG_DEBUG("x&",(x & (1<<15)) ? HIGH : LOW);
        digitalWrite(SERIAL_DATA_PIN, (x & (1 << 15)) ? HIGH : LOW);
        cyclePin(SHIFT_CLOCK_PIN);
        x <<= 1;
    }

    //
    writeCathode(cathode);

    cyclePin(LATCH_CLOCK_PIN);
}

void ClockLEDs::writeCathode(uint8_t cathode)
{
    digitalWrite(SERIAL_DATA_PIN, cathode ? HIGH : LOW);
    cyclePin(SHIFT_CLOCK_PIN);
}

void ClockLEDs::cyclePin(uint8_t pin)
{
    digitalWrite(pin, HIGH);
    // delay(2);
    digitalWrite(pin, LOW);
    // delay(2);
}

std::tuple<uint16_t, uint16_t> ClockLEDs::getTupleToWrite(uint16_t num)
{
    /*writeTuple({
      DOT_BOTTOM_MASK|std::get<0>(CHAR_0_8)|std::get<0>(CHAR_1_8)|std::get<0>(CHAR_2_8)|std::get<0>(CHAR_3_8),
        COLON_MASK|DOT_TOP_MASK|std::get<1>(CHAR_0_8)|std::get<1>(CHAR_1_8)|std::get<1>(CHAR_2_8)|std::get<1>(CHAR_3_8)
      });
    */

    auto a{LED_MAP.at({0, num % 10})};
    auto b{LED_MAP.at({1, (num / 10) % 10})};
    auto c{LED_MAP.at({2, (num / 100) % 10})};
    auto d{LED_MAP.at({3, (num / 1000) % 10})};

    return {
        ~(std::get<0>(a) | std::get<0>(b) | std::get<0>(c) | std::get<0>(d)),
        ~(std::get<1>(a) | std::get<1>(b) | std::get<1>(c) | std::get<1>(d))};
}

////////////////////////////////////////////////////////////
/// removal/debug/test section
////////////////////////////////////////////////////////////

void ClockLEDs::powerSingleLed(int led)
{
    uint8_t cathode{0};

    if(led >= LED_COUNT)
    {
        led = led - LED_COUNT;
        cathode = 1;
    }

    uint8_t data = ~(1 << led);

    writeToRegister(data, cathode);
}

void ClockLEDs::allSingleLEDs()
{
    static uint32_t last_millis{0};
    uint32_t curr_millis{millis()};
    static int curr_led{0};

    if(curr_millis - last_millis > 500)
    {
        last_millis = curr_millis;

        curr_led++;
        if(curr_led == NUM_LED_POS)
            curr_led = 0;

        powerSingleLed(led_vec[curr_led]);

        delay(500);
    }
}
