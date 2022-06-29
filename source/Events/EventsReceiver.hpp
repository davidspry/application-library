//! @date 15/11/21
//! @author David Spry

#pragma once

#include <Events/Event.hpp>
#include <Events/EventsDispatcher.hpp>
#include <Events/EventsReceiverInterface.hpp>

namespace ds::events {

//! @class An abstract class that can receive events of the given event type.

template <int EventId>
class Receiver: public ReceiverInterface {
public:
    Receiver() {
        ds::events::Dispatcher::subscribe(EventId, this);
    }

    ~Receiver() override {
        ds::events::Dispatcher::unsubscribe(EventId, this);
    }

public:
    void onEvent(Event const& event) override = 0;
};

}