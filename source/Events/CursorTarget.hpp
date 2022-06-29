//! @date 16/10/21
//! @author David Spry

#pragma once

#include <UI/Point.hpp>
#include <Events/CursorEvent.hpp>

namespace ds::ui {

//! @class A class that can be interacted with by a cursor.

class CursorTarget {
public:
    //! @brief This method should be invoked when the cursor moves.
    //! @param event An event representing the state of the cursor.

    inline void cursorMove(CursorEvent const& event) {
        if (didCursorLeave(event)) {
            cursorDidLeave(event);
            setCursorIsHovering(false);
        } else if (didCursorEnter(event)) {
            cursorDidEnter(event);
            setCursorIsHovering(true);
        } else { cursorDidMove(event); }
    }

    //! @brief This method should be invoked when a cursor press occurs.
    //! @param event An event representing the state of the cursor.

    inline void cursorDown(CursorEvent const& event) {
        cursorWasDown(event);

        if (isCursorInBounds(event)) {
            setIsBeingPressed(true);
            targetWasPressed(event);
        }
    }

    //! @brief This method should be invoked when a cursor drag occurs.
    //! @param event An event representing the state of the cursor.

    inline void cursorDrag(CursorEvent const& event) {
        cursorDidDrag(event);
        setIsBeingPressed(isBeingPressed());
    }

    //! @brief This method should be invoked when a cursor press is released.
    //! @param event An event representing the state of the cursor.

    inline void cursorUp(CursorEvent const& event) {
        cursorWasUp(event);

        if (isBeingPressed()) {
            setIsBeingPressed(false);

            if (isCursorInBounds(event)) {
                targetWasReleased(event);
            }
        }
    }

public:
    //! @brief Indicate whether the cursor is hovering over the target or not.

    [[nodiscard]] inline bool isCursorHovering() const {
        return cursorIsHovering;
    }

    //! @brief Indicate whether the cursor is pressing on the target or not.

    [[nodiscard]] inline bool isBeingPressed() const {
        return hasBeenPressed;
    }

protected:
    //! @brief Stipulate whether the cursor is hovering over the target or not.
    //! @param isHovering Whether the cursor is hovering over the target or not.

    inline void setCursorIsHovering(bool const isHovering) {
        cursorIsHovering = isHovering;
    }

    //! @brief Stipulate whether the cursor is pressing on the target or not.
    //! @param isHovering Whether the cursor is pressing on the target or not.

    inline void setIsBeingPressed(bool const isBeingPressed) {
        hasBeenPressed = isBeingPressed;
    }

protected:
    //! @brief Indicate whether the cursor lies within the bounds of the target or not.
    //! @param event The cursor event to be tested.

    [[nodiscard]] virtual bool isCursorInBounds(CursorEvent const& event) const = 0;

protected:
    //! @brief This method is invoked when a cursor press is released.
    //! @param event The event that triggered the callback.

    virtual void cursorWasUp(CursorEvent const& event) {
    }

    //! @brief This method is invoked when a cursor press occurs.
    //! @param event The event that triggered the callback.

    virtual void cursorWasDown(CursorEvent const& event) {
    }

    //! @brief This method is invoked when the cursor target is pressed.
    //! @param event The event that triggered the callback.

    virtual void targetWasPressed(CursorEvent const& event) {
    }

    //! @brief This method is invoked when the cursor target is released (i.e., it is no longer being pressed)
    //! @param event The event that triggered the callback.

    virtual void targetWasReleased(CursorEvent const& event) {
    }

    //! @brief This method is invoked when a cursor drag occurs.
    //! @param event The event that triggered the callback.

    virtual void cursorDidDrag(CursorEvent const& event) {
    }

    //! @brief This method is invoked when the cursor moves within the bounds of the target.
    //! @param event The event that triggered the callback.

    virtual void cursorDidMove(CursorEvent const& event) {
    }

    //! @brief This method is invoked when the cursor enters the bounds of the target..
    //! @param event The event that triggered the callback.

    virtual void cursorDidEnter(CursorEvent const& event) {
    }

    //! @brief This method is invoked when the cursor leaves the bounds of the target.
    //! @param event The event that triggered the callback.

    virtual void cursorDidLeave(CursorEvent const& event) {
    }

private:
    //! @brief Indicate whether the cursor has entered the bounds of the target or not.
    //! @param event The cursor event to be tested.

    [[nodiscard]] bool didCursorEnter(CursorEvent const& event) const {
        return not isCursorHovering()
               and isCursorInBounds(event);
    };

    //! @brief Indicate whether the cursor has left the bounds of the target or not.
    //! @param event The cursor event to be tested.

    [[nodiscard]] bool didCursorLeave(CursorEvent const& event) const {
        return not isCursorInBounds(event)
               and isCursorHovering();
    }

private:
    bool hasBeenPressed {false};
    bool cursorIsHovering {false};
};

}