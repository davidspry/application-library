//! @date 25/10/21
//! @author David Spry

#pragma once

#include <UI/Components/Grid.hpp>
#include <Shaders/GridCells.hpp>
#include <cinder/gl/gl.h>
#include <vector>

namespace ds::ui {

class DotGrid: public Grid {
public:
    DotGrid(int const rows, int const columns): Grid(rows, columns) {
        init();
    }

    DotGrid(int const rows, int const columns, ds::ui::Size<float> const& cellSize):
            Grid(rows, columns, cellSize) {
        init();
    }

private:
    void init();

public:
    void draw() override;
    void draw(Point<float> const& offset) override;
    void draw(float offsetX, float offsetY) override;

private:
    float dotRadius {3.0f};

private:
    cinder::gl::BatchRef batch;
};

}