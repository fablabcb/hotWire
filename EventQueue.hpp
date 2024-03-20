#ifndef EVENTQUEUE_HPP
#define EVENTQUEUE_HPP

#include <array>

/**
 * @brief The EventQueue class uses a ring buffer to store events. You can always push, but once you fill your buffer
 * completely, you loose all events currently stored.
 */
// TODO "loose all events"? more like "begin overwriting"? which ones?
template <class T, unsigned int size = 10>
class EventQueue
{
  public:
    EventQueue()
        : writePos{ringBuffer.begin()}
        , readPos{ringBuffer.begin()}
    {}

    /**
     * @brief push will add new events to the buffer, possibly overwriting existing ones.
     */
    void push(T const& event)
    {
        *writePos = event;
        writePos++;
        if(writePos == ringBuffer.end())
            writePos = ringBuffer.begin();
    }

    bool hasEvent() const { return writePos != readPos; }

    /**
     * @brief get writes the current event (if any) to the parameter, pops it and returns true iff there was an event.
     */
    bool get(T& event)
    {
        if(!hasEvent())
            return false;

        event = *readPos;
        pop();
        return true;
    }

    void pop()
    {
        if(not hasEvent())
            return;

        readPos++;
        if(readPos == ringBuffer.end())
            readPos = ringBuffer.begin();
    }

    void clear() { readPos = writePos; }

  private:
    std::array<T, size> ringBuffer;
    typename decltype(ringBuffer)::iterator writePos;
    typename decltype(ringBuffer)::iterator readPos;
};

#endif // EVENTQUEUE_HPP
