#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

/*
static const char *wlan_ssid = "FRITZ!Box 7430 MH";
static const char *wlan_password = "bananenbrot29";
/*/
// static const char *wlan_ssid = "fablabcb";
// static const char *wlan_password = "98184880";
//*/

static const uint8_t LED_BUILTIN = 2;
static const uint8_t SERIAL_DATA_PIN = 21;
static const uint8_t LATCH_CLOCK_PIN = 22;
static const uint8_t SHIFT_CLOCK_PIN = 19; // 34 is input only!!!

// GPIO35 has no internal pullup/down
const uint8_t FINISH_PIN = 33;  // rechter DC jack außen (schwarz) zielring
const uint8_t HOTWIRE_PIN = 35; // rechter DC jack innen (rot) heißer draht
// const uint8_t SHIFT_CLOCK_PIN =   ; // linker  DC jack innen (gelb) kein input! 3v3!
const uint8_t BUTTON1_PIN = 17; // taster oben 1 (gelb)
const uint8_t BUTTON2_PIN = 18; // taster oben 2 (rot)
const uint8_t BUTTON3_PIN = 25; // taster oben 3 (grün)
const uint8_t BUTTON4_PIN = 23; // taster oben STD+ZEIT

// const uint8_t CATHODE_PIN     = ;

// LEDC config for piezo speaker
const uint8_t LEDC_CHANNEL_0 = 0;
const uint8_t LEDC_PIN = 32;

#endif
