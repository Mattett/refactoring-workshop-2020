#pragma once

#include <cstdint>
#include <memory>

//klaudia
class Event
{
public:
    virtual ~Event() = default;

    virtual std::uint32_t getMessageId() const = 0;
    virtual std::unique_ptr<Event> clone() const  = 0;
};
