//! @date 12/11/21
//! @author David Spry

#pragma once

#include <functional>
#include <UI/Component.hpp>
#include <Events/CursorTarget.hpp>

namespace ds::ui {

//! @enum Parameters for a ButtonState that define its behaviour.

enum class ButtonStateType {
    Latch, Momentary
};

//! @class The state underlying a button.

template<ButtonStateType ButtonType = ButtonStateType::Latch>
class ButtonState: public ds::ui::CursorTarget {
public:
    //! @brief Create a button state with the given callback function and initial state.
    //! @param callback The function to be invoked as the button state changes.
    //! @param initialState The initial state of the button.

    ButtonState(std::function<void(bool buttonState)>&& callback,
                bool const initialState): ds::ui::CursorTarget(),
                                          buttonCallback(std::move(callback)),
                                          buttonIsPressed(initialState) {
    }

    virtual ~ButtonState() = default;

public:
    //! @brief Indicate whether the button is currently pressed or not.

    [[nodiscard]] inline bool isButtonPressed() const {
        return buttonIsPressed;
    }

    //! @brief Set the state of the button.
    //! @param isButtonPressed Whether the button should be 'pressed' or not.

    inline void setIsButtonPressed(bool const isButtonPressed) {
        buttonIsPressed = isButtonPressed;
    }

protected:
    inline void targetWasPressed(CursorEvent const& event) override {
        /* Latch implementation */
    }

    inline void targetWasReleased(CursorEvent const& event) override {
        buttonIsPressed = !buttonIsPressed;
        buttonStateWasToggled();
    }

private:
    inline void buttonStateWasToggled() const {
        if (buttonCallback) {
            buttonCallback(buttonIsPressed);
        }
    }

protected:
    bool buttonIsPressed {false};

protected:
    std::function<void(bool buttonState)> buttonCallback;
};

template<>
inline void ButtonState<ButtonStateType::Momentary>::targetWasPressed(CursorEvent const& event) {
    buttonIsPressed = !buttonIsPressed;
    buttonStateWasToggled();
}

}