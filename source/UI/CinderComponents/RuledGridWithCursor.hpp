//! @date 15/11/21
//! @author David Spry

#pragma once

#include <algorithm>
#include <Events/CursorTarget.hpp>
#include <UI/Constructs/GridPosition.hpp>
#include <UI/CinderComponents/RuledGrid.hpp>

namespace ds::ui {

class RuledGridWithCursor: public RuledGrid,
                           public CursorTarget,
                           public GridPosition {
public:
    RuledGridWithCursor(int const rows, int const columns):
            RuledGrid(rows, columns) {
        init();
    }

    RuledGridWithCursor(int const rows, int const columns, ds::ui::Size<float> const& cellSize):
            RuledGrid(rows, columns, cellSize) {
        init();
    }

private:
    void init();

public:
    void draw() override;
    void draw(Point<float> const& offset) override;
    void draw(float offsetX, float offsetY) override;

public:
    void moveCursor(Direction const&& direction) override;
    void moveCursorTo(Point<int> const& screenPosition) override;

protected:
    [[nodiscard]] bool isCursorInBounds(CursorEvent const& event) const override;
    void targetWasPressed(CursorEvent const& event) override;
    void cursorDidDrag(CursorEvent const& event) override;

protected:
    cinder::gl::BatchRef cursor;
};

}