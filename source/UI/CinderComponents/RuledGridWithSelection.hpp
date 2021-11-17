//! @date 15/11/21
//! @author David Spry

#pragma once

#include <UI/Constructs/MarqueeSelection.hpp>
#include <UI/CinderComponents/RuledGridWithCursor.hpp>

namespace ds::ui {

class RuledGridWithSelection: public RuledGridWithCursor {
public:
    RuledGridWithSelection(int const rows, int const columns):
            RuledGridWithCursor(rows, columns) {
        init();
    }

    RuledGridWithSelection(int const rows, int const columns, ds::ui::Size<float> const& cellSize):
            RuledGridWithCursor(rows, columns, cellSize) {
        init();
    }

private:
    void init();

public:
    void draw() override;
    void draw(Point<float> const& offset) override;
    void draw(float offsetX, float offsetY) override;

public:
    //! @brief Get the bounds of the marquee selection if one exists or the cursor position otherwise.

    [[nodiscard]] ds::ui::Bounds<int> getSelectionBounds() const;

public:
    void moveCursor(Direction const&& direction) override;

    //! @brief Move the grid's cursor in the given direction and optionally
    //! contribute to the grid's marquee selection.
    //! @param direction The direction in which the grid's cursor should be moved.
    //! @param shouldExtendSelection Whether the grid's cursor should contribute to
    //! the grid's marquee selection or not.

    void moveCursor(Direction const&& direction, bool shouldExtendSelection);

protected:
    void targetWasPressed(CursorEvent const& event) override;
    void cursorWasDown(CursorEvent const& event) override;
    void cursorDidDrag(CursorEvent const& event) override;

private:
    void processCursorEvent(CursorEvent const& event);

private:
    MarqueeSelection selection;

private:
    cinder::gl::BatchRef marquee;
};

}