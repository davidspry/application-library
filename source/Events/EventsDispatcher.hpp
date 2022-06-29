//! @date 15/11/21
//! @author David Spry

#pragma once

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <Events/Event.hpp>
#include <Events/EventsReceiverInterface.hpp>

namespace ds::events {

class Dispatcher final {
public:
    Dispatcher() = delete;

public:
    static void dispatch(Event const& event);
    static void subscribe(int eventId, ReceiverInterface* receiver);
    static void unsubscribe(int eventId, ReceiverInterface* receiver);

private:
    using EventReceivers = std::vector<ReceiverInterface*>;
    using EventChannels = std::unordered_map<int, EventReceivers>;
    static EventChannels inline channels {};
};

}