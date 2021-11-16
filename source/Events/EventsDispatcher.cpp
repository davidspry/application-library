//! @date 15/11/21
//! @author David Spry

#include "EventsDispatcher.hpp"

namespace ds::events {

void Dispatcher::dispatch(Event const& event) {
    if (channels().contains(event.type)) {
        auto const& channel = channels().at(event.type);
        for (auto receiver: channel) {
            receiver->onEvent(event);
        }
    }
}

void Dispatcher::subscribe(EventType const& eventType, ReceiverInterface* const receiver) {
    channels()[eventType].push_back(receiver);
}

void Dispatcher::unsubscribe(EventType const& eventType, ReceiverInterface* receiver) {
    if (channels().contains(eventType)) {
        auto& channel = channels().at(eventType);
        auto iterator = std::find(channel.cbegin(), channel.cend(), receiver);
        if (iterator != channel.cend()) {
            channel.erase(iterator);
        }
    }
}

}