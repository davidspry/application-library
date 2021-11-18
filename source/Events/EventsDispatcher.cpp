//! @date 15/11/21
//! @author David Spry

#include "EventsDispatcher.hpp"

namespace ds::events {

void Dispatcher::dispatch(Event const& event) {
    if (channels().contains(event.id)) {
        auto const& channel = channels().at(event.id);
        for (auto receiver: channel) {
            receiver->onEvent(event);
        }
    }
}

void Dispatcher::subscribe(int const& eventId, ReceiverInterface* const receiver) {
    channels()[eventId].push_back(receiver);
}

void Dispatcher::unsubscribe(int const& eventId, ReceiverInterface* receiver) {
    if (channels().contains(eventId)) {
        auto& channel = channels().at(eventId);
        auto iterator = std::find(channel.cbegin(), channel.cend(), receiver);
        if (iterator != channel.cend()) {
            channel.erase(iterator);
        }
    }
}

}