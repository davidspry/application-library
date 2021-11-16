//! @date 12/11/21
//! @author David Spry

#pragma once

#include <atomic>
#include <UI/Constructs/ButtonState.hpp>
#include <UI/CinderComponents/GridOutline.hpp>

namespace ds::ui {

class Button: public ds::ui::GridOutline,
              public ds::ui::ButtonState<ButtonStateType::Latch> {
public:
    //! @brief Create a button that synchronises with the given variable.
    //! @param buttonStateVariable The variable that should be synchronised with the button state.

    explicit Button(bool& buttonStateVariable):
            Button([&](bool const& buttonState) {
                buttonStateVariable = buttonState;
            }, buttonStateVariable) {
    }

    //! @brief Create a button that synchronises with the given variable.
    //! @param buttonStateVariable The variable that should be synchronised with the button state.

    explicit Button(std::atomic<bool>& buttonStateVariable):
            Button([&](bool const& buttonState) {
                buttonStateVariable.store(buttonState);
            }, buttonStateVariable.load()) {
    }

    //! @brief Create a button that invokes the given function with its state.
    //! @param callback The function that should be invoked when the button's state changes.
    //! @param initialButtonState The button's initial state, which defaults to `false`.

    explicit Button(std::function<void(bool const&)> callback, bool const initialButtonState = false):
            GridOutline(1, 2),
            ButtonState(std::move(callback), initialButtonState) {
        init();
    }

private:
    void init();

public:
    void draw() override;
    void draw(Point<float> const& offset) override;
    void draw(float offsetX, float offsetY) override;

public:
    //! @brief Set the button's active colour.
    //! @param colour The desired active colour.

    inline void setActiveColour(cinder::Color8u const& colour) {
        activeColour = colour;
    }

    //! @brief Set the button's active colour.
    //! @param red The red component of the desired active colour.
    //! @param green The green component of the desired active colour.
    //! @param blue The blue component of the desired active colour.

    inline void setActiveColour(uint8_t const red, uint8_t const green, uint8_t const blue) {
        setActiveColour({red, green, blue});
    }

protected:
    [[nodiscard]] bool isCursorInBounds(CursorEvent const& event) const override;

protected:
    cinder::Color8u activeColour {75, 200, 155};

protected:
    cinder::gl::BatchRef buttonFill;
};

}