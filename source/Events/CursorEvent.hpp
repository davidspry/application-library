//! @date 25/10/21
//! @author David Spry

#pragma once

#include "UI/Point.hpp"
#include "Events/Event.hpp"

namespace ds::ui {

//! @struct The state of a cursor event.

struct CursorEventData {
    explicit CursorEventData(ds::ui::Point<int> const& cursorPosition,
                             bool const leftButtonDown,
                             bool const rightButtonDown):
            xy(cursorPosition),
            leftButtonIsPressed(leftButtonDown),
            rightButtonIsPressed(rightButtonDown) {
    }

    ds::ui::Point<int> xy {};
    bool leftButtonIsPressed {false};
    bool rightButtonIsPressed {false};
};

//! @struct An event representing the state of a cursor.

struct CursorEvent: public ds::events::Event, public CursorEventData {
    CursorEvent(ds::ui::Point<int> const& cursorPosition,
                bool const leftButtonDown,
                bool const rightButtonDown):
            Event(ds::events::EventType::CursorEvent),
            CursorEventData(cursorPosition, leftButtonDown, rightButtonDown) {
    }
};

}