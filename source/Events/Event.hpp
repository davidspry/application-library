//! @date 25/10/21
//! @author David Spry

#pragma once

namespace ds::events {

//! @enum Types of system events.

enum class EventType {
    CursorEvent
};

//! @struct An event within a system.

struct Event {
    explicit Event(EventType const& eventType):
            type(eventType) {
    }

    EventType const type;
};

}