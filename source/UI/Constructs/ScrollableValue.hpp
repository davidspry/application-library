//! @date 26/10/21
//! @author David Spry

#pragma once

#include <type_traits>
#include "Events/CursorTarget.hpp"

namespace ds::ui {

//! @class A numeric value that can be scrolled within a range by a cursor.

template<typename T>
class ScrollableValue: public ds::ui::CursorTarget {
public:
    //! @brief Create a scrolled value between 0 and 1.

    ScrollableValue(): ScrollableValue(0, 0, 1) {
    }

    //! @brief Create a scrolled value with the given range and initial value.
    //! @param minimumValue The desired minimum value.
    //! @param initialValue The desired initial value.
    //! @param maximumValue The desired maximum value.

    ScrollableValue(T const minimumValue,
                    T const initialValue,
                    T const maximumValue): minimum(minimumValue),
                                           maximum(maximumValue) {
        static_assert(std::is_integral_v<T> or std::is_floating_point_v<T>,
                      "The given type must either be integral or floating point");

        sourceValue = static_cast<double>(initialValue);
        updateScrollableValue(0.0);
    }

    virtual ~ScrollableValue() = default;

public:
    //! @brief Get the underlying value.

    inline T getValue() const {
        return value;
    }

public:
    //! @brief Set the current value.
    //! @param newValue The desired value.

    virtual inline void setValue(T const newValue) {
        sourceValue = static_cast<double>(newValue);

        updateScrollableValue(0.0);
    }

    //! @brief Set the minimum value.
    //! @param minimumValue The desired minimum value.

    inline void setMinimumScrollableValue(T const minimumValue) {
        minimum = minimumValue;

        setScrollScale((maximum - minimum) * 0.001);
    }

    //! @brief Set the maximum value.
    //! @param minimumValue The desired maximum value.

    inline void setMaximumScrollableValue(T const maximumValue) {
        maximum = maximumValue;

        setScrollScale((maximum - minimum) * 0.001);
    }

    //! @brief Set the scroll scale factor.
    //! @param scaleValue The desired scroll scale factor.

    inline void setScrollScale(double const scaleValue) {
        scrollScale = scaleValue;
    }

protected:
    void cursorWasDown(CursorEvent const& event) override {
        if (isCursorInBounds(event)) {
            auto const delta = static_cast<double>(lastDownPosition.y - event.xy.y) * scrollScale;
            updateScrollableValue(isBeingPressed() ? delta : 0.0);
            lastDownPosition = event.xy;
        }
    }

    void cursorDidDrag(CursorEvent const& event) override {
        if (isBeingPressed()) {
            auto const delta = static_cast<double>(lastDownPosition.y - event.xy.y) * scrollScale;
            updateScrollableValue(delta);
            lastDownPosition = event.xy;
        }
    }

protected:
    //! @brief This method is invoked after the scrollable value has been updated.

    virtual void didUpdateScrollableValue() {
    };

private:
    //! @brief Update the scrollable value by adding the given delta.
    //! @param delta The amount to add to the scrollable value.

    void updateScrollableValue(double const delta) {
        sourceValue = sourceValue + delta;
        sourceValue = std::min(static_cast<double>(maximum), sourceValue);
        sourceValue = std::max(static_cast<double>(minimum), sourceValue);
        value = static_cast<T>(sourceValue);

        didUpdateScrollableValue();
    }

private:
    T value {};
    T minimum {static_cast<T>(0)};
    T maximum {static_cast<T>(1)};
    double scrollScale {0.5};
    double sourceValue {0.0};

private:
    Point<int> lastDownPosition {};
};

}