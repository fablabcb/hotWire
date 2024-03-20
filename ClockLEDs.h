#ifndef CLOCKLEDS_H
#define CLOCKLEDS_H

#include <cstdint>
#include <tuple>

/**
 * @brief The ClockLEDs class is responsible for displaying a given number on the LED screen.
 */
class ClockLEDs
{
  public:
    ClockLEDs()
        : count(0)
        , change(false)
    {}

    /**
     * @brief displayNumber will render the given number on the LEDs. Each half will be visible for approx. onTimeMs/2.
     */
    void displayNumber(
        uint16_t number, uint8_t onTimeMs, bool showColon = false, bool showBottomDot = false, bool showTopDot = false);

  private:
    /**
     * @brief writeToLeds will write both values to the register and adding a delay after each write to give both half
     * of the LEDs the same ON time
     * @param t
     * @param delay
     */
    static void writeToLeds(uint16_t first, uint16_t second, uint8_t onTimePerHalf);

    /**
     * @brief writeToRegister will write the given data and cathode to serial pin (and thus the 16bit register)
     */
    static void writeToRegister(uint8_t cathode, uint16_t data);

    /**
     * @brief writeCathode writes the cathode value to the serial pin
     */
    static void writeCathode(uint8_t cathode);

    /**
     * @brief cyclePin will cycle or pulse the given pin (set HIGH then LOW)
     */
    static void cyclePin(uint8_t pin);

    /**
     * @brief getTupleToWrite will return the 2 values to write for each cathode in order to display the given number
     * @param num the number to display with the LEDs
     * @return [data_0,data_1] to then write to the register one by one
     */
    static std::tuple<uint16_t, uint16_t> getTupleToWrite(uint16_t num);

    // some old display tests
  private:
    // switch off all LEDs and switch one the given one
    static void powerSingleLed(int led);
    static void allSingleLEDs();

  private:
    uint16_t count; //! TODO internal member that should not be required
    bool change;    //! testing only
    // uint16_t data;   //! bits controling which LEDs are ON
    // uint8_t cathode; //! TODO likely not required besides testing
};

#endif
