#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <Preferences.h>

class Storage
{
  public:
    enum class Int
    {
        TIMED_HIGHSCORE,
        HARDCORE_HIGHSCORE
    };

  public:
    Storage();

    int get(Int data);
    void set(Int data, int newValue);

  private:
    Preferences prefs;
};

#endif // STORAGE_HPP
