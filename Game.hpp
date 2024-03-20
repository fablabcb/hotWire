#ifndef GAME_HPP
#define GAME_HPP

#include "Audio.hpp"
#include "EventQueue.hpp"
#include "Storage.hpp"

// do NOT add Arduino stuff here

#include <cstddef>
#include <cstdint>
#include <functional>

class Game
{
  public:
    enum class Event
    {
        START_RESET = 1, // start the game/time OR reset the game (e.g. to clear the display)
        WIRE_CONTACT,    // wire has been touched
        END_CONTACT,     // end position has been reached
        SET_HARDCORE,    // enable hardcore mode
        SET_TIMED,       // enable timed mode
        RESET_HIGHSCORE
    };

    enum class GameMode
    {
        HARDCORE, // fastest wins, first contact means death
        TIMED,    // fastest wins; each contact is penalized (with some seconds) -> could be exploited!
    };

    struct Result
    {
        bool won = false;
        size_t contacts = 0;
        size_t runtimeInMs = 0; // written once finished
        uint32_t startTime = 0; // written on start
    };

  public:
    /**
     * @brief Game creates a game
     * @param timerFunction function to get the current application runtime in ms; required for timing
     */
    Game(std::function<uint32_t()> timerFunction, std::function<void(Audio::Sound)> audioCallback);
    /**
     * @brief setupMode changes to the given mode
     * @note Any running game is aborted.
     */
    void setupMode(GameMode mode);

    void pushEvent(Event const& event);

    void processEvents();

    size_t getRuntimeInMs() const;

    bool isRunning() const { return state == State::RUNNING; }
    bool hasWon() const { return state == State::FINISHED && currentResult.won; }
    Result getResult() const { return currentResult; }

  private:
    enum class State
    {
        RUNNING,  //! game is running
        FINISHED, //! game has been finished
        WAITING,  //! game is ready to be started
    };

    struct Config
    {
        GameMode mode = GameMode::HARDCORE;
        bool deathOnContact = true;
        size_t contactPenalty = 0; //! number of ms to add for each contact
    };

  private:
    void doStart();
    void doReset();
    void handleWireContact();
    void handleEndContact();

    uint32_t getCurrentTime() const;
    void processHighscore();

  private:
    State state = State::WAITING;

    Config config;
    Result currentResult;
    Storage storage;

    EventQueue<Event> queue;
    std::function<uint32_t()> timerFunction;
    std::function<void(Audio::Sound)> audioCallback;
};

#endif // GAME_HPP
