#ifndef LEDCONFIG_HPP
#define LEDCONFIG_HPP

#include <cstdint>
#include <map>
#include <tuple>
#include <vector>

/*
 * This file contains data mappings required to control the LEDs. For a given input, the correct LEDs of the 30
 * available ones need to light up.
 * There 30 LEDs but only a 16bit register is available. Thus, 2 cathodes (1 of 16 bits) control which half of the 30
 * LEDs is controlled by the other 15 bits.
 */

// LED Panel Positions to Driver Chip Pins
//
// 1,2,3 - Q_a - 1st  bit // GND switch
// 4,5   - Q_p - 16th bit
// 6,22  - Q_b - 2
// 7     - Q_o - 15
// 8     - Q_k - 11
// 9     - Q_n - 14
// 10    - Q_m - 13
// 11,12 - Q_l - 12
// 13    - Q_j - 10
// 14,15 - Q_i - 9
// 16    - Q_g - 7
// 17    - Q_f - 6
// 18    - Q_e - 5
// 19    - Q_d - 4
// 20    - Q_c - 3
// 21    - Q_h - 8

// Q_a is the last bit written into the register
// so just put 15bit in and then which cathode
//
// writing a 0 to Q_a corresponds to cathode 2 (pins 2+3)
// writing a 1 to Q_a corresponds to cathode 1 (pin 1)

enum LEDPos
{
    // cathode=0:
    CHAR_3_SEG_B = 0,
    CHAR_0_SEG_C,
    CHAR_0_SEG_B,
    CHAR_1_SEG_E,
    CHAR_1_SEG_D,
    CHAR_1_SEG_G,
    CHAR_0_SEG_A,
    CHAR_1_SEG_F,
    CHAR_2_SEG_A,
    CHAR_3_SEG_E,
    CHAR_2_SEG_C,
    CHAR_2_SEG_B,
    CHAR_3_SEG_C,
    CHAR_3_SEG_G,
    DOT_BOTTOM,

    // cathode=1:
    COLON,
    CHAR_0_SEG_D,
    CHAR_0_SEG_G,
    CHAR_0_SEG_E,
    CHAR_1_SEG_C,
    CHAR_1_SEG_B,
    CHAR_0_SEG_F,
    CHAR_1_SEG_A,
    CHAR_2_SEG_F,
    CHAR_3_SEG_D,
    CHAR_2_SEG_D,
    CHAR_2_SEG_G,
    CHAR_2_SEG_E,
    CHAR_3_SEG_A,
    DOT_TOP,
    NUM_LED_POS
};
static const uint8_t LED_COUNT = 15;

enum LED_MASK
{
    CHAR_0_SEG_A_MASK = 1 << (CHAR_0_SEG_A),
    CHAR_0_SEG_B_MASK = 1 << (CHAR_0_SEG_B),
    CHAR_0_SEG_C_MASK = 1 << (CHAR_0_SEG_C),
    CHAR_0_SEG_D_MASK = 1 << (CHAR_0_SEG_D - LED_COUNT),
    CHAR_0_SEG_E_MASK = 1 << (CHAR_0_SEG_E - LED_COUNT),
    CHAR_0_SEG_F_MASK = 1 << (CHAR_0_SEG_F - LED_COUNT),
    CHAR_0_SEG_G_MASK = 1 << (CHAR_0_SEG_G - LED_COUNT),

    CHAR_1_SEG_A_MASK = 1 << (CHAR_1_SEG_A - LED_COUNT),
    CHAR_1_SEG_B_MASK = 1 << (CHAR_1_SEG_B - LED_COUNT),
    CHAR_1_SEG_C_MASK = 1 << (CHAR_1_SEG_C - LED_COUNT),
    CHAR_1_SEG_D_MASK = 1 << (CHAR_1_SEG_D),
    CHAR_1_SEG_E_MASK = 1 << (CHAR_1_SEG_E),
    CHAR_1_SEG_F_MASK = 1 << (CHAR_1_SEG_F),
    CHAR_1_SEG_G_MASK = 1 << (CHAR_1_SEG_G),

    COLON_MASK = 1 << (COLON - LED_COUNT),

    CHAR_2_SEG_A_MASK = 1 << (CHAR_2_SEG_A),
    CHAR_2_SEG_B_MASK = 1 << (CHAR_2_SEG_B),
    CHAR_2_SEG_C_MASK = 1 << (CHAR_2_SEG_C),
    CHAR_2_SEG_D_MASK = 1 << (CHAR_2_SEG_D - LED_COUNT),
    CHAR_2_SEG_E_MASK = 1 << (CHAR_2_SEG_E - LED_COUNT),
    CHAR_2_SEG_F_MASK = 1 << (CHAR_2_SEG_F - LED_COUNT),
    CHAR_2_SEG_G_MASK = 1 << (CHAR_2_SEG_G - LED_COUNT),

    CHAR_3_SEG_A_MASK = 1 << (CHAR_3_SEG_A - LED_COUNT),
    CHAR_3_SEG_B_MASK = 1 << (CHAR_3_SEG_B),
    CHAR_3_SEG_C_MASK = 1 << (CHAR_3_SEG_C),
    CHAR_3_SEG_D_MASK = 1 << (CHAR_3_SEG_D - LED_COUNT),
    CHAR_3_SEG_E_MASK = 1 << (CHAR_3_SEG_E),
    //  CHAR_3_SEG_F, // doesnt exist, because led not populated
    CHAR_3_SEG_G_MASK = 1 << (CHAR_3_SEG_G),

    DOT_BOTTOM_MASK = 1 << (DOT_BOTTOM),
    DOT_TOP_MASK = 1 << (DOT_TOP - LED_COUNT),
};

// define the '8' first, so all segments are here and in the right cathode tuple part
static const std::map<std::tuple<uint8_t, uint8_t>, std::tuple<uint16_t, uint16_t>> LED_MAP{
    {{0, 8},
     {CHAR_0_SEG_A_MASK | CHAR_0_SEG_B_MASK | CHAR_0_SEG_C_MASK,
      CHAR_0_SEG_D_MASK | CHAR_0_SEG_E_MASK | CHAR_0_SEG_F_MASK | CHAR_0_SEG_G_MASK}},

    {{0, 0},
     {CHAR_0_SEG_A_MASK | CHAR_0_SEG_B_MASK | CHAR_0_SEG_C_MASK,
      CHAR_0_SEG_D_MASK | CHAR_0_SEG_E_MASK | CHAR_0_SEG_F_MASK}},

    {{0, 1}, {CHAR_0_SEG_B_MASK | CHAR_0_SEG_C_MASK, 0}},

    {{0, 2}, {CHAR_0_SEG_A_MASK | CHAR_0_SEG_B_MASK, CHAR_0_SEG_D_MASK | CHAR_0_SEG_E_MASK | CHAR_0_SEG_G_MASK}},

    {{0, 3}, {CHAR_0_SEG_A_MASK | CHAR_0_SEG_B_MASK | CHAR_0_SEG_C_MASK, CHAR_0_SEG_D_MASK | CHAR_0_SEG_G_MASK}},

    {{0, 4}, {CHAR_0_SEG_B_MASK | CHAR_0_SEG_C_MASK, CHAR_0_SEG_F_MASK | CHAR_0_SEG_G_MASK}},

    {{0, 5}, {CHAR_0_SEG_A_MASK | CHAR_0_SEG_C_MASK, CHAR_0_SEG_D_MASK | CHAR_0_SEG_F_MASK | CHAR_0_SEG_G_MASK}},

    {{0, 6},
     {CHAR_0_SEG_A_MASK | CHAR_0_SEG_C_MASK,
      CHAR_0_SEG_D_MASK | CHAR_0_SEG_E_MASK | CHAR_0_SEG_F_MASK | CHAR_0_SEG_G_MASK}},

    {{0, 7}, {CHAR_0_SEG_A_MASK | CHAR_0_SEG_B_MASK | CHAR_0_SEG_C_MASK, 0}},

    {{0, 9},
     {CHAR_0_SEG_A_MASK | CHAR_0_SEG_B_MASK | CHAR_0_SEG_C_MASK,
      CHAR_0_SEG_D_MASK | CHAR_0_SEG_F_MASK | CHAR_0_SEG_G_MASK}},

    {{1, 8},
     {CHAR_1_SEG_D_MASK | CHAR_1_SEG_E_MASK | CHAR_1_SEG_F_MASK | CHAR_1_SEG_G_MASK,
      CHAR_1_SEG_A_MASK | CHAR_1_SEG_B_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 0},
     {CHAR_1_SEG_D_MASK | CHAR_1_SEG_E_MASK | CHAR_1_SEG_F_MASK,
      CHAR_1_SEG_A_MASK | CHAR_1_SEG_B_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 1}, {0, CHAR_1_SEG_B_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 2}, {CHAR_1_SEG_D_MASK | CHAR_1_SEG_E_MASK | CHAR_1_SEG_G_MASK, CHAR_1_SEG_A_MASK | CHAR_1_SEG_B_MASK}},

    {{1, 3}, {CHAR_1_SEG_D_MASK | CHAR_1_SEG_G_MASK, CHAR_1_SEG_A_MASK | CHAR_1_SEG_B_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 4}, {CHAR_1_SEG_F_MASK | CHAR_1_SEG_G_MASK, CHAR_1_SEG_B_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 5}, {CHAR_1_SEG_D_MASK | CHAR_1_SEG_F_MASK | CHAR_1_SEG_G_MASK, CHAR_1_SEG_A_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 6},
     {CHAR_1_SEG_D_MASK | CHAR_1_SEG_E_MASK | CHAR_1_SEG_F_MASK | CHAR_1_SEG_G_MASK,
      CHAR_1_SEG_A_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 7}, {0, CHAR_1_SEG_A_MASK | CHAR_1_SEG_B_MASK | CHAR_1_SEG_C_MASK}},

    {{1, 9},
     {CHAR_1_SEG_D_MASK | CHAR_1_SEG_F_MASK | CHAR_1_SEG_G_MASK,
      CHAR_1_SEG_A_MASK | CHAR_1_SEG_B_MASK | CHAR_1_SEG_C_MASK}},

    {{2, 8},
     {CHAR_2_SEG_A_MASK | CHAR_2_SEG_B_MASK | CHAR_2_SEG_C_MASK,
      CHAR_2_SEG_D_MASK | CHAR_2_SEG_E_MASK | CHAR_2_SEG_F_MASK | CHAR_2_SEG_G_MASK}},

    {{2, 0},
     {CHAR_2_SEG_A_MASK | CHAR_2_SEG_B_MASK | CHAR_2_SEG_C_MASK,
      CHAR_2_SEG_D_MASK | CHAR_2_SEG_E_MASK | CHAR_2_SEG_F_MASK}},

    {{2, 1}, {CHAR_2_SEG_B_MASK | CHAR_2_SEG_C_MASK, 0}},

    {{2, 2}, {CHAR_2_SEG_A_MASK | CHAR_2_SEG_B_MASK, CHAR_2_SEG_D_MASK | CHAR_2_SEG_E_MASK | CHAR_2_SEG_G_MASK}},

    {{2, 3}, {CHAR_2_SEG_A_MASK | CHAR_2_SEG_B_MASK | CHAR_2_SEG_C_MASK, CHAR_2_SEG_D_MASK | CHAR_2_SEG_G_MASK}},

    {{2, 4}, {CHAR_2_SEG_B_MASK | CHAR_2_SEG_C_MASK, CHAR_2_SEG_F_MASK | CHAR_2_SEG_G_MASK}},

    {{2, 5}, {CHAR_2_SEG_A_MASK | CHAR_2_SEG_C_MASK, CHAR_2_SEG_D_MASK | CHAR_2_SEG_F_MASK | CHAR_2_SEG_G_MASK}},

    {{2, 6},
     {CHAR_2_SEG_A_MASK | CHAR_2_SEG_C_MASK,
      CHAR_2_SEG_D_MASK | CHAR_2_SEG_E_MASK | CHAR_2_SEG_F_MASK | CHAR_2_SEG_G_MASK}},

    {{2, 7}, {CHAR_2_SEG_A_MASK | CHAR_2_SEG_B_MASK | CHAR_2_SEG_C_MASK, 0}},

    {{2, 9},
     {CHAR_2_SEG_A_MASK | CHAR_2_SEG_B_MASK | CHAR_2_SEG_C_MASK,
      CHAR_2_SEG_D_MASK | CHAR_2_SEG_F_MASK | CHAR_2_SEG_G_MASK}},

    {{3, 8},
     {CHAR_3_SEG_B_MASK | CHAR_3_SEG_C_MASK | CHAR_3_SEG_E_MASK | CHAR_3_SEG_G_MASK,
      CHAR_3_SEG_A_MASK | CHAR_3_SEG_D_MASK}},

    {{3, 0}, {CHAR_3_SEG_B_MASK | CHAR_3_SEG_C_MASK | CHAR_3_SEG_E_MASK, CHAR_3_SEG_A_MASK | CHAR_3_SEG_D_MASK}},

    {{3, 1}, {CHAR_3_SEG_B_MASK | CHAR_3_SEG_C_MASK, 0}},

    {{3, 2}, {CHAR_3_SEG_B_MASK | CHAR_3_SEG_E_MASK | CHAR_3_SEG_G_MASK, CHAR_3_SEG_A_MASK | CHAR_3_SEG_D_MASK}},

    {{3, 3}, {CHAR_3_SEG_B_MASK | CHAR_3_SEG_C_MASK | CHAR_3_SEG_G_MASK, CHAR_3_SEG_A_MASK | CHAR_3_SEG_D_MASK}},

    {{3, 4}, {CHAR_3_SEG_B_MASK | CHAR_3_SEG_C_MASK | CHAR_3_SEG_G_MASK, 0}},

    {{3, 5}, {CHAR_3_SEG_C_MASK | CHAR_3_SEG_G_MASK, CHAR_3_SEG_A_MASK | CHAR_3_SEG_D_MASK}},

    {{3, 6}, {CHAR_3_SEG_C_MASK | CHAR_3_SEG_E_MASK | CHAR_3_SEG_G_MASK, CHAR_3_SEG_A_MASK | CHAR_3_SEG_D_MASK}},

    {{3, 7}, {CHAR_3_SEG_B_MASK | CHAR_3_SEG_C_MASK, CHAR_3_SEG_A_MASK}},

    {{3, 9}, {CHAR_3_SEG_B_MASK | CHAR_3_SEG_C_MASK | CHAR_3_SEG_G_MASK, CHAR_3_SEG_A_MASK | CHAR_3_SEG_D_MASK}},

};

static const std::vector<int> led_vec(
    {CHAR_0_SEG_A,
     CHAR_0_SEG_B,
     CHAR_0_SEG_C,
     CHAR_0_SEG_D,
     CHAR_0_SEG_E,
     CHAR_0_SEG_F,
     CHAR_0_SEG_G,

     CHAR_1_SEG_A,
     CHAR_1_SEG_B,
     CHAR_1_SEG_C,
     CHAR_1_SEG_D,
     CHAR_1_SEG_E,
     CHAR_1_SEG_F,
     CHAR_1_SEG_G,

     COLON,

     CHAR_2_SEG_A,
     CHAR_2_SEG_B,
     CHAR_2_SEG_C,
     CHAR_2_SEG_D,
     CHAR_2_SEG_E,
     CHAR_2_SEG_F,
     CHAR_2_SEG_G,

     CHAR_3_SEG_A,
     CHAR_3_SEG_B,
     CHAR_3_SEG_C,
     CHAR_3_SEG_D,
     CHAR_3_SEG_E,
     //  CHAR_3_SEG_F,
     CHAR_3_SEG_G,

     DOT_BOTTOM,
     DOT_TOP});

#endif
