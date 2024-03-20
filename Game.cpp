// #define DEBUGLOG_DISABLE_LOG
#define DEBUGLOG_DEFAULT_LOG_LEVEL_TRACE
#include <DebugLog.h>

#include "Game.hpp"

// do NOT add Arduino stuff here

Game::Game(std::function<uint32_t()> timerFunction, std::function<void(Audio::Sound)> audioCallback)
    : timerFunction(timerFunction)
    , audioCallback(audioCallback)
{
    if(not timerFunction)
        throw "You failed";
}

void Game::setupMode(GameMode mode)
{
    state = State::WAITING;

    audioCallback(Audio::Sound::BUTTON);

    config.mode = mode;
    switch(mode)
    {
        case GameMode::HARDCORE:
            config.contactPenalty = 0;
            config.deathOnContact = true;
            break;

        case GameMode::TIMED:
            config.contactPenalty = 5000;
            config.deathOnContact = false;
            break;
    }

    currentResult = Result{};
}

void Game::pushEvent(Event const& event)
{
    queue.push(event);
}

void Game::processEvents()
{
    if(queue.hasEvent())
        LOG_DEBUG("pE");

    Event event;
    while(queue.get(event))
    {
        LOG_DEBUG("e:", static_cast<int>(event));

        switch(state)
        {
            case State::WAITING:
                switch(event)
                {
                    case Event::START_RESET:
                        doStart();
                        break;
                    case Event::SET_HARDCORE:
                        setupMode(GameMode::HARDCORE);
                        break;
                    case Event::SET_TIMED:
                        setupMode(GameMode::TIMED);
                        break;
                    case Event::RESET_HIGHSCORE:
                        audioCallback(Audio::Sound::BUTTON);
                        storage.set(
                            config.mode == GameMode::HARDCORE ? Storage::Int::HARDCORE_HIGHSCORE
                                                              : Storage::Int::TIMED_HIGHSCORE,
                            0);
                        break;
                }
                break;

            case State::RUNNING:
                switch(event)
                {
                    case Event::END_CONTACT:
                        handleEndContact();
                        break;
                    case Event::WIRE_CONTACT:
                        handleWireContact();
                        break;
                    case Event::START_RESET:
                        doReset();
                        break;
                    default:
                        break;
                }
                break;

            case State::FINISHED:
                if(event == Event::START_RESET)
                    doReset();
                break;
        }
    }
}

size_t Game::getRuntimeInMs() const
{
    switch(state)
    {
        case State::WAITING:
            return 0;

        case State::FINISHED:
            return currentResult.runtimeInMs;

        case State::RUNNING:
            return getCurrentTime();
    }
}

void Game::doStart()
{
    currentResult = Result{};
    currentResult.startTime = timerFunction();
    state = State::RUNNING;
    // audioCallback(Audio::Sound::BUTTON);
    audioCallback(Audio::Sound::START);
}

void Game::doReset()
{
    if(state == State::RUNNING)
        audioCallback(Audio::Sound::LOST);
    else
        audioCallback(Audio::Sound::BUTTON);

    currentResult = Result{};
    state = State::WAITING;
}

void Game::handleWireContact()
{
    currentResult.contacts++;

    if(config.deathOnContact)
    {
        state = State::WAITING;
        currentResult.won = false;
        currentResult.runtimeInMs = getCurrentTime();
        audioCallback(Audio::Sound::LOST);
    }
    else
        audioCallback(Audio::Sound::PENALTY);
}

void Game::handleEndContact()
{
    state = State::FINISHED;
    currentResult.won = true;
    currentResult.runtimeInMs = getCurrentTime();

    processHighscore();
}

uint32_t Game::getCurrentTime() const
{
    switch(config.mode)
    {
        case GameMode::HARDCORE:
            return timerFunction() - currentResult.startTime;

        case GameMode::TIMED:
            return timerFunction() - currentResult.startTime + currentResult.contacts * config.contactPenalty;
    }
}

void Game::processHighscore()
{
    auto scoreField =
        config.mode == GameMode::HARDCORE ? Storage::Int::HARDCORE_HIGHSCORE : Storage::Int::TIMED_HIGHSCORE;
    auto currentScore = getRuntimeInMs();
    auto bestScore = storage.get(scoreField);

    if(currentScore < bestScore || bestScore == 0)
    {
        storage.set(scoreField, currentScore);
        audioCallback(Audio::Sound::NEW_HIGHSCORE);
        audioCallback(Audio::Sound::NEW_HIGHSCORE);
        audioCallback(Audio::Sound::NEW_HIGHSCORE);
    }
    else
        audioCallback(Audio::Sound::WON);
}
