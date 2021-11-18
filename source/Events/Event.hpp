//! @date 25/10/21
//! @author David Spry

#pragma once

namespace ds::events {

//! @namespace Types of system events.
//! @note Inherit from this struct in order to add new events.

namespace EventType {
    static constexpr int CursorEvent {-1};
}

//! @struct An event within a system.

struct Event {
    explicit Event(int const eventType):
            id(eventType) {
    }

    virtual ~Event() = default;

    int const id;
};

}