//! @date 24/11/21
//! @author David Spry

#pragma once

#include <algorithm>
#include <functional>
#include <type_traits>
#include <Events/CursorTarget.hpp>
#include <iostream>

namespace ds::ui {

template<typename T>
class SliderState: public ds::ui::CursorTarget {
public:
    //! @brief Create a slider state with the given callback function.
    //! @param callback The function to be invoked as the slider state changes.

    explicit SliderState(std::function<void(T sliderValue)>&& callback):
            SliderState(static_cast<T>(0),
                        static_cast<T>(0),
                        static_cast<T>(1),
                        std::move(callback)) {
    }

    //! @brief Create a slider state with the given range and initial value.
    //! @param minimumValue The desired minimum value.
    //! @param initialValue The desired initial value.
    //! @param maximumValue The desired maximum value.
    //! @param callback The function to be invoked as the slider state changes.

    SliderState(T const minimumValue,
                T const initialValue,
                T const maximumValue,
                std::function<void(T sliderValue)>&& callback):
            minimum(static_cast<float>(minimumValue)),
            maximum(static_cast<float>(maximumValue)),
            sliderCallback(std::move(callback)) {
        static_assert(std::is_integral_v<T> or std::is_floating_point_v<T>,
                      "The given type must either be integral or floating point");

        setValue(initialValue);
    }


    virtual ~SliderState() = default;

public:
    //! @brief Get the underlying value.

    inline T getValue() const {
        return static_cast<T>(minimum + value * (maximum - minimum));
    }

    //! @brief Get the slider's current position as a number between 0 and 1.

    [[nodiscard]] inline float getSliderPosition() const {
        return value;
    }

public:
    //! @brief Set the current value.
    //! @param newValue The desired value.

    inline void setValue(T const newValue) {
        auto const bounded = std::clamp(static_cast<float>(newValue), minimum, maximum);
        auto const normalised = (bounded - minimum) / (maximum - minimum);

        updateSliderValue(normalised);
    }

    //! @brief Set the minimum value.
    //! @param minimumValue The desired minimum value.

    inline void setMinimumSliderValue(T const minimumValue) {
        minimum = static_cast<float>(minimumValue);
    }

    //! @brief Set the maximum value.
    //! @param minimumValue The desired maximum value.

    inline void setMaximumSliderValue(T const maximumValue) {
        maximum = static_cast<float>(maximumValue);
    }

protected:
    void cursorWasDown(CursorEvent const& event) override {
        if (isCursorInBounds(event)) {
            lastDownPosition = event.xy.x;
        }
    }

    void cursorDidDrag(CursorEvent const& event) override {
        if (isBeingPressed()) {
            auto const start = sliderOriginX();
            auto const width = sliderWidthInPixels();
            auto const point = static_cast<float>(event.xy.x);

            if (not(value == 0.0f and point < start) and
                not(value == 1.0f and point > start + width)) {
                updateSliderValue(value - (lastDownPosition - point) / width);
            }

            lastDownPosition = event.xy.x;
        }
    }

protected:
    //! @brief This method is invoked after the slider state is updated.

    virtual void didUpdateSliderValue() {
    };

    //! @brief The x-coordinate of the slider's origin point.

    [[nodiscard]] virtual float sliderOriginX() const = 0;

    //! @brief The width of the slider track in pixels.

    [[nodiscard]] virtual float sliderWidthInPixels() const = 0;

private:
    //! @brief Update the slider value with the given normalised value.
    //! @param position A position value between 0 and 1 (inclusive).

    void updateSliderValue(float const position) {
        value = std::clamp(position, 0.0f, 1.0f);

        if (sliderCallback) {
            sliderCallback(getValue());
        }

        didUpdateSliderValue();
    }

protected:
    float value {0.0f};
    float minimum;
    float maximum;

protected:
    std::function<void(T sliderValue)> sliderCallback;

private:
    int lastDownPosition {};
};

}