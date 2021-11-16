//! @date 13/11/21
//! @author David Spry

#pragma once

#include <UI/Bounds.hpp>

namespace ds::ui {

class MarqueeSelection: public ds::ui::Bounds<int> {
public:
    MarqueeSelection() = default;

public:
    //! @brief Indicate whether the MarqueeSelection currently contains a selection.

    [[nodiscard]] inline bool containsSelection() const {
        return isBuildingSelection;
    }

public:
    void buildSelection(Point<int> const& point) {
        if (not isBuildingSelection) {
            isBuildingSelection = true;
            cursorOrigin = point;
            setSizeFromOrigin(0, 0);
            setPositionWithOrigin(point);
        } else {
            Point<int> const upperLeft {
                    std::min(cursorOrigin.x, point.x),
                    std::min(cursorOrigin.y, point.y)
            };

            auto const direction = point.x < cursorOrigin.x or
                                   point.y < cursorOrigin.y;

            Point<int> const lowerRight {
                    std::max(cursorOrigin.x + static_cast<int>(direction), point.x + 1),
                    std::max(cursorOrigin.y + static_cast<int>(direction), point.y + 1)
            };

            setPositionWithOrigin(upperLeft);
            setSizeFromOrigin(lowerRight - upperLeft);
        }
    }

    inline void resetSelection() {
        isBuildingSelection = false;
        setSizeFromOrigin(0, 0);
    }

private:
    bool isBuildingSelection {false};

private:
    Point<int> cursorOrigin {};
};

}