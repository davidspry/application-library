//! @date 15/11/21
//! @author David Spry

#pragma once

#include <UI/Point.hpp>

namespace ds::ui {

class GridPosition {
public:
    GridPosition() = default;

public:
    enum class Direction {
        Up, Right, Down, Left
    };

public:
    [[nodiscard]] inline Point<int> const& getCursorPosition() const {
        return position;
    }

public:
    virtual void moveCursor(Direction const&& direction) = 0;
    virtual void moveCursorTo(Point<int> const& screenPosition) = 0;

protected:
    Point<int> position {};
};

}