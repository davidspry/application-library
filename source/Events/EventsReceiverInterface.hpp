//! @date 25/10/21
//! @author David Spry

#pragma once

#include <Events/Event.hpp>

namespace ds::events {

//! @class An interface for a class that can receive events.

class ReceiverInterface {
public:
    virtual ~ReceiverInterface() = default;

public:
    virtual void onEvent(Event const& event) = 0;
};

}