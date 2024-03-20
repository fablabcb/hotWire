#include "Storage.hpp"

#define DEBUGLOG_DEFAULT_LOG_LEVEL_TRACE
#include <DebugLog.h>

Storage::Storage() {}

int Storage::get(Int data)
{
    if(not prefs.begin("hotewire"))
        LOG_ERROR("Failed to open 'hotwire' preferences");

    int r = 0;
    switch(data)
    {
        case Int::HARDCORE_HIGHSCORE:
            r = prefs.getInt("hard_highscore", 0);
            break;

        case Int::TIMED_HIGHSCORE:
            r = prefs.getInt("timed_highscore", 0);
            break;
    }

    prefs.end();
    LOG_DEBUG("get", r);
    return r;
}

void Storage::set(Int data, int newValue)
{
    if(not prefs.begin("hotewire"))
        LOG_ERROR("Failed to open 'hotwire' preferences");

    LOG_DEBUG("set", newValue);

    switch(data)
    {
        case Int::HARDCORE_HIGHSCORE:
            if(prefs.putInt("hard_highscore", newValue) != sizeof(int))
                LOG_ERROR("Failed to write highscore");
            break;

        case Int::TIMED_HIGHSCORE:
            if(prefs.putInt("timed_highscore", newValue) != sizeof(int))
                LOG_ERROR("Failed to write highscore");
            break;
    }

    prefs.end();
}
