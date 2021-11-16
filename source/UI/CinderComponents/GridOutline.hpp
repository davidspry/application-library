//! @date 25/10/21
//! @author David Spry

#pragma once

#include "RuledGrid.hpp"

namespace ds::ui {

class GridOutline: public RuledGrid {
public:
    GridOutline(int const rows, int const columns):
            RuledGrid(rows, columns) {
        init();
    }

    GridOutline(int const rows, int const columns, ds::ui::Size<float> const& cellSize):
            RuledGrid(rows, columns, cellSize) {
        init();
    }

public:
    void draw() override;
    void draw(Point<float> const& offset) override;
    void draw(float offsetX, float offsetY) override;

private:
    void init();
};

}