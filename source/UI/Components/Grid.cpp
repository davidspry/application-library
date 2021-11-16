//! @date 25/10/21
//! @author David Spry

#include "Grid.hpp"

namespace ds::ui {

Point<int> Grid::getGridPositionAsPixelOffset(Point<int> const& gridPosition) const {
    return {gridPosition.x * static_cast<int>(spacing().w), gridPosition.y * static_cast<int>(spacing().h)};
}

Point<int> Grid::getGridPositionAtPoint(Point<int> const& xy) const {
    auto const row = (xy.y - static_cast<int>(origin().y)) / static_cast<int>(spacing().h);
    auto const col = (xy.x - static_cast<int>(origin().x)) / static_cast<int>(spacing().w);
    return {
            std::min(dimensions().x - 1, std::max(0, col)),
            std::min(dimensions().y - 1, std::max(0, row))
    };
}

}