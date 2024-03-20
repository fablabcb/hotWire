cmake_minimum_required(VERSION 3.16)

project(hotWire
    VERSION 1.0
    DESCRIPTION "Hot Wire"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


add_executable(console
    Audio.hpp Audio.cpp
    main.cpp
    ArduinoFake.hpp ArduinoFake.cpp
)

target_compile_definitions(console PRIVATE FAKE_ARDUINO)

add_custom_target(files
    SOURCES
        .gitignore
        hotWire.ino
        notes
)

# not a real target to run, just here to get the files "into" an IDE
target_sources(files
  PRIVATE
    Audio.hpp Audio.cpp
    ClockLEDs.h ClockLEDs.cpp
    Config.h
    EventQueue.hpp
    Game.hpp Game.cpp
    Interrupts.h
    LedConfig.hpp
    Storage.hpp Storage.cpp
    Makefile
)
